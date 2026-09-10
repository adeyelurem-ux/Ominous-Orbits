# Ominous Orbits

A modular 3D N-body orbital physics simulator built in C++20 and SDL3. This project is an exercise in numerical integration schemes, gravitational mechanics, and decoupled software architecture.

<img width="800" height="741" alt="ominous orbits gif 2" src="https://github.com/user-attachments/assets/9d016162-0973-4043-aaf1-4c7a2d5d02b9" />


---

## Technical Overview

The framework uses an object-oriented architecture designed to decouple physical state computation from rendering pipelines:

* **`World` (Coordinator):** Manages celestial body states (`position`, `velocity`, `acceleration`) and orchestrates pairwise force calculations and numerical time-stepping.
* **`GravField` (Gravitational Physics):** Evaluates vector acceleration fields acting on target bodies using Newton's Law of Universal Gravitation:
  Evaluating the gravitational field acceleration vector:

$$
\mathbf{a}_i = -G \sum_{j \neq i} m_j \frac{\mathbf{r}_i - \mathbf{r}_j}{\|\mathbf{r}_i - \mathbf{r}_j\|^3}
$$

where $\mathbf{r}_i$ and $\mathbf{r}_j$ represent body positions in 3D space.
* **`Renderer2D` (Visualisation):** A lightweight graphics layer using SDL3 primitives. Reads world state data independently to enable simple "plug-and-play" visualisers.

---

## Numerical Integration: Why Velocity Verlet?

When simulating $1/r^2$ gravitational systems over many orbital periods, choosing the correct numerical integrator is critical to prevent artificial orbital decay or system expansion:

| Integrator | Symplectic? | Local Error Order | Energy Conservation |
| :--- | :---: | :---: | :--- |
| **Explicit Euler** | No | $O(\Delta t)$ | Rapid energy gain (orbits spiral outward) |
| **Runge-Kutta 4 (RK4)** | No | $O(\Delta t^4)$ | Accurate short-term, secular drift over long durations |
| **Symplectic Euler** | Yes | $O(\Delta t)$ | Bounded energy, but lower accuracy per step |
| **Velocity Verlet** | **Yes** | $\mathbf{O(\Delta t^2)}$ | **Bounded energy & time-reversible accuracy** |

* **Symplecticity:** Standard Runge-Kutta methods are non-symplectic and slowly leak or inject energy into orbital systems over extended simulations.
* **Accuracy vs. Complexity:** Velocity Verlet offers second-order quadratic error $O(\Delta t^2)$ compared to Symplectic Euler's first-order linear error $O(\Delta t)$, delivering long-term orbital stability without requiring multiple expensive force evaluations per step (unlike RK4).

---

## Matplotlib Visualisation

There is now a python visualisation script, which using `matplotlib` and `pandas` to interpret collected data from the CSV Logger. This can be activated by installing the dependencies on `requirements.txt` and building with the `BUILD_PLOTTING_TOOLS` option on. You can do this by entering:

```bash
cmake -B build -DBUILD_PLOTTING_TOOLS=ON
cmake --build build --target plot
```
---

## Build Requirements

* **Language Standard:** C++20
* **Build System:** CMake 3.20+
* **Dependencies:** SDL3

```bash
# Clone repository
git clone [https://github.com/adeyelurem-ux/Ominous-Orbits.git](https://github.com/adeyelurem-ux/Ominous-Orbits.git)
cd Ominous-Orbits

# Configure and build
cmake -B build
cmake --build build
