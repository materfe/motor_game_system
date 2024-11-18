//
// Created by Mat on 05.11.2024.
//

#include "physic/quadtree.h"

//void quadtree::Quadtree::Insert(AABB *collider) {
//  if (collider)
//  {
//    root_->Insert(collider, kMaxShapeCount_, kMaxDepth_);
//  }
//}
//std::vector<AABB *> quadtree::Quadtree::Query(const AABB &range) const {
//  std::vector<AABB*> foundColliders;
//  root_->Query(range, foundColliders);
//  return foundColliders;
//}
//void quadtree::Quadtree::Clear() {
//  root_ = std::make_unique<quadtree::QuadNode>(root_->bounding_box());
//}
//void quadtree::Quadtree::Draw(SDL_Renderer *renderer) const {
//  root_->Draw(renderer);
//}