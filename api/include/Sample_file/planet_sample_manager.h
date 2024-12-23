﻿//
// Created by Mat on 13.10.2024.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "SDL2/SDL.h"
#include "renderer.h"
#include "window.h"
#include "planet.h"
#include <chrono>
#include <array>


constexpr static int kMaxArraySize = 100;


class PlanetSampleEngine final {
 private:
  int window_height_ = -1;
  int window_width_ = -1; //TODO those are in window class
  bool running_ = true;

  const char *window_title_ = nullptr;
  std::array<Planet, kMaxArraySize> planets_{};

  Uint32 last_time_ = 0;
  Uint32 current_time_ = 0;
  Uint32 delta_time_ = 0;

  Window *window_ = nullptr;
  Renderer *renderer_ = nullptr;

 public:
  // Initialize the game engine
  void Begin();
  void SetArrayForMaxElements();

  PlanetSampleEngine(const char *title, int width, int height);

  ~PlanetSampleEngine() {
    End();
  }

  // Main game loop
  void Update();

  // Cleanup and end the game
  void End();
};

#endif //GAME_ENGINE_H
