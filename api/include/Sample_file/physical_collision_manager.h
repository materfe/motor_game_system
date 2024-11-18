//
// Created by Mat on 11.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_SAMPLE_FILE_PHYSICAL_COLLISION_MANAGER_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_SAMPLE_FILE_PHYSICAL_COLLISION_MANAGER_H_

#include "SDL2/SDL.h"
#include "renderer.h"
#include "window.h"
#include "physic/aabb.h"
#include "physic/physical_circle.h"
#include "physic/contact_listener.h"
#include <chrono>
#include <array>


static constexpr std::size_t kMaxArraySize = 100;


class CollisionSampleEngine final {
 private:
  int window_height_ = -1;
  int window_width_ = -1; //TODO those are in window class
  bool running_ = true;

  const char *window_title_ = nullptr;
  std::array<PhysicalCircle, kMaxArraySize> circles_{};
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

  CollisionSampleEngine(const char *title, int width, int height);

  ~CollisionSampleEngine() {
    End();
  }

  // Main game loop
  void Update();

  // Cleanup and end the game
  void End();
  void BroadPhase(const float delta_time_sec);
  void NarrowPhase();
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_SAMPLE_FILE_PHYSICAL_COLLISION_MANAGER_H_
