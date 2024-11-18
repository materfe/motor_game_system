//
// Created by Mat on 27.10.2024.
//

#include "physic/contact_listener.h"

void ContactListener::UpdateContact(PhysicalCircle &circle_1, PhysicalCircle &circle_2) {
  auto circle_pair = std::make_pair(&circle_1.bounds(), &circle_2.bounds());

  // Check if the two AABBs are colliding
  bool currentlyColliding = Physic::AreTwoCirclesColliding(circle_1, circle_2);

  // If currently colliding but the pair is not in the set, it’s a new collision
  if (currentlyColliding && colliding_pairs_.find(circle_pair) == colliding_pairs_.end()) {
    colliding_pairs_.insert(circle_pair); // Add the pair to the set
    circle_1.bounds().collider().OnTriggerEnter();
    circle_2.bounds().collider().OnTriggerEnter();
  }

  // If not colliding and the pair is in the set, the collision has ended
  if (!currentlyColliding && colliding_pairs_.find(circle_pair) != colliding_pairs_.end()) {
    colliding_pairs_.erase(circle_pair); // Remove the pair from the set
    circle_1.bounds().collider().OnTriggerExit();
    circle_2.bounds().collider().OnTriggerExit();
  }
}

void ContactListener::UpdateContact(PhysicalPolygon &poly_1, PhysicalPolygon &poly_2) {
  auto circle_pair = std::make_pair(&poly_1.bounds(), &poly_2.bounds());

  // Check if the two AABBs are colliding
  bool currentlyColliding = Physic::AreTwoPolygonsColliding(poly_1, poly_2);

  // If currently colliding but the pair is not in the set, it’s a new collision
  if (currentlyColliding && colliding_pairs_.find(circle_pair) == colliding_pairs_.end()) {
    colliding_pairs_.insert(circle_pair); // Add the pair to the set
    poly_1.bounds().collider().OnTriggerEnter();
    poly_2.bounds().collider().OnTriggerEnter();
  }

  // If not colliding and the pair is in the set, the collision has ended
  if (!currentlyColliding && colliding_pairs_.find(circle_pair) != colliding_pairs_.end()) {
    colliding_pairs_.erase(circle_pair); // Remove the pair from the set
    poly_1.bounds().collider().OnTriggerExit();
    poly_2.bounds().collider().OnTriggerExit();
  }
}

void ContactListener::UpdateContact(PhysicalCircle &circle, PhysicalPolygon &poly) {
  auto circle_pair = std::make_pair(&circle.bounds(), &poly.bounds());

  // Check if the two AABBs are colliding
  bool currentlyColliding = Physic::IsOnePolygonCollidingWithOneCircle(poly, circle);

  // If currently colliding but the pair is not in the set, it’s a new collision
  if (currentlyColliding && colliding_pairs_.find(circle_pair) == colliding_pairs_.end()) {
    colliding_pairs_.insert(circle_pair); // Add the pair to the set
    poly.bounds().collider().OnTriggerEnter();
    circle.bounds().collider().OnTriggerEnter();
  }

  // If not colliding and the pair is in the set, the collision has ended
  if (!currentlyColliding && colliding_pairs_.find(circle_pair) != colliding_pairs_.end()) {
    colliding_pairs_.erase(circle_pair); // Remove the pair from the set
    poly.bounds().collider().OnTriggerExit();
    circle.bounds().collider().OnTriggerExit();
  }
}

void ContactListener::UpdateContact(AABB &aabb_1, AABB &aabb_2) {
  auto circle_pair = std::make_pair(&aabb_1, &aabb_2);

  // Check if the two AABBs are colliding
  bool currentlyColliding = Physic::AreTwoAabbsColliding(aabb_1, aabb_2);

  // If currently colliding but the pair is not in the set, it’s a new collision
  if (currentlyColliding && colliding_pairs_.find(circle_pair) == colliding_pairs_.end()) {
    colliding_pairs_.insert(circle_pair); // Add the pair to the set
    aabb_1.collider().OnTriggerEnter();
    aabb_2.collider().OnTriggerEnter();
  }

  // If not colliding and the pair is in the set, the collision has ended
  if (!currentlyColliding && colliding_pairs_.find(circle_pair) != colliding_pairs_.end()) {
    colliding_pairs_.erase(circle_pair); // Remove the pair from the set
    aabb_1.collider().OnTriggerExit();
    aabb_2.collider().OnTriggerExit();
  }
}
