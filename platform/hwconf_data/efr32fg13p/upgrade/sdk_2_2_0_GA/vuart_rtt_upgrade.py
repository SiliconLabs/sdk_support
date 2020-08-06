from .upgradeUtility import *

description="VUART module property HAL_VUART_TYPE no longer has HAL_VUART_TYPE_RTT as an option. HAL_VUART_TYPE_RTT->HAL_VUART_TYPE_SWO"
version="2.2.0"
priority=1
def upgradeCallback(xmlDevice, verbose=False):
	verbose = True
	if verbose:
		print ("%s upgradeCallback" % __name__)
	xmlMode = xmlDevice.getModes()[0]
	renamePropertyText(xmlMode, "HAL_VUART_TYPE_RTT", "HAL_VUART_TYPE_SWO", verbose)
	return xmlDevice
