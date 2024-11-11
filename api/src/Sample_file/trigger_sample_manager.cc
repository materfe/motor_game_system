//
// Created by Mat on 04.11.2024.
//

#include <iostream>
#include "Sample_file/trigger_sample_manager.h"
#include "physic/delta_for_collisions.h"

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#include "tracy/TracyC.h"
#endif

void TriggerCollisionEngine::SetArrayForMaxElements() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (int i = 0; i < max_array_size; i++) {
    const auto random_number_radius = common::GenerateRandomNumber(5.0f, 50.0f);
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
TriggerCollisionEngine::TriggerCollisionEngine(const char *title, const int width, const int height)
    : window_height_(height), window_width_(width), window_title_(title){
#ifdef TRACY_ENABLE
  TracyCZoneN(const constructor, "contr", true)
#endif
  Begin();
  SetArrayForMaxElements();

#ifdef TRACY_ENABLE
  TracyCZoneEnd(constructor)
#endif

}

void TriggerCollisionEngine::Begin() {
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

void TriggerCollisionEngine::Update() {
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

    BroadPhase(delta_time_sec);



    renderer_->SetDrawColor(0, 0, 0, 255); //black color
    renderer_->ClearScreen();

    // DrawFullPlanet the orbiting circle
    NarrowPhase();


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
void TriggerCollisionEngine::NarrowPhase() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  for (auto &_ : circles_) {
    if (_.GetCollider().GetIsTriggerActivated()) {
      renderer_->SetDrawColor(255, 0, 0, 255);
      renderer_->DrawCornersOfCircle(_);
    } else {
      renderer_->SetDrawColor(255, 255, 0, 255);
      renderer_->DrawCornersOfCircle(_);
    }
  }
}

void TriggerCollisionEngine::BroadPhase(const float delta_time_sec) {// Update the circle's position
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (auto &_ : circles_) {
    _.Update(delta_time_sec, window_width_, window_height_);
  }

  // Update the collider
  for (size_t i = 0; i < circles_.size(); i++) {
    for (size_t j = 0; j < circles_.size(); j++) {
      if (j != i - 1) {
        size_t index = (j + 1) % circles_.size();
        listener_.updateContact(circles_[i], circles_[index]);
//        if(Physic::AreTwoCirclesColliding(circles_[i], circles_[index]))
//        {
//          Physic::ResolveCollision(circles_[i], circles_[index]);
//        }
      }
    }
  }
}

void TriggerCollisionEngine::End() {
  running_ = false;
  SDL_Quit();
}