﻿//
// Created by Mat on 04.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_TRIGGER_SAMPLE_MANAGER_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_TRIGGER_SAMPLE_MANAGER_H_


#include "SDL2/SDL.h"
#include "renderer.h"
#include "window.h"
#include "Physic/aabb.h"
#include "Physic/physical_circle.h"
#include "Physic/contact_listener.h"
#include "Physic/quadtree.h"
#include <chrono>
#include <array>


constexpr static int max_array_size = 10;


class SampleEngine final {
 private:
  int window_height_ = -1;
  int window_width_ = -1; //TODO those are in window class
  bool running_ = true;

  const char *window_title_ = nullptr;
  std::array<PhysicalCircle, max_array_size> circles_{};

  Uint32 last_time_ = 0;
  Uint32 current_time_ = 0;
  Uint32 delta_time_ = 0;

  Window *window_ = nullptr;
  Renderer *renderer_ = nullptr;
  ContactListener listener_;
  AABB world_bounds_;
  Quadtree quad_tree_;

 public:
  // Initialize the game engine
  void Begin();
  void SetArrayForMaxElements();

  SampleEngine(const char *title, int width, int height);

  ~SampleEngine() {
    End();
  }

  // Main game loop
  void Update();

  // Cleanup and end the game
  void End();
};


#endif //GAME_MOTOR_ENGINE_API_INCLUDE_TRIGGER_SAMPLE_MANAGER_H_