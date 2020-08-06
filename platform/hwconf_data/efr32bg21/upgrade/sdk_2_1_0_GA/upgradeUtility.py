# SDK 2.1.0 GA upgrade utilities

# Rename set property with oldPropertyId to newPropertyId
def renameFullPropertyId(xmlmode, oldPropertyId, newPropertyId, verbose=False):
  properties = xmlmode.getProperty()
  for p in properties:
    if oldPropertyId == p.getPropertyId():
      if verbose:
        print ("Renaming %s->%s" % (oldPropertyId, newPropertyId))
      p.setPropertyId(newPropertyId)

# Replace text in propertyId. Useful for changing define without checking
# object/module or type specifiers.
def renamePropertyText(xmlmode, oldPropertyText, newPropertyText, verbose=False):
  properties = xmlmode.getProperty()
  for p in properties:
    # prop[0] = module
    # prop[1] = property
    # prop[2] = type
    prop=p.getPropertyId().split(".")
    if oldPropertyText == prop[1]:
      prop[1] = newPropertyText
      newPropertyId = ".".join(prop)
      if verbose:
        print ("Renaming %s->%s" % (p.getPropertyId(), newPropertyId))
      p.setPropertyId(newPropertyId)

# Replace property with oldPropertyId with a new one with newPropertyId and the
# same object/module and value. This should have the same effect as renameFullPropertyId
# Note this function returns an xmldevice which should be passed back up to the
# upgradeDispatch level. Example:
#   newXmlDevice = replaceProperty(xmlDevice, "PA.HAL_PA_VOLTAGE.INT", "PA.BSP_PA_VOLTAGE.INT")
#   return newXmlDevice
def replaceProperty(xmldevice, oldPropertyId, newPropertyId, verbose=False):
  xmlmode = xmldevice.getModes()[0]
  properties = xmlmode.getProperty()
  removeList = []
  for i in range(0,len(properties)):
    p = properties[i]
    if oldPropertyId == p.getPropertyId():
      if verbose:
        print ("Replacing %s->%s" % (oldPropertyId, newPropertyId))
      newval = xmldevice.createPropertyValue(newPropertyId.split('.')[0], newPropertyId, p.getValue())
      xmlmode.addProperty(newval)
      removeList.append(i)
  # reverse sort indicies in removeList so they can be removed from last to first
  for index in sorted(removeList, reverse=True):
    xmlmode.removeProperty(index)
  return xmldevice

# Replace the object and a substring of the propertyId with new values. Useful when changing
# entire modules name. Example:
#   newXmlDevice = replaceObjAndPropertyStr(xmlDevice, "LNA", "FEM", "BSP_LNA_TXRX", "BSP_FEM_RX")
#   return newXmlDevice
def replaceObjAndPropertyStr(xmldevice, oldObject, newObject, oldPropertyText, newPropertyText, verbose=False):
  xmlmode = xmldevice.getModes()[0]
  properties = xmlmode.getProperty()
  removeList = []
  for i in range(0,len(properties)):
    p = properties[i]
    oldPropertyId = p.getPropertyId()
    prop=oldPropertyId.split(".")
    # prop[0] = module
    # prop[1] = property
    # prop[2] = type
    # if the propertyId contains the old propertyId substring and the object matches
    if (oldPropertyText in prop[1]) and (oldObject == prop[0]):
      prop[0] = newObject
      # replace the old text substring with the new substring, a max of 1 time
      prop[1] = prop[1].replace(oldPropertyText, newPropertyText, 1)
      newPropertyId = ".".join(prop)
      if verbose:
        print ("Replacing %s->%s" % (oldPropertyId, newPropertyId))
      newval = xmldevice.createPropertyValue(newObject, newPropertyId, p.getValue())
      xmlmode.addProperty(newval)
      removeList.append(i)
  # reverse sort indicies in removeList so they can be removed from last to first
  for index in sorted(removeList, reverse=True):
    xmlmode.removeProperty(index)
  return xmldevice

# Replace the object of an ABPeripheral.included property line. Useful when changing
# entire module name
def replaceABPeripheralObject(xmldevice, oldObject, newObject, verbose):
  xmlmode = xmldevice.getModes()[0]
  properties = xmlmode.getProperty()
  removeList = []
  for i in range(0,len(properties)):
    p = properties[i]
    propertyId = p.getPropertyId()
    obj = p.getObject()
    if (propertyId == "ABPeripheral.included") and (obj == oldObject):
      if verbose:
        print ("Replacing %s ABPeripheral -> %s ABPeripheral" % (oldObject, newObject))
      newval = xmldevice.createPropertyValue(newObject, propertyId, p.getValue())
      xmlmode.addProperty(newval)
      removeList.append(i)
  # reverse sort indicies in removeList so they can be removed from last to first
  for index in sorted(removeList, reverse=True):
    xmlmode.removeProperty(index)
  return xmldevice

# Add a new property line
def addNewProperty(xmldevice, fullPropertyId, value, verbose):
  xmlmode = xmldevice.getModes()[0]
  if verbose:
        print ("Adding %s" % fullPropertyId)
  newval = xmldevice.createPropertyValue(fullPropertyId.split('.')[0], fullPropertyId, value)
  xmlmode.addProperty(newval)
  return xmldevice

# Checks if there are any instances of a certain object in the hwconf file
def objectInHwconf(xmldevice, obj):
  xmlmode = xmldevice.getModes()[0]
  properties = xmlmode.getProperty()
  for i in range(0,len(properties)):
    p = properties[i]
    o = p.getObject()
    if o == obj:
      return True
