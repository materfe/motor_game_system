//
// Created by Mat on 27.10.2024.
//

#include "Physic/contact_listener.h"

//void ContactListener::updateContact(const AABB &aabb1, const AABB &aabb2, Trigger &trigger) {
//  auto aabbPair = std::make_pair(&aabb1, &aabb2);
//
//  // Check if the two AABBs are colliding
//  bool currentlyColliding = aabb1.IsColliding(aabb2);
//
//  // If currently colliding but the pair is not in the set, it’s a new collision
//  if (currentlyColliding && colliding_pairs_.find(aabbPair) == colliding_pairs_.end()) {
//    colliding_pairs_.insert(aabbPair); // Add the pair to the set
//    trigger.TriggerEnter();           // Call TriggerEnter
//  }
//
//  // If not colliding and the pair is in the set, the collision has ended
//  if (!currentlyColliding && colliding_pairs_.find(aabbPair) != colliding_pairs_.end()) {
//    colliding_pairs_.erase(aabbPair); // Remove the pair from the set
//    trigger.TriggerExit();           // Call TriggerExit
//  }
//}