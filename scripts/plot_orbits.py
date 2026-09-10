import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

# Path to the directory containing this Python script (e.g., .../Ominous Orbits/scripts)
script_dir = Path(__file__).resolve().parent

# Project root (one directory up from scripts/)
project_root = script_dir.parent

# Search candidates in order of priority:
# 1. relative to current working directory (if user runs directly alongside output)
# 2. relative to bin/ (build output folder)
# 3. relative to project root
candidate_paths = [
    Path("orbit_outputs"),
    Path("bin/orbit_outputs"),
    project_root / "bin" / "orbit_outputs",
    project_root / "orbit_outputs",
    ]

output_dir = None
for path in candidate_paths:
    if path.exists() and path.is_dir():
        output_dir = path
        break

if output_dir is None:
    raise FileNotFoundError("Could not locate an 'orbit_outputs' directory in standard execution paths.")


file_list = sorted(list(output_dir.glob("*.csv")))

if not file_list:
    raise FileNotFoundError("No CSV files found in orbit_outputs.")

latest_file = file_list[-1]
first_file = file_list[0]

print(f"Found {len(file_list)} runs. Latest run {latest_file.name}")

df = pd.read_csv(latest_file)

bodies = {body_id: group for body_id, group in df.groupby('body_id')}

sun_data = bodies[0]
earth_data = bodies[1]

plt.figure(figsize=(8, 8))
plt.plot(sun_data["pos_x"], sun_data["pos_y"], "yo-", label="Sun (Body 0)")
plt.plot(earth_data["pos_x"], earth_data["pos_y"], "b-", label="Earth (Body 1)")

plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.title(f"Orbital Trajectory: {latest_file.name}")
plt.axis("equal")
plt.grid(True)
plt.legend()

plt.show()
