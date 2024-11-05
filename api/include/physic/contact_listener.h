//
// Created by Mat on 27.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_

#include "intersection_manager.h"
#include <unordered_set>
#include <utility>

// Helper structure for hashing a pair of AABB pointers
struct CirclesPairHash {
  std::size_t operator()(const std::pair<const PhysicalCircle *, const PhysicalCircle *> &pair) const {
    return std::hash<const PhysicalCircle *>()(pair.first) ^ std::hash<const PhysicalCircle *>()(pair.second);
  }
};

class ContactListener {
 private:
  std::unordered_set<std::pair<const PhysicalCircle *, const PhysicalCircle *>, CirclesPairHash> colliding_pairs_;

 public:
  // Method to update contacts between two AABBs
  void updateContact(PhysicalCircle &circle_1, PhysicalCircle &circle_2);


  //GET
  [[nodiscard]] std::unordered_set<std::pair<const PhysicalCircle *, const PhysicalCircle *>, CirclesPairHash> GetSet() const
  {return colliding_pairs_;};
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_
