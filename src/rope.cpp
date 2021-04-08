#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass,
           float k, vector<int> pinned_nodes) {
  // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and
  // containing `num_nodes` nodes.
  //
  // New masses can be created (see mass.h):
  // Mass *m = new Mass(position, mass, bool)
  // and should be added to the masses vector.
  //
  // Springs can be created (see spring.h):
  // Spring *s = new Spring(mass_a, mass_b, spring_const)
  // and should be added to the springs vector.
  //
  // Masses corresponding to indices in pinned_nodes
  // should have their pinned field set to true.

}

void Rope::simulateEuler(float delta_t, Vector2D gravity) {
  for (auto &s : springs) {
    // TODO (Part 2.1): Use Hooke's law to calculate the force on a node

    // TODO (Part 4.1): Add damping forces

    // TODO Apply forces as appropriate.

  }

  for (auto &m : masses) {
    if (!m->pinned) {
      // TODO (Part 2.1): Add the force due to gravity, then compute the new
      // velocity and position

    }

    // TODO Reset all forces on each mass

  }
}

void Rope::simulateVerlet(float delta_t, Vector2D gravity) {
  // TODO (Part 3.1): Clear forces
  for (auto &s : springs) {
    // TODO (Part 3.1): Simulate one timestep of the rope using explicit Verlet
    
  }

  for (auto &m : masses) {
    if (!m->pinned) {
      Vector2D temp_position = m->position;

      // TODO (Part 3.1): Set the new position of the rope mass
      // TODO (Part 4.2): Add global Verlet damping

    }
  }
}
}
