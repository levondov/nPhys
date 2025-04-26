import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/src')))

import nphys

engine= nphys.Engine()
stophere()
engine.initialize()

engine.run()

engine.shutdown()