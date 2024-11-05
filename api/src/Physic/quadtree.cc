//
// Created by Mat on 05.11.2024.
//

#include "physic/quadtree.h"

void Quadtree::Subdivide() {
  float halfWidth = (bounds_.GetMaxX() - bounds_.GetMinX()) / 2.0f;
  float halfHeight = (bounds_.GetMaxY() - bounds_.GetMinY()) / 2.0f;
  float x = bounds_.GetMinX();
  float y = bounds_.GetMinY();

  children_.emplace_back(std::make_unique<Quadtree>(level_ + 1, AABB(x, y, x + halfWidth, y + halfHeight))); // Top left
  children_.emplace_back(std::make_unique<Quadtree>(level_ + 1, AABB(x + halfWidth, y, x + 2 * halfWidth, y + halfHeight))); // Top right
  children_.emplace_back(std::make_unique<Quadtree>(level_ + 1, AABB(x, y + halfHeight, x + halfWidth, y + 2 * halfHeight))); // Bottom left
  children_.emplace_back(std::make_unique<Quadtree>(level_ + 1, AABB(x + halfWidth, y + halfHeight, x + 2 * halfWidth, y + 2 * halfHeight))); // Bottom
}

int Quadtree::GetIndex(PhysicalCircle *circle) const {
  const auto& pos = circle->GetPosition();
  const float verticalMidpoint = bounds_.GetMinX() + (bounds_.GetMaxX() - bounds_.GetMinX()) / 2.0f;
  const float horizontalMidpoint = bounds_.GetMinY() + (bounds_.GetMaxY() - bounds_.GetMinY()) / 2.0f;

  // Circle fits within the top or bottom quadrants
  bool topQuadrant = (pos.y_ - circle->GetRadius() >= bounds_.GetMinY() && pos.y_ + circle->GetRadius() < horizontalMidpoint);
  bool bottomQuadrant = (pos.y_ - circle->GetRadius() >= horizontalMidpoint && pos.y_ + circle->GetRadius() < bounds_.GetMaxY());

  // Circle fits within the left or right quadrants
  if (pos.x_ + circle->GetRadius() < verticalMidpoint) {
    if (topQuadrant) return 0; // Top left
    if (bottomQuadrant) return 2; // Bottom left
  } else if (pos.x_ - circle->GetRadius() >= verticalMidpoint) {
    if (topQuadrant) return 1; // Top right
    if (bottomQuadrant) return 3; // Bottom right
  }

  // Circle does not fit within any single quadrant
  return -1;
}

void Quadtree::Insert(PhysicalCircle *circle) {
  // If we have subdivided, try to insert into children
  if (!children_.empty()) {
    int index = GetIndex(circle);
    if (index != -1) {
      children_[index]->Insert(circle);
      return;
    }
  }

  // Add the circle to this node
  objects_.push_back(circle);

  // If we exceed the capacity and haven't hit max depth, subdivide
  if (objects_.size() > MAX_CIRCLES_PER_NODE && level_ < MAX_DEPTH) {
    if (children_.empty()) {
      Subdivide();
    }

    // Move circles to children if possible
    auto it = objects_.begin();
    while (it != objects_.end()) {
      int index = GetIndex(*it);
      if (index != -1) {
        children_[index]->Insert(*it);
        it = objects_.erase(it);
      } else {
        ++it;
      }
    }
  }
}

void Quadtree::Retrieve(std::vector<PhysicalCircle *> &returnObjects, PhysicalCircle *circle) {
  int index = GetIndex(circle);
  if (index != -1 && !children_.empty()) {
    children_[index]->Retrieve(returnObjects, circle);
  }

  // Add all objects in this node to the list
  returnObjects.insert(returnObjects.end(), objects_.begin(), objects_.end());
}

void Quadtree::Clear() {
  objects_.clear();
  for (auto& child : children_) {
    if (child) {
      child->Clear();
    }
  }
  children_.clear();
}