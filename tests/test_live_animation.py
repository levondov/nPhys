import sys
import os

# Add the build directory to the Python path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/src')))

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import nphys

# Initialize the engine and simulation settings
engine = nphys.Engine()

sim_settings = nphys.simulation_settings()
sim_settings.dt = 0.001
sim_settings.scene_width = 100
sim_settings.scene_height = 100
sim_settings.gravity_scale = 1.0
engine.initialize(sim_settings)

# Create a circle shape
circle = nphys.shape_circle(1.0)
s1 = nphys.shape(1.0, 1000.0, circle, "s1", 5, 50, 0 * 3.14 / 180, 40, 40)
s1.name = "s1"
s1.dyn.e = 0.70
engine.addShape(s1)
# Initialize data storage for the animation
xp = [s1.st.x.x[0]]
yp = [s1.st.y.x[0]]

# Create the figure and axis for the animation
fig, ax = plt.subplots(figsize=(8, 6))
line, = ax.plot([], [], 'b-', label="Trajectory")  # Line for the trajectory

# Set up the plot limits and labels
ax.set_xlim(0, sim_settings.scene_width)
ax.set_ylim(0, sim_settings.scene_height)
ax.set_title("Live Animation: Position (x vs y)")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.grid()
ax.legend()

# Animation update function
def update(frame):
    # Run the simulation for one step
    for _ in range(10):  # Skip 5 frames
        engine.run()

    # Get the current time and position
    xp.append(s1.st.x.x[0])
    yp.append(s1.st.y.x[0])

    # Update the line and point data
    line.set_data(xp, yp)

    return (line,)

# Create the animation
ani = FuncAnimation(fig, update, frames=range(5000), interval=sim_settings.dt * 1000, blit=True, repeat=False)

# Show the animation
plt.tight_layout()
plt.show()

# Shutdown the engine after the animation
engine.shutdown()