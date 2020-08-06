#SDK 2.2.0 GA upgrade utilities

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