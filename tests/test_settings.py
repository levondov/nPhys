import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/src')))

import nphys

engine= nphys.Engine()

sim_settings = nphys.simulation_settings()
sim_settings.dt = 0.001
sim_settings.scene_width = 100
sim_settings.scene_height = 100
sim_settings.gravity_scale = 1.0

engine.initialize(sim_settings)
