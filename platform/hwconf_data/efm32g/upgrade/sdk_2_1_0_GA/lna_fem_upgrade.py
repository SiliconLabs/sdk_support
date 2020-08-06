from .upgradeUtility import *

description="LNA module is now FEM module: BSP_LNA_TXRX->BSP_FEM_RX, BSP_LNA_SLEEP->BSP_FEM_SLEEP, new definitions available. LNA module assumed RX channel active: HAL_FEM_RX_ACTIVE created and set to true if LNA was enabled"
version="2.1.0"
priority=1
def upgradeCallback(xmlDevice, verbose=False):
	verbose = True
	if verbose:
		print ("%s upgradeCallback" % __name__)
	if objectInHwconf(xmlDevice, "LNA") == True:
		addNewProperty(xmlDevice, "FEM.HAL_FEM_RX_ACTIVE.BOOL", "1", verbose)
	replaceABPeripheralObject(xmlDevice, "LNA", "FEM", verbose)
	replaceObjAndPropertyStr(xmlDevice, "LNA", "FEM", "BSP_LNA_TXRX", "BSP_FEM_RX", verbose)
	replaceObjAndPropertyStr(xmlDevice, "LNA", "FEM", "BSP_LNA_SLEEP", "BSP_FEM_SLEEP", verbose)
	return xmlDevice