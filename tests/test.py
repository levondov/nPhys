import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/src')))

import matplotlib.pyplot as plt
import nphys

engine= nphys.Engine()

sim_settings = nphys.simulation_settings()
sim_settings.dt = 0.001
sim_settings.scene_width = 1050
sim_settings.scene_height = 50
sim_settings.gravity_scale = 1.0

engine.initialize(sim_settings)

circle = nphys.shape_circle(1.0)

s1 = nphys.shape(1.0, 1000.0, circle, "s1", 2, 30, 0*3.14/180, 10, 10)
s1.name = "s1"
s1.dyn.e = 0.75
s2 = nphys.shape(1.0, 1.0, circle, "s1", 0, 0, 0*3.14/180, 10, 15)
s2.name = "s2"

engine.addShape(s1)
#engine.addShape(s2)
engine.run()
stime = []
xp = []
yp = []
xp1 = []
yp1 = []
fx = []
fy = []
tmax = 25
ct = 0
while ct <= tmax:
    ct = sim_settings.t
    stime.append(ct)
    xp.append(s1.st.x.x[0])
    yp.append(s1.st.y.x[0])
    fx.append(s1.dyn.fx)
    fy.append(s1.dyn.fy)
    # xp1.append(s2.st.x.x[0])
    # yp1.append(s2.st.y.x[0])
    engine.run()
engine.shutdown()

# Create a single figure with two subplots
fig, axs = plt.subplots(2, 1, figsize=(8, 6))  # 2 rows, 1 column

# First subplot: xp vs yp
axs[0].plot(xp, yp)
axs[0].plot(xp1, yp1, marker='.')
axs[0].set_title("Position (x vs y)")
axs[0].set_xlabel("x")
axs[0].set_ylabel("y")
axs[0].grid()

# # Second subplot: stime vs yp
# axs[1].plot(stime, yp, marker='.')
# axs[1].plot(stime, yp1, marker='.')
# axs[1].set_title("Time vs y")
# axs[1].set_xlabel("Time")
# axs[1].set_ylabel("y")
# axs[1].grid()

# Second subplot: stime vs yp
axs[1].plot(stime, fx, marker='.')
axs[1].plot(stime, fy, marker='.')
axs[1].grid()


# Adjust layout and show the plot
plt.tight_layout()
plt.show()