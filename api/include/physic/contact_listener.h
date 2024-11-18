//
// Created by Mat on 27.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_

#include "intersection_manager.h"
#include <unordered_set>
#include <utility>

// Helper structure for hashing a pair of AABB pointers
struct PairHash {
  std::size_t operator()(const std::pair<const AABB *, const AABB *> &pair) const {
    return std::hash<const AABB *>()(pair.first) ^ std::hash<const AABB *>()(pair.second);
  }
};

class ContactListener {
 private:
  std::unordered_set<std::pair<const AABB *, const AABB *>, PairHash> colliding_pairs_;

 public:
  // Method to update contacts between two AABBs
  void UpdateContact(PhysicalCircle &circle_1, PhysicalCircle &circle_2);
  void UpdateContact(PhysicalPolygon &poly_1, PhysicalPolygon &poly_2);
  void UpdateContact(PhysicalCircle &circle, PhysicalPolygon &poly);
  void UpdateContact(AABB &aabb_1, AABB &aabb_2);


  //GET
  [[nodiscard]] std::unordered_set<std::pair<const AABB *, const AABB *>, PairHash> GetSet() const
  {return colliding_pairs_;};
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_
