import sys
import os
import random
import matplotlib.pyplot as plt
import matplotlib.patches as patches

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/src')))
import nphys

# --- settings ---
NUM_CIRCLES   = 100
RADIUS        = 0.25
SCENE_W       = 100.0
SCENE_H       = 100.0
DT            = 0.01
STEPS_PER_FRAME = 50

# --- engine setup ---
engine = nphys.Engine()

sim_settings = nphys.simulation_settings()
sim_settings.dt           = DT
sim_settings.scene_width  = SCENE_W
sim_settings.scene_height = SCENE_H
sim_settings.gravity_scale = 1.0

engine.initialize(sim_settings)

random.seed(42)
for _ in range(NUM_CIRCLES):
    x = random.uniform(RADIUS, SCENE_W - RADIUS)
    y = random.uniform(SCENE_H * 0.5, SCENE_H - RADIUS)
    engine.add_shape(x, y, 1.0, nphys.shape_type.Circle, RADIUS, e=0.85)

# --- plot setup ---
fig, ax = plt.subplots(figsize=(7, 7))
ax.set_xlim(0, SCENE_W)
ax.set_ylim(0, SCENE_H)
ax.set_aspect('equal')
ax.set_facecolor('#1a1a2e')
fig.patch.set_facecolor('#1a1a2e')
ax.tick_params(colors='white')
for spine in ax.spines.values():
    spine.set_edgecolor('white')

circles = [
    plt.Circle((0, 0), RADIUS, color='#00d4ff', alpha=0.85)
    for _ in range(NUM_CIRCLES)
]
for c in circles:
    ax.add_patch(c)

step_text = ax.text(0.02, 0.97, '', transform=ax.transAxes,
                    color='white', fontsize=9, va='top')

plt.ion()
plt.show()

# --- run loop ---
step = 0
while plt.fignum_exists(fig.number):
    for _ in range(STEPS_PER_FRAME):
        engine.run()
    step += STEPS_PER_FRAME

    positions = engine.get_positions()
    for i, (x, y) in enumerate(positions):
        circles[i].center = (x, y)

    step_text.set_text(f'step: {step}   t: {step * DT:.2f}s')
    fig.canvas.draw()
    fig.canvas.flush_events()

engine.shutdown()
