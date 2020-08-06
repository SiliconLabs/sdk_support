from .upgradeUtility import *

description="PA voltage is now a BSP define: HAL_PA_VOLTAGE->BSP_PA_VOLTAGE"
version="2.1.0"
priority = 1
def upgradeCallback(xmlDevice, verbose=False):
  if verbose:
    print ("%s upgradeCallback" % __name__)
  xmlMode = xmlDevice.getModes()[0]
  renamePropertyText(xmlMode, "HAL_PA_VOLTAGE", "BSP_PA_VOLTAGE", verbose)
  return xmlDevice