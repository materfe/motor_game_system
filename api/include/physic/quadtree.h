//
// Created by Mat on 05.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_QUADTREE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_QUADTREE_H_

#include "physical_circle.h"
#include "aabb.h"
#include <vector>
#include <memory>
#include <algorithm>


// Define a maximum number of circles per quad_tree_ node before subdividing
static constexpr int MAX_CIRCLES_PER_NODE = 4;
static constexpr int MAX_DEPTH = 5; // Maximum quad_tree_ depth to prevent infinite subdivisions

class Quadtree {
 private:
  int level_;                  // Current level of the quad_tree_ node
  AABB bounds_;                // Bounds of this node
  std::vector<PhysicalCircle*> objects_; // Circles in this node
  std::vector<std::unique_ptr<Quadtree>> children_; // Child nodes

  // Subdivide this node into four child nodes
  void Subdivide();

  // Determine which quadrant the circle belongs to
  int GetIndex(PhysicalCircle* circle) const;


 public:
  Quadtree(int level, const AABB& bounds)
      : level_(level), bounds_(bounds) {}

  // Insert a circle into the quad_tree_
  void Insert(PhysicalCircle* circle);

  // Retrieve all circles that might collide with the given circle
  void Retrieve(std::vector<PhysicalCircle*>& returnObjects, PhysicalCircle* circle);

  // Clear the quad_tree_ (for reuse in each frame)
  void Clear();
};


#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_QUADTREE_H_
