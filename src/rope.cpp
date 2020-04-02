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

  Vector2D offset = (end - start) / (num_nodes - 1);

  for (int i = 0; i < num_nodes; i++) {
    Vector2D position = start + (i * offset);
    Mass *m = new Mass(position, node_mass, false);

    masses.push_back(m);
    if (i > 0) {
      Spring *s = new Spring(m, masses[i - 1], k);
      springs.push_back(s);
    }
  }

  for (auto &i : pinned_nodes) {
    masses[i]->pinned = true;
  }
}

void Rope::simulateEuler(float delta_t, Vector2D gravity) {
  for (auto &s : springs) {
    // TODO (Part 2.1): Use Hooke's law to calculate the force on a node

    Vector2D diff = s->m2->position - s->m1->position;
    float displacement = diff.norm() - s->rest_length;

    Vector2D spring_force = displacement * s->k * diff.unit();

    // TODO (Part 4.1): Add damping forces

    // Vector2D relative_velocity = s->m2->velocity - s->m1->velocity;
    // Vector2D damping_force = 0.02 * relative_velocity;

    s->m1->forces += spring_force;
    s->m2->forces -= spring_force;

    // s->m1->forces += spring_force + damping_force;
    // s->m2->forces -= spring_force - damping_force;
  }

  for (auto &m : masses) {
    if (!m->pinned) {
      // TODO (Part 2.1): Add the force due to gravity, then compute the new
      // velocity and position

      m->velocity += (m->forces / m->mass + gravity) * delta_t;
      m->position += m->velocity * delta_t;
    }

    // Reset all forces on each mass

    m->forces = Vector2D(0, 0);
  }
}

void Rope::simulateVerlet(float delta_t, Vector2D gravity) {
  for (auto &s : springs) {
    // TODO (Part 3.1): Simulate one timestep of the rope using explicit
    // Verlet

    Vector2D diff = s->m2->position - s->m1->position;
    float displacement = diff.norm() - s->rest_length;

    // Move each mass by the half displacement

    if (!s->m1->pinned) {
      s->m1->position += diff.unit() * 0.5 * displacement;
    }
    if (!s->m2->pinned) {
      s->m2->position -= diff.unit() * 0.5 * displacement;
    }
  }

  for (auto &m : masses) {
    if (!m->pinned) {
      Vector2D temp_position = m->position;

      // TODO (Part 3.1): Set the new position of the rope mass
      // TODO (Part 4.2): Add global Verlet damping

      m->position +=
          (m->position - m->last_position) + gravity * delta_t * delta_t;

      m->last_position = temp_position;
    }
  }
}
}
