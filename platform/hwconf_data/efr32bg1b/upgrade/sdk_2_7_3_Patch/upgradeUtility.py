# SDK 2.7.3 Patch upgrade utilities

# Remove property with propertyId
# Note this function returns an xmldevice which should be passed back up to the
# upgradeDispatch level. Example:
#   newXmlDevice = removePropertyLine(xmlDevice, "CMU.HAL_CLK_HFCLK_SOURCE.ENUM", verbose)
#   return newXmlDevice
def removePropertyLine(xmldevice, propertyId, verbose=False):
  xmlmode = xmldevice.getModes()[0]
  properties = xmlmode.getProperty()
  removeList = []
  for i in range(0,len(properties)):
    p = properties[i]
    if propertyId == p.getPropertyId():
      if verbose:
        print ("Removing %s" % (propertyId))
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
# that have a certain value
def propertyIDInHwconfHasValue(xmldevice, propertyId, value):
  xmlmode = xmldevice.getModes()[0]
  properties = xmlmode.getProperty()
  for i in range(0,len(properties)):
    p = properties[i]
    propId = p.getPropertyId()
    if propId == propertyId:
      if p.getValue() == value:
        return True
