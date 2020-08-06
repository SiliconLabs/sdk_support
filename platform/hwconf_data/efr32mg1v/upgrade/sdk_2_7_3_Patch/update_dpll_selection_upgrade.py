from .upgradeUtility import *

description="In order to use DPLL, HAL_CLK_HFCLK_SOURCE now needs to be set to HFRCODPLL instead of HFRCO."
version="2.7.3"
priority=1
def upgradeCallback(xmlDevice, verbose=False):
	verbose = True
	if verbose:
		print ("%s upgradeCallback" % __name__)
	if propertyIDInHwconfHasValue(xmlDevice, "CMU.HAL_CLK_HFCLK_SOURCE.ENUM", "HAL_CLK_HFCLK_SOURCE_HFRCO"):
		if not propertyIDInHwconfHasValue(xmlDevice, "CMU.HAL_CLK_PLL_CONFIGURATION.ENUM", "HAL_CLK_PLL_CONFIGURATION_NONE"):
			newXmlDevice = removePropertyLine(xmlDevice, "CMU.HAL_CLK_HFCLK_SOURCE.ENUM", verbose)
			newXmlDevice = addNewProperty(xmlDevice, "CMU.HAL_CLK_HFCLK_SOURCE.ENUM", "HAL_CLK_HFCLK_SOURCE_HFRCODPLL", verbose)
		else:
			newXmlDevice = removePropertyLine(xmlDevice, "CMU.HAL_CLK_PLL_CONFIGURATION.ENUM", verbose)
	return newXmlDevice