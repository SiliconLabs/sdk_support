import os
import glob

ms = glob.glob(os.path.dirname(__file__)+"/*/*.py")
__all__ = ["upgrade."+os.path.relpath(os.path.dirname(f), start=os.path.dirname(__file__)).replace(os.path.sep, ".") for f in ms if os.path.isfile(f) and not os.path.basename(f).startswith('_')]
