//
// Created by Mat on 27.10.2024.
//

#include "physic/contact_listener.h"

void ContactListener::updateContact(PhysicalCircle &circle_1, PhysicalCircle &circle_2) {
  auto circle_pair = std::make_pair(&circle_1, &circle_2);

  // Check if the two AABBs are colliding
  bool currentlyColliding = Physic::AreTwoCirclesColliding(circle_1, circle_2);

  // If currently colliding but the pair is not in the set, it’s a new collision
  if (currentlyColliding && colliding_pairs_.find(circle_pair) == colliding_pairs_.end()) {
    colliding_pairs_.insert(circle_pair); // Add the pair to the set
    circle_1.GetCollider().OnTriggerEnter();
    circle_2.GetCollider().OnTriggerEnter();
  }

  // If not colliding and the pair is in the set, the collision has ended
  if (!currentlyColliding && colliding_pairs_.find(circle_pair) != colliding_pairs_.end()) {
    colliding_pairs_.erase(circle_pair); // Remove the pair from the set
    circle_1.GetCollider().OnTriggerExit();
    circle_2.GetCollider().OnTriggerExit();
  }
}