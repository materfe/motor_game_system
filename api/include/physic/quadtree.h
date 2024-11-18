//
// Created by Mat on 05.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_QUADTREE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_QUADTREE_H_

#include <SDL_render.h>
#include "physic/physical_circle.h"
#include "physic/aabb.h"
#include "intersection_manager.h"
#include <vector>
#include <array>
#include <memory>
#include <iostream>

static constexpr std::size_t kMaxObjects = 4; // Max objects before subdivision
static constexpr int kMaxLevels = 5; // Max levels of the quadtree

class QuadTree {
 private:
  int level_;                       // Current level of this node
  AABB bounds_{};                     // Region this node represents
  std::vector<PhysicalCircle *> shapes_; // Circles stored in this node

  //std::unique_ptr<QuadTree> children_[4];
  std::array<std::unique_ptr<QuadTree>, 4> children_; // Subnodes: NW, NE, SW, SE

  // Subdivides this node into 4 child nodes
  void Divide() {
    const float mid_x = (bounds_.GetMinX() + bounds_.GetMaxX()) / 2;
    const float mid_y = (bounds_.GetMinY() + bounds_.GetMaxY()) / 2;

    children_[0] = std::make_unique<QuadTree>(level_ + 1,
                                              AABB{bounds_.GetMinX(), bounds_.GetMinY(),
                                                   mid_x, mid_y}); // NW
    children_[1] = std::make_unique<QuadTree>(level_ + 1,
                                              AABB{mid_x, bounds_.GetMinY(),
                                                   bounds_.GetMaxX(), mid_y}); // NE
    children_[2] = std::make_unique<QuadTree>(level_ + 1,
                                              AABB{bounds_.GetMinX(), mid_y,
                                                   mid_x, bounds_.GetMaxY()}); // SW
    children_[3] = std::make_unique<QuadTree>(level_ + 1,
                                              AABB{mid_x, mid_y, bounds_.GetMaxX(),
                                                   bounds_.GetMaxY()}); // SE
  }
  // Determines which child node the object belongs to
  int GetIndex(PhysicalCircle &circle) const {
    AABB circle_bounds = circle.bounds();
    const float mid_x = (bounds_.GetMinX() + bounds_.GetMaxX()) / 2;
    const float mid_y = (bounds_.GetMinY() + bounds_.GetMaxY()) / 2;

    bool top = circle_bounds.GetMaxY() < mid_y;
    bool bottom = circle_bounds.GetMinY() > mid_y;
    bool left = circle_bounds.GetMaxX() < mid_x;
    bool right = circle_bounds.GetMinX() > mid_x;

    if (top && left) return 0;   // NW
    if (top && right) return 1; // NE
    if (bottom && left) return 2; // SW
    if (bottom && right) return 3; // SE

    return -1; // Object does not fit entirely within a child node
  }

 public:
  QuadTree(const int level, AABB bounds) : level_(level), bounds_(bounds) {}

  // Clears the quadtree
  void Clear() {
    shapes_.clear();
    for (std::size_t i = 0; i < children_.size(); ++i) {
      if (children_[i]) {
        children_[i]->Clear();
        children_[i] = nullptr;
      }
    }
  }

  // Inserts a circle into the quadtree
  void Insert(PhysicalCircle &circle) {
    if (children_[0]) {
      const auto index = GetIndex(circle);
      if (index != -1) {
        children_[index]->Insert(circle);
        return;
      }
    }

    shapes_.push_back(&circle);

    // Subdivide if necessary
    if (shapes_.size() > kMaxObjects && level_ < kMaxLevels) {
      if (!children_[0]) {
        Divide();
      }

      auto it = shapes_.begin();
      while (it != shapes_.end()) {
        int index = GetIndex(**it);
        if (index != -1) {
          children_[index]->Insert(**it);
          it = shapes_.erase(it);
        } else {
          ++it;
        }
      }
    }
  }

  // Retrieves all circles that might collide with a given AABB
  void Retrieve(std::vector<PhysicalCircle *> &return_objects, const AABB &range) const {
    if (!Physic::AreTwoAabbsColliding(bounds_, range)) {
      return;
    }

    for (PhysicalCircle *circle : shapes_) {
      return_objects.push_back(circle);
    }

    if (children_[0]) {
      for (std::size_t i = 0; i < children_.size(); ++i) {
        children_[i]->Retrieve(return_objects, range);
      }
    }
  }

  // Add this method to your QuadTree class
  void Draw(SDL_Renderer *renderer) const {
    // Draw the bounds of the current node
    SDL_Rect rect{
        static_cast<int>(bounds_.GetMinX()),
        static_cast<int>(bounds_.GetMinY()),
        static_cast<int>(bounds_.GetMaxX()),
        static_cast<int>(bounds_.GetMaxY())
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_RenderDrawRect(renderer, &rect);

    // Recursively draw child nodes
    if (!children_.empty()) {
      for (const auto &child : children_) {
        child->Draw(renderer);
      }
    }
  }

  //GET
  [[nodiscard]] AABB &bounds() { return bounds_; }
};
#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_QUADTREE_H_
