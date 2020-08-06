import os
import glob
from importlib import import_module
from distutils.version import StrictVersion

VERBOSE=False
UPGRADE_CURRENT_VERSION=False

def importUpgradeRules(upgradeModule, verbose=False):
  ms = glob.glob(os.path.abspath(os.path.dirname(__file__)) + "/*/*.py")
  modelfiles =  list(set([upgradeModule.__name__+"."+os.path.relpath(os.path.dirname(f), start=os.path.dirname(__file__)).replace(os.path.sep, ".") for f in ms if not f.startswith('_')]))
  versionModules = [import_module(m) for m in modelfiles]
  if(verbose):
    print ("Version Modules: " + str([v.__name__ for v in versionModules]))
  upgradeModules = []
  for m in versionModules:
    newmodules= [import_module(".".join([m.__name__,rule])) for rule in m.__all__]
    upgradeModules.extend(newmodules)
  if (verbose):
    print ("Upgrade Modules:")
    for u in upgradeModules:
      print ("%s | %s | %s" % (u.__name__, u.version, u.description))
  return upgradeModules

def filterUpgrades(upgradeRules, version, xmlDevice):
  matchedUpgrades = []
  for u in upgradeRules:
    # Skip upgrades if HWCONF version is newer or equal to upgrade rule version
    if version >= StrictVersion(u.version):
      continue
    matchedUpgrades.append(u)
  return matchedUpgrades

def upgradeMain(upgradeModule, xmlDevice):
  # Import all upgrade rules
  upgradeRules = importUpgradeRules(upgradeModule, verbose=VERBOSE)
  
  contextId = xmlDevice.getContextId()
  # Expect contextId like com.silabs.sdk.stack.super:2.1.0._-2123046338
  # Matches <major>.<minor>.<special> version number enclosed between ":" and "_"
  try:
    version = StrictVersion(contextId.split(':')[1].split("_")[0].rstrip("."))
  except:
    print ("FATAL ERROR: Failed to extract version from HWCONF contextId: " + contextId)
    return (xmlDevice, "FATAL ERROR: Failed to extract version from HWCONF contextId: " + contextId)
  print ('Current HWCONF version: ' + str(version))

  # Filter upgrade rules for current or higher version
  matchedUpgrades = filterUpgrades(upgradeRules, version, xmlDevice)
  # Sort rules so that they are applied in order by version, then priority
  matchedUpgrades = sorted(matchedUpgrades, key=lambda x:(StrictVersion(x.version), x.priority))

  if len(matchedUpgrades)>0:
    print ("Matched Upgrades: " + str([x.__name__[x.__name__.find("sdk"):] for x in matchedUpgrades]))
    # Run upgrade rules and compile change text to present in Studio
    changeText = "This HWCONF file has been upgraded to the current SDK. The following upgrade rules were applied:\n"
    for u in matchedUpgrades:
      xmlDevice = u.upgradeCallback(xmlDevice, verbose=VERBOSE)
      changeText+= "%s (%s)\n" % (u.description, u.version)
    print (changeText)
    # return xmlDevice and changeText to upgrade hook to be packaged in a newXMLDeviceChange
    return (xmlDevice, changeText)
  else:
    print ("No matched upgrades")
    return
