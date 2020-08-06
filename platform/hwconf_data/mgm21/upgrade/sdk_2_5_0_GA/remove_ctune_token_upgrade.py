from .upgradeUtility import *

description="BSP_CLK_HFXO_CTUNE_TOKEN is no longer used, now CTUNE is by default set using one of the following, listed in order of priority. Factory calibrated value, manufacturing token value, BSP_CLK_HFXO_CTUNE, default."
version="2.5.0"
priority=1
def upgradeCallback(xmlDevice, verbose=False):
	verbose = True
	if verbose:
		print ("%s upgradeCallback" % __name__)
	newXmlDevice = removePropertyLine(xmlDevice, "CMU.BSP_CLK_HFXO_CTUNE_TOKEN.BOOL", verbose)
	return newXmlDevice