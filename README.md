# Rope Simulation

In this discussion, you will be creating a simplified version of the upcoming cloth simulation project.

## Part 1: Linking the Rope Constraints (10 mins)

In `rope.cpp`, implement the Rope constructor. It should create a new `Rope` object starting at `start` and ending at `end`, containing `num_nodes` nodes. That is, something along the following diagram:

```
Rope(start, end, 3, ...)

  O------------O-------------O
  ^                          ^
start                       end
```

The nodes at the indices specified by `pinned_nodes` should have their `pinned` attribute set to `true`. Make sure to pass along the `node_mass` constant into the `Mass` constructor, and `k` into the `Spring` constructor. You should be creating a new `Mass` object for each node in the rope, and link together adjacent pairs of `Mass` objects with `Spring` objects.

Run `./ropesim`. You should see the rope drawn to the screen.

## Part 2: Explicit Euler (15 mins)

Hooke's law states that the force on two points along a spring is proportional to their distance. That is,

![](http://quicklatex.com/cache3/bf/ql_1d79c5f0195b3fb81b7aa300358ccfbf_l3.png)

$$f_{a\rightarrowb} = -k_s\frac{b - a}{||b - a||^2} (||b - a|| - l)$$

In `Rope::simulateEuler`, first implement Hooke's law. Iterate over all the springs and apply the correct spring force to the mass on either end of the spring. Ensure that the force is pointing in the correct direction! Accumulate all forces due to springs in the `forces` attribute of each `Mass`.

Once all the spring forces have been computed, apply the laws of physics to each particle:

```
F = ma
v(t+1) = v(t) + a(t) * dt
x(t+1) = x(t) + v(t) * dt
```

### Part 2.2

Run `./ropesim`. Your simulation should start running, but as it only has 3 nodes, it doesn't look like much. At the top of `application.cpp`, you should see where the Euler and Verlet ropes are defined. Change the 3 value for the number of nodes to a higher constant like 16 for both ropes. What happens?

Run `./ropesim -s 32` to set the simulation to use a different number of simulation steps per frame. Try small values and large values (default is 64). What happens?

## Part 3: Explicit Verlet (15 mins)

Verlet is a different way of ensuring that all constraints are dealt with accurately. The benefit to this approach is that the simulation is handled entirely through the positions of the vertices in the simulation, and it remains fourth-order accurate! Unlike Euler, Verlet integration follows the following rule to calculate the next position in the simulation:

```
x(t+1) = 2 * x(t) - x(t-1) + a(t) * dt * dt
```

In addition, we can now emulate springs with an infinite spring constant. Instead of bothering with spring forces, we simply move each mass's position such that the springs are set back to their rest length. The correction vector should be proportional to the displacement between the two masses and in the direction between one mass and the other. Each mass should move by half the displacement.

As long as we do this for every pair of springs, the simulation should approach stability. Additional rounds of simulations may be necessary to make the motion smoother.

## Part 4: Damping (10 mins)

### Part 4.1

Add damping to Hooke's law in explicit Euler. In a spring-damper system, an additional damping force is applied (springs in real life don't continue bouncing forever - energy is lost to friction). The damping force is proportional to the relative velocity of the two particles. Use a damping constant of 0.5.

### Part 4.2

```
x(t+1) = (2 - damping_factor) * x(t) - x(t-1) + a(t) * dt * dt
```

where 0 < damping_factor < 1. Small damping factors work better (~0.0005), otherwise the simulation becomes overdamped and uninteresting.
