//
// Created by Mat on 11.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_DELTA_FOR_COLLISIONS_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_DELTA_FOR_COLLISIONS_H_

#include "physical_circle.h"
#include "physical_polygon.h"

namespace Physic {

// Project a polygon onto an axis and find the minimum and maximum values
void ProjectOntoAxis(const PhysicalPolygon &polygon, const core::Vec2<float> &axis, float &min, float &max) {
  const auto &vertices = polygon.GetVertices();

  // Project the first vertex onto the axis to initialize min and max
  min = max = axis.x_ * vertices[0].x_ + axis.y_ * vertices[0].y_;

  for (std::size_t i = 1; i < vertices.size(); ++i) {
    float projection = axis.x_ * vertices[i].x_ + axis.y_ * vertices[i].y_;
    if (projection < min) min = projection;
    if (projection > max) max = projection;
  }
}





void ResolveCollision(PhysicalCircle &circle_1, PhysicalCircle &circle_2) {
  auto position1 = circle_1.GetPosition();
  auto position2 = circle_2.GetPosition();
  auto velocity1 = circle_1.GetVelocity();
  auto velocity2 = circle_2.GetVelocity();

  // Calculate the vector between the circles' centers
  core::Vec2<float> delta = {position2.x_ - position1.x_, position2.y_ - position1.y_};

  // Normalize the delta vector to get the collision normal
  core::Vec2<float> normal = delta.Normalise();

  // Calculate the relative velocity
  core::Vec2<float> relativeVelocity = {velocity2.x_ - velocity1.x_, velocity2.y_ - velocity1.y_};
  float velocityAlongNormal = relativeVelocity.x_ * normal.x_ + relativeVelocity.y_ * normal.y_;

  // Calculate the restitution coefficient for an elastic collision (1.0 for perfect bounce)
  float restitution = 1.0f;

  // Calculate the impulse scalar
  float mass1 = circle_1.GetMass();
  float mass2 = circle_2.GetMass();
  float impulseScalar = -(1 + restitution) * velocityAlongNormal / (1 / mass1 + 1 / mass2);

  // Apply impulse to each circle
  core::Vec2<float> impulse = {impulseScalar * normal.x_, impulseScalar * normal.y_};
  circle_1.SetVelocity(
      velocity1.x_ - (impulse.x_ / mass1),
      velocity1.y_ - (impulse.y_ / mass1)
  );
  circle_2.SetVelocity(
      velocity2.x_ + (impulse.x_ / mass2),
      velocity2.y_ + (impulse.y_ / mass2)
  );
}
void ResolveCollision(PhysicalPolygon &poly_1, PhysicalPolygon &poly_2) {
  auto &vertices_1 = poly_1.GetVertices();
  auto &vertices_2 = poly_2.GetVertices();

  // Calculate the axes for SAT
  std::vector<core::Vec2<float>> axes;
  for (std::size_t i = 0; i < vertices_1.size(); ++i) {
    std::size_t next = (i + 1) % vertices_1.size();
    core::Vec2<float> edge = {vertices_1[next].x_ - vertices_1[i].x_, vertices_1[next].y_ - vertices_1[i].y_};
    axes.emplace_back(-edge.y_, edge.x_); // Normal to the edge
  }
  for (std::size_t i = 0; i < vertices_2.size(); ++i) {
    std::size_t next = (i + 1) % vertices_2.size();
    core::Vec2<float> edge = {vertices_2[next].x_ - vertices_2[i].x_, vertices_2[next].y_ - vertices_2[i].y_};
    axes.emplace_back(-edge.y_, edge.x_); // Normal to the edge
  }

  // Find the axis with the smallest overlap (penetration depth)
  float minOverlap = std::numeric_limits<float>::max();
  core::Vec2<float> collisionNormal;

  for (const auto &axis : axes) {
    float min1, max1, min2, max2;
    Physic::ProjectOntoAxis(poly_1, axis, min1, max1);
    Physic::ProjectOntoAxis(poly_2, axis, min2, max2);

    float overlap = std::min(max1, max2) - std::max(min1, min2);
    if (overlap < 0) {
      return; // No collision
    } else if (overlap < minOverlap) {
      minOverlap = overlap;
      collisionNormal = axis;
    }
  }

  // Normalize the collision normal
  float magnitude = std::sqrt(collisionNormal.x_ * collisionNormal.x_ + collisionNormal.y_ * collisionNormal.y_);
  collisionNormal.x_ /= magnitude;
  collisionNormal.y_ /= magnitude;

  // Calculate the relative velocity and apply the collision response
  auto velocity1 = poly_1.GetVelocity();
  auto velocity2 = poly_2.GetVelocity();
  core::Vec2<float> relativeVelocity = {velocity2.x_ - velocity1.x_, velocity2.y_ - velocity1.y_};

  float velocityAlongNormal = relativeVelocity.x_ * collisionNormal.x_ + relativeVelocity.y_ * collisionNormal.y_;
  if (velocityAlongNormal > 0) return; // Objects moving apart

  float restitution = 1.0f;
  float impulseScalar = -(1 + restitution) * velocityAlongNormal / (1 / poly_1.GetMass() + 1 / poly_2.GetMass());

  core::Vec2<float> impulse = {impulseScalar * collisionNormal.x_, impulseScalar * collisionNormal.y_};
  poly_1.SetVelocity(velocity1.x_ - impulse.x_ / poly_1.GetMass(), velocity1.y_ - impulse.y_ / poly_1.GetMass());
  poly_2.SetVelocity(velocity2.x_ + impulse.x_ / poly_2.GetMass(), velocity2.y_ + impulse.y_ / poly_2.GetMass());
}

void ResolveCollision(PhysicalCircle &circle, PhysicalPolygon &polygon) {
  auto circlePosition = circle.GetPosition();
  const auto &vertices = polygon.GetVertices();

  core::Vec2<float> closestPoint = vertices[0];
  float minDistance = std::numeric_limits<float>::max();

  for (std::size_t i = 0; i < vertices.size(); ++i) {
    std::size_t next = (i + 1) % vertices.size();
    core::Vec2<float> edge = {vertices[next].x_ - vertices[i].x_, vertices[next].y_ - vertices[i].y_};
    core::Vec2<float> point = vertices[i];

    // Project the circle center onto the edge
    float t = ((circlePosition.x_ - point.x_) * edge.x_ + (circlePosition.y_ - point.y_) * edge.y_) /
        (edge.x_ * edge.x_ + edge.y_ * edge.y_);
    t = std::max(0.0f, std::min(1.0f, t));

    core::Vec2<float> projection = {point.x_ + t * edge.x_, point.y_ + t * edge.y_};
    float distance = std::sqrt((circlePosition.x_ - projection.x_) * (circlePosition.x_ - projection.x_) +
        (circlePosition.y_ - projection.y_) * (circlePosition.y_ - projection.y_));

    if (distance < minDistance) {
      minDistance = distance;
      closestPoint = projection;
    }
  }

  core::Vec2<float> collisionNormal = {circlePosition.x_ - closestPoint.x_, circlePosition.y_ - closestPoint.y_};
  float magnitude = std::sqrt(collisionNormal.x_ * collisionNormal.x_ + collisionNormal.y_ * collisionNormal.y_);
  if (magnitude == 0) return;

  collisionNormal.x_ /= magnitude;
  collisionNormal.y_ /= magnitude;

  auto velocity1 = circle.GetVelocity();
  auto velocity2 = polygon.GetVelocity();
  core::Vec2<float> relativeVelocity = {velocity2.x_ - velocity1.x_, velocity2.y_ - velocity1.y_};
  float velocityAlongNormal = relativeVelocity.x_ * collisionNormal.x_ + relativeVelocity.y_ * collisionNormal.y_;

  if (velocityAlongNormal > 0) return;

  float restitution = 1.0f;
  float impulseScalar = -(1 + restitution) * velocityAlongNormal / (1 / circle.GetMass() + 1 / polygon.GetMass());

  core::Vec2<float> impulse = {impulseScalar * collisionNormal.x_, impulseScalar * collisionNormal.y_};
  circle.SetVelocity(velocity1.x_ - impulse.x_ / circle.GetMass(), velocity1.y_ - impulse.y_ / circle.GetMass());
  polygon.SetVelocity(velocity2.x_ + impulse.x_ / polygon.GetMass(), velocity2.y_ + impulse.y_ / polygon.GetMass());
}
void ResolveCollision(PhysicalPolygon &polygon, PhysicalCircle &circle) {
  ResolveCollision(circle, polygon);
}

void ResolveCollision(AABB &aabb1, AABB &aabb2) {
  auto position1 = aabb1.GetPosition();
  auto position2 = aabb2.GetPosition();
  auto velocity1 = aabb1.GetVelocity();
  auto velocity2 = aabb2.GetVelocity();

  // Calculate the vector between the circles' centers
  core::Vec2<float> delta = {position2.x_ - position1.x_, position2.y_ - position1.y_};

  // Normalize the delta vector to get the collision normal
  core::Vec2<float> normal = delta.Normalise();

  // Calculate the relative velocity
  core::Vec2<float> relativeVelocity = {velocity2.x_ - velocity1.x_, velocity2.y_ - velocity1.y_};
  float velocityAlongNormal = relativeVelocity.x_ * normal.x_ + relativeVelocity.y_ * normal.y_;

  // Calculate the restitution coefficient for an elastic collision (1.0 for perfect bounce)
  float restitution = 1.0f;

  // Calculate the impulse scalar
  float mass1 = aabb1.GetMass();
  float mass2 = aabb2.GetMass();
  float impulseScalar = -(1 + restitution) * velocityAlongNormal / (1 / mass1 + 1 / mass2);

  // Apply impulse to each circle
  core::Vec2<float> impulse = {impulseScalar * normal.x_, impulseScalar * normal.y_};
  aabb1.SetVelocity(
      velocity1.x_ - (impulse.x_ / mass1),
      velocity1.y_ - (impulse.y_ / mass1)
  );
  aabb2.SetVelocity(
      velocity2.x_ + (impulse.x_ / mass2),
      velocity2.y_ + (impulse.y_ / mass2)
  );
}
void ResolveCollision(AABB &aabb, PhysicalCircle &circle) {
  auto position1 = aabb.GetPosition();
  auto position2 = circle.GetPosition();
  auto velocity1 = aabb.GetVelocity();
  auto velocity2 = circle.GetVelocity();

  // Calculate the vector between the circles' centers
  core::Vec2<float> delta = {position2.x_ - position1.x_, position2.y_ - position1.y_};

  // Normalize the delta vector to get the collision normal
  core::Vec2<float> normal = delta.Normalise();

  // Calculate the relative velocity
  core::Vec2<float> relativeVelocity = {velocity2.x_ - velocity1.x_, velocity2.y_ - velocity1.y_};
  float velocityAlongNormal = relativeVelocity.x_ * normal.x_ + relativeVelocity.y_ * normal.y_;

  // Calculate the restitution coefficient for an elastic collision (1.0 for perfect bounce)
  float restitution = 1.0f;

  // Calculate the impulse scalar
  float mass1 = aabb.GetMass();
  float mass2 = circle.GetMass();
  float impulseScalar = -(1 + restitution) * velocityAlongNormal / (1 / mass1 + 1 / mass2);

  // Apply impulse to each circle
  core::Vec2<float> impulse = {impulseScalar * normal.x_, impulseScalar * normal.y_};
  aabb.SetVelocity(
      velocity1.x_ - (impulse.x_ / mass1),
      velocity1.y_ - (impulse.y_ / mass1)
  );
  circle.SetVelocity(
      velocity2.x_ + (impulse.x_ / mass2),
      velocity2.y_ + (impulse.y_ / mass2)
  );
}
}

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_DELTA_FOR_COLLISIONS_H_
