//
// Created by Mat on 13.10.2024.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>
#include "renderer.h"
#include "window.h"
#include "planet.h"
#include <chrono>
#include <array>


constexpr static int max_array_size = 1000;


class GameEngine {
 private:
  int window_height_;
  int window_width_;
  bool running_;

  const char *window_title_;
  std::array<Planet, max_array_size> planets_;

  Uint32 last_time_;
  Uint32 current_time_;
  Uint32 delta_time_;

  Window *window_;
  Renderer *renderer_;

 public:
  // Initialize the game engine
  void Begin();
  void SetVariablesToNothing();
  void SetArrayForMaxElements();

  GameEngine(const char *title, int width, int height);

  ~GameEngine() {
    End();
  }

  // Main game loop
  void Update();

  // Cleanup and end the game
  void End();
};

#endif //GAME_ENGINE_H
