//
// Created by Mat on 04.11.2024.
//

#include "Sample_file/trigger_sample_manager.h"
#include <iostream>
#include <set>

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#include "tracy/TracyC.h"
#endif

using Vec2f = core::Vec2<float>;

static const void SetVertices(std::vector<core::Vec2<float>> &vertices) {
  vertices = {core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 80.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 80.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 90.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 0.0f),
                                common::GenerateRandomNumber(0.0f, 80.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 80.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 70.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 20.0f)),
              core::Vec2<float>(common::GenerateRandomNumber(0.0f, 50.0f),
                                common::GenerateRandomNumber(0.0f, 30.0f))};
}

void TriggerCollisionEngine::SetArrayForMaxElements() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (int i = 0; i < kMaxArraySize; i++) {
    const auto random_number_radius = common::GenerateRandomNumber(5.0f, 50.0f);
    const auto random_number_position_x = common::GenerateRandomNumber(0.0f, 20.0f);
    const auto random_number_position_x_2 = common::GenerateRandomNumber(20.0f, 40.0f);
    const auto random_number_position_y = common::GenerateRandomNumber(0.0f, 20.0f);
    const auto random_number_position_y_2 = common::GenerateRandomNumber(20.0f, 40.0f);
    const auto random_number_mass = common::GenerateRandomNumber(0.0f, 2e20f);
    const auto random_number_velocity_x = common::GenerateRandomNumber(-200.0f, 200.0f);
    const auto random_number_velocity_y = common::GenerateRandomNumber(-200.0f, 200.0f);
    //const auto speed_orientation = static_cast<float>(std::pow(-1, i));

    circles_[i] = PhysicalCircle(Vec2f(random_number_position_x, random_number_position_y),
                                 Vec2f(random_number_velocity_x, random_number_velocity_y),
                                 random_number_mass, random_number_radius);
    std::vector<core::Vec2<float>> vertices{};
    SetVertices(vertices);
    polygons_[i] =
        PhysicalPolygon(core::Vec2<float>(random_number_velocity_x, random_number_velocity_y), random_number_mass,
                        vertices);

    aabbs_[i] = AABB(Vec2f(random_number_position_x, random_number_position_y),
                     Vec2f(random_number_position_x_2, random_number_position_y_2),
                     Vec2f(random_number_velocity_x, random_number_velocity_y));
  }
}

//warning because variables implemented in SetVariable other than in constructor
TriggerCollisionEngine::TriggerCollisionEngine(const char *title, const int width, const int height)
    : window_height_(height),
      window_width_(width),
      window_title_(title) {
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

  //quadtree_->Draw(&renderer_->renderer());
  std::array<uint16_t, 3> red_color{255, 0, 0};
  std::array<uint16_t, 3> normal_color{255, 255, 0};
  for (auto &_ : circles_) {
    if (_.bounds().collider().is_trigger()) {
      renderer_->DrawFullCircle(_, red_color);
    } else {
      renderer_->DrawFullCircle(_, normal_color);
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
  UpdateContactCircleCircle();
}

void TriggerCollisionEngine::UpdateContactPolyCircle() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  for (std::size_t i = 0; i < circles_.size(); i++) {
    for (std::size_t j = 0; j < polygons_.size(); j++) {
      listener_.UpdateContact(circles_[i], polygons_[j]);
    }
  }
}

void TriggerCollisionEngine::UpdateContactPolyPoly() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  for (std::size_t i = 0; i < polygons_.size(); i++) {
    for (std::size_t j = i + 1; j < polygons_.size(); j++) {  // j starts from i + 1 for unique pairs
      listener_.UpdateContact(polygons_[i], polygons_[j]);
    }
  }
}

void TriggerCollisionEngine::UpdateContactCircleCircle() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  for (std::size_t i = 0; i < circles_.size(); i++) {
    for (std::size_t j = i + 1; j < circles_.size(); j++) {
      listener_.UpdateContact(circles_[i], circles_[j]);
    }
  }
}

void TriggerCollisionEngine::UpdateContactAABBAABB() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  for (std::size_t i = 0; i < aabbs_.size(); i++) {
    for (std::size_t j = i + 1; j < aabbs_.size(); j++) {
      listener_.UpdateContact(aabbs_[i], aabbs_[j]);
    }
  }
}

void TriggerCollisionEngine::End() {
  running_ = false;
  SDL_Quit();
}