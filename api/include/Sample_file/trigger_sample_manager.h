//
// Created by Mat on 04.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_TRIGGER_SAMPLE_MANAGER_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_TRIGGER_SAMPLE_MANAGER_H_


#include "SDL2/SDL.h"
#include "renderer.h"
#include "window.h"
#include "physic/aabb.h"
#include "physic/physical_circle.h"
#include "physic/contact_listener.h"
#include "physic/quadtree.h"
#include <chrono>
#include <array>
#include <unordered_map>


static constexpr size_t kMaxArraySize = 10;



class TriggerCollisionEngine final {
 private:
  int window_height_ = -1;
  int window_width_ = -1; //TODO those are in window class
  bool running_ = true;

  const char *window_title_ = nullptr;
  std::array<PhysicalCircle, kMaxArraySize> circles_{};
  std::array<PhysicalPolygon, kMaxArraySize> polygons_{};
  std::array<AABB, kMaxArraySize> aabbs_{};

  Uint32 last_time_ = 0;
  Uint32 current_time_ = 0;
  Uint32 delta_time_ = 0;

  Window *window_ = nullptr;
  Renderer *renderer_ = nullptr;
  ContactListener listener_;


 public:
  // Initialize the game engine
  void Begin();
  void SetArrayForMaxElements();

  TriggerCollisionEngine(const char *title, int width, int height);

  ~TriggerCollisionEngine() {
    End();
  }

  // Main game loop
  void Update();

  // Cleanup and end the game
  void End();
  void BroadPhase(const float delta_time_sec);
  void NarrowPhase();
  void UpdateContactCircleCircle();
  void UpdateContactPolyPoly();
  void UpdateContactPolyCircle();
  void UpdateContactAABBAABB();
};


#endif //GAME_MOTOR_ENGINE_API_INCLUDE_TRIGGER_SAMPLE_MANAGER_H_
