//
// Created by Mat on 27.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_

#include "trigger.h"
#include <unordered_set>
#include <utility>

// Helper structure for hashing a pair of AABB pointers
struct AABBPairHash {
  std::size_t operator()(const std::pair<const AABB *, const AABB *> &pair) const {
    return std::hash<const AABB *>()(pair.first) ^ std::hash<const AABB *>()(pair.second);
  }
};

class ContactListener {
 private:
  std::unordered_set<std::pair<const AABB *, const AABB *>, AABBPairHash> colliding_pairs_;

 public:
  // Method to update contacts between two AABBs
  //void updateContact(const AABB &aabb1, const AABB &aabb2, Trigger &trigger);
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_CONTACT_LISTENER_H_
