import random
import ecosim
import matplotlib.pyplot as plt
import matplotlib.animation as animation

GRID_SIZE = 150
NUM_HERBS = 50
Ttime = 250

# how often (in steps) to capture a frame for the gif — capturing every
# single step for 250 steps makes a huge/slow gif, so we thin it out
GIF_FRAME_STRIDE = 2

# Create a 300x300 grid, growth rate/carrying capacity are hardcoded in C++ for now
grid = ecosim.Grid(GRID_SIZE, 0)

# Create 50 herbivores at random positions scattered across the grid
# NOTE: size must match the grid size (300) or bounds-checking will be wrong
herbs = [
    ecosim.Herb(
        random.randint(0, GRID_SIZE - 1),
        random.randint(0, GRID_SIZE - 1),
        i,
        GRID_SIZE,
    )
    for i in range(NUM_HERBS)
]

# Track each herb's position/energy/alive status over time
history = {h.get_id(): {"x": [], "y": [], "energy": [], "alive": []} for h in herbs}

snapshots = []
snapshot_steps = [0, Ttime // 2 - Ttime//4, Ttime // 2 ,Ttime // 2 + Ttime//4 , Ttime]

# frames captured for the gif: each is (step_num, grid_data)
gif_frames = []

for step_num in range(Ttime + 1):
    if step_num in snapshot_steps:
        snapshots.append((step_num, grid.get_grid()))

    if step_num % GIF_FRAME_STRIDE == 0:
        gif_frames.append((step_num, grid.get_grid()))

    # record state, then step each herb, then step the grid
    for h in herbs:
        history[h.get_id()]["x"].append(h.get_x())
        history[h.get_id()]["y"].append(h.get_y())
        history[h.get_id()]["energy"].append(h.get_energy())
        history[h.get_id()]["alive"].append(h.is_alive())
        h.step(grid)

    grid.step()

# --- Plot 1: vegetation heatmaps with herb positions overlaid ---
fig, axes = plt.subplots(1, len(snapshots), figsize=(40, 9))

for ax, (step_num, data) in zip(axes, snapshots):
    im = ax.imshow(data, cmap="Greens", vmin=0, vmax=1)
    ax.set_title(f"Step {step_num}")
    ax.axis("off")

    # overlay each herb's position at this step, if still alive
    for hid, h in history.items():
        if step_num < len(h["alive"]) and h["alive"][step_num]:
            ax.plot(h["y"][step_num], h["x"][step_num], "o", color="red", markersize=3)

fig.colorbar(im, ax=axes, shrink=0.6, label="Vegetation density")
plt.savefig("output/growth_test.png")
plt.show()

# --- Plot 2: energy over time per herb ---
fig2, ax2 = plt.subplots(figsize=(8, 4))
for hid, h in history.items():
    ax2.plot(h["energy"], label=f"Herb {hid}")

ax2.set_xlabel("Step")
ax2.set_ylabel("Energy")
ax2.set_title("Herbivore energy over time")
# 50 herbs would make a legend unreadable, so it's dropped — see note below
plt.savefig("output/energy_test.png")
plt.show()

# --- Plot 3: animated gif of the simulation ---
fig3, ax3 = plt.subplots(figsize=(6, 6))

first_step, first_data = gif_frames[0]
im3 = ax3.imshow(first_data, cmap="Greens", vmin=0, vmax=1)
title3 = ax3.set_title(f"Step {first_step}")
ax3.axis("off")

# separate scatter plot for herb dots, updated each frame
scatter3 = ax3.scatter([], [], color="red", s=10)


def update(frame_idx):
    step_num, data = gif_frames[frame_idx]
    im3.set_data(data)
    title3.set_text(f"Step {step_num}")

    xs, ys = [], []
    for hid, h in history.items():
        if step_num < len(h["alive"]) and h["alive"][step_num]:
            xs.append(h["y"][step_num])
            ys.append(h["x"][step_num])
    scatter3.set_offsets(list(zip(xs, ys)) if xs else [])

    return im3, title3, scatter3


ani = animation.FuncAnimation(
    fig3, update, frames=len(gif_frames), interval=100, blit=False
)
ani.save("output/simulation.gif", writer="pillow", fps=10)
plt.show()
