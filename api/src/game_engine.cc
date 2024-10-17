//
// Created by Mat on 13.10.2024.
//

#include "game_engine.h"
#include <iostream>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

void GameEngine::SetVariablesToNothing() {
  delta_time_ = 0.0f;
  last_time_ = 0.0f;
  current_time_ = 0.0f;
  window_ = nullptr;
  renderer_ = nullptr;
  running_ = true;
}

void GameEngine::SetArrayForMaxElements() {
  for (int i = 0; i < max_array_size; i++) {
    const auto random_number_radius = common::GenerateAFloatNumber(50.0f);
    const auto random_number_orbit_radius = common::GenerateAFloatNumber(200.0f);
    const auto speed_orientation = static_cast<float>(std::pow(-1, i));

    planets_[i] = Planet(600.0f, 400.0f, random_number_radius,
                         random_number_orbit_radius, 800.0f * speed_orientation);
  }
}

//warning because variables implemented in SetVariable other than in constructor
GameEngine::GameEngine(const char *title, const int width, const int height)
    : window_height_(height), window_width_(width), window_title_(title), planets_() {
#ifdef TRACY_ENABLE
  TracyCZoneN(const constructor, "contr", true)
#endif
  SetVariablesToNothing();
  Begin();
  SetArrayForMaxElements();

#ifdef TRACY_ENABLE
  TracyCZoneEnd(constructor)
#endif

}

void GameEngine::Begin() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

#ifdef TRACY_ENABLE
  TracyCZoneN(const init, "sdl_make_window", true)
#endif
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
    running_ = false;
  }
#ifdef TRACY_ENABLE
  TracyCZoneEnd(init)
#endif

#ifdef TRACY_ENABLE
  TracyCZoneN(const set_alocations, "news", true)
#endif
//TODO : this take a lot of time -> optimisation ?
  window_ = new Window(window_title_, window_width_, window_height_);
  renderer_ = new Renderer(*window_);
#ifdef TRACY_ENABLE
  TracyCZoneEnd(set_alocations)
#endif

  last_time_ = SDL_GetTicks();
}

void GameEngine::Update() {
  SDL_Event event;

  while (running_) {

    current_time_ = SDL_GetTicks();
    delta_time_ = current_time_ - last_time_;
    last_time_ = current_time_;

    const float delta_time_sec = static_cast<float>(delta_time_) / 1000.0f;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        End();
      }
    }

#ifdef TRACY_ENABLE
    TracyCZoneN(const update, "planets_update", true)
#endif
    // Update the circle's orbit position
    for (auto &_ : planets_) {
      _.Update(delta_time_sec); // Update circle's position based on its angular velocity
    }
#ifdef TRACY_ENABLE
    TracyCZoneEnd(update)
#endif

#ifdef TRACY_ENABLE
    TracyCZoneN(const clear, "set_draw+clear", true)
#endif

    renderer_->SetDrawColor(0, 0, 0, 255); //black color
    renderer_->ClearScreen();
#ifdef TRACY_ENABLE
    TracyCZoneEnd(clear)
#endif

    // DrawFullPlanet the orbiting circle

#ifdef TRACY_ENABLE
    TracyCZoneN(const draw, "draw", true)
#endif
    for (const auto &_ : planets_) {
      renderer_->SetDrawColor(static_cast<Uint8>(_.getColor()[0]),
                              static_cast<Uint8>(_.getColor()[1]),
                              static_cast<Uint8>(_.getColor()[2]),
                              255);
      //renderer_->DrawCornersOfPlanet(_);
      renderer_->DrawFullPlanets(_);
    }
#ifdef TRACY_ENABLE
    TracyCZoneEnd(draw)
#endif

#ifdef TRACY_ENABLE
    TracyCZoneN(const present, "present", true)
#endif
    renderer_->Present(); //completely normal if it is long -> its SDL2 that does it

#ifdef TRACY_ENABLE
    TracyCZoneEnd(present)
#endif

#ifdef TRACY_ENABLE
    FrameMark;
#endif
  }
}
void GameEngine::End() {
  running_ = false;
  SDL_Quit();
}

