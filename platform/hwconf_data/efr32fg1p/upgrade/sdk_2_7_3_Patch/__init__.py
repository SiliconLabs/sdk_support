import os
import glob

ms = glob.glob(os.path.dirname(__file__)+"/*upgrade.py")
__all__ = [os.path.relpath(f, start=os.path.dirname(__file__))[:-3].replace(os.path.sep, ".") for f in ms if os.path.isfile(f) and not os.path.basename(f).startswith('_')]
