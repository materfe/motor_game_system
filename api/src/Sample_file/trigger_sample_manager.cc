//
// Created by Mat on 04.11.2024.
//

#include "Sample_file/trigger_sample_manager.h"
#include <iostream>

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#include "tracy/TracyC.h"
#endif

void SampleEngine::SetArrayForMaxElements() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (int i = 0; i < max_array_size; i++) {
    const auto random_number_radius = common::GenerateRandomNumber(0.0f, 50.0f);
    const auto random_number_position_x = common::GenerateRandomNumber(0.0f, 800.0f);
    const auto random_number_position_y = common::GenerateRandomNumber(0.0f, 800.0f);
    const auto random_number_mass = common::GenerateRandomNumber(0.0f, 2e20f);
    const auto random_number_velocity_x = common::GenerateRandomNumber(0.0f, 200.0f);
    const auto random_number_velocity_y = common::GenerateRandomNumber(0.0f, 200.0f);
    //const auto speed_orientation = static_cast<float>(std::pow(-1, i));

    circles_[i] = PhysicalCircle(core::Vec2<float>(random_number_position_x, random_number_position_y),
        core::Vec2<float>(random_number_velocity_x, random_number_velocity_y),
            random_number_mass, random_number_radius);
  }
}

//warning because variables implemented in SetVariable other than in constructor
SampleEngine::SampleEngine(const char *title, const int width, const int height)
    : window_height_(height), window_width_(width), window_title_(title) {
#ifdef TRACY_ENABLE
  TracyCZoneN(const constructor, "contr", true)
#endif
  Begin();
  SetArrayForMaxElements();

#ifdef TRACY_ENABLE
  TracyCZoneEnd(constructor)
#endif

}

void SampleEngine::Begin() {
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

void SampleEngine::Update() {
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
    TracyCZoneN(const update, "update", true)
#endif
    // Update the circle's position
    for (auto &_ : circles_) {
      _.Update(delta_time_sec, window_width_, window_height_);
    }
    // Update the collider
    for (std::size_t i = 0; i < circles_.size(); i++) {
      for(std::size_t j = 0; j < circles_.size(); j++)
      {
        std::size_t index = (j + 1) % circles_.size();
        listener_.updateContact(circles_[i], circles_[index]);
      }
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
    for (auto &_ : circles_) {
      if(_.GetCollider().GetIsTriggerActivated())
      {
        renderer_->SetDrawColor(255, 0, 0, 255);
        renderer_->DrawCornersOfCircle(_);
      } else
      {
        renderer_->SetDrawColor(255, 255, 0, 255);
        renderer_->DrawCornersOfCircle(_);
      }
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


void SampleEngine::End() {
  std::cout << "nooooo\n";
  running_ = false;
  SDL_Quit();
}