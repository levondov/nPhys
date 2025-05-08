import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/src')))

import matplotlib.pyplot as plt
import nphys

engine= nphys.Engine()

sim_settings = nphys.simulation_settings()
sim_settings.dt = 0.001
sim_settings.scene_width = 100
sim_settings.scene_height = 100
sim_settings.gravity_scale = 1.0

engine.initialize(sim_settings)

circle = nphys.shape_circle(1.0)

s1 = nphys.shape(1.0, 1000.0, circle, "s1", 2, 85, 0*3.14/180, 13, 10)
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
fx = []
fy = []
vx = []
vy = []
tmax = 30
ct = 0
while ct <= tmax:
    ct = sim_settings.t
    stime.append(ct)
    xp.append(s1.st.x.x[0])
    yp.append(s1.st.y.x[0])
    fx.append(s1.dyn.fx)
    fy.append(s1.dyn.fy)
    vx.append(s1.st.x.xd[0])
    vy.append(s1.st.y.xd[0])
    engine.run()
engine.shutdown()

# Create a single figure with two subplots
fig, axs = plt.subplots(1, 1, figsize=(6, 6))  # 2 rows, 1 column

# First subplot: xp vs yp
axs.plot(xp, yp)
axs.set_title("Position (x vs y)")
axs.set_xlabel("x")
axs.set_ylabel("y")
axs.grid()
axs.set_xlim(0, sim_settings.scene_width)
axs.set_ylim(0, sim_settings.scene_height)
plt.tight_layout()
plt.show()

# Create a single figure with two subplots
fig, axs = plt.subplots(3, 1, figsize=(8, 6))  # 2 rows, 1 column

# First subplot: xp vs yp
# axs[0].plot(xp, yp)
# axs[0].set_title("Position (x vs y)")
# axs[0].set_xlabel("x")
# axs[0].set_ylabel("y")
# axs[0].grid()
# axs[0].set_xlim(0, sim_settings.scene_width)
# axs[0].set_ylim(0, sim_settings.scene_height)

# Second subplot: stime vs yp
axs[1].plot(stime, fx, marker='.')
axs[1].plot(stime, fy, marker='.')
axs[1].grid()
axs[1].set_ylim(0, 100000)

# Second subplot: stime vs yp
axs[2].plot(stime, vx, marker='.')
axs[2].plot(stime, vy, marker='.')
axs[2].grid()
axs[2].set_ylim(-100, 100)

# Adjust layout and show the plot
plt.tight_layout()
plt.show()