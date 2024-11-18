//
// Created by Mat on 11.11.2024.
//

#include "Sample_file/physical_collision_manager.h"
#include "physic/delta_for_collisions.h"
#include <iostream>

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#include "tracy/TracyC.h"
#endif

using Vec2f = core::Vec2<float>;

void CollisionSampleEngine::SetArrayForMaxElements() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (int i = 0; i < kMaxArraySize; i++) {
    //const auto random_number_radius = common::GenerateRandomNumber(0.0f, 5.0f);
    const auto random_number_position_x = common::GenerateRandomNumber(100.0f, 500.0f);
    const auto random_number_position_y = common::GenerateRandomNumber(100.0f, 500.0f);
    const auto random_number_mass = common::GenerateRandomNumber(1.0f, 200.0f);
    const auto random_number_velocity_x = common::GenerateRandomNumber(-200.0f, 200.0f);
    const auto random_number_velocity_y = common::GenerateRandomNumber(-200.0f, 200.0f);

    const auto random_number_min_aabb_bound_x = common::GenerateRandomNumber(1.0f, 2.0f);
    const auto random_number_min_aabb_bound_y = common::GenerateRandomNumber(1.0f, 2.0f);
    const auto random_number_max_aabb_bound_x = common::GenerateRandomNumber(10.0f, 15.0f);
    const auto random_number_max_aabb_bound_y = common::GenerateRandomNumber(10.0f, 15.0f);

    circles_[i] = PhysicalCircle(Vec2f(random_number_position_x, random_number_position_y),
                                 Vec2f(random_number_velocity_x, random_number_velocity_y),
                                 random_number_mass, 5.0f);

    aabbs_[i] = AABB(Vec2f(random_number_min_aabb_bound_x, random_number_min_aabb_bound_y),
                     Vec2f(random_number_max_aabb_bound_x, random_number_max_aabb_bound_y),
                     Vec2f(random_number_velocity_x, random_number_velocity_y), random_number_mass);
  }
}

//warning because variables implemented in SetVariable other than in constructor
CollisionSampleEngine::CollisionSampleEngine(const char *title, const int width, const int height)
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

void CollisionSampleEngine::Begin() {
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

void CollisionSampleEngine::Update() {
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
void CollisionSampleEngine::NarrowPhase() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  const auto circle_color = std::array<uint16_t, 3>{200, 0, 160};
  const auto aabb_color = std::array<uint16_t, 3>{0, 255, 255};
  for (auto &_ : circles_) {
    renderer_->DrawFullCircle(_, circle_color);
  }
  for (auto &_ : aabbs_) {
    renderer_->DrawAABB(_, aabb_color);
  }
}

void CollisionSampleEngine::BroadPhase(const float delta_time_sec) {// Update the circle's position
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (auto &_ : circles_) {
    _.Update(delta_time_sec, window_width_, window_height_);
  }
  for (auto &_ : aabbs_) {
    _.Update(delta_time_sec / 2.0f, window_width_, window_height_);
  }

  // Update the collider
  for (size_t i = 0; i < circles_.size(); i++) {
    for (size_t j = i + 1; j < circles_.size(); j++) {
      if (Physic::AreTwoCirclesColliding(circles_[i], circles_[j])) {
        Physic::ResolveCollision(circles_[i], circles_[j]);
      }
    }
  }

  for (size_t i = 0; i < aabbs_.size(); i++) {
    for (size_t j = i + 1; j < aabbs_.size(); j++) {
      if (Physic::AreTwoAabbsColliding(aabbs_[i], aabbs_[j])) {
        Physic::ResolveCollision(aabbs_[i], aabbs_[j]);
      }
    }
  }

  for (size_t i = 0; i < aabbs_.size(); i++) {
    for (size_t j = 0; j < circles_.size(); j++) {
      if (Physic::IsOneCircleCollidingWithOneAabb(circles_[i], aabbs_[j])) {
        Physic::ResolveCollision(aabbs_[j], circles_[i]);
      }
    }
  }
}

void CollisionSampleEngine::End() {
  running_ = false;
  SDL_Quit();
}