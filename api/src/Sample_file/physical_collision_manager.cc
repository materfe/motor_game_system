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

// Initialize variables for tracking FPS
static int frameCount = 0;
static double fps = 0.0;
static auto startTime = std::chrono::high_resolution_clock::now();


// Call this function in your main loop to update and display FPS
static void calculateFPS() {
  // Increment the frame counter
  frameCount++;

  // Get the current time
  auto currentTime = std::chrono::high_resolution_clock::now();

  // Calculate the duration (in seconds) since the last FPS calculation
  std::chrono::duration<double> elapsedTime = currentTime - startTime;

  // If a second has passed, update the FPS and reset counters
  if (elapsedTime.count() >= 1.0) {
    fps = frameCount / elapsedTime.count();  // Calculate FPS
    frameCount = 0;                          // Reset frame counter
    startTime = currentTime;                 // Reset start time

    // Display the FPS (or store it as needed)
    std::cout << "FPS: " << fps << std::endl;
  }
}

void CollisionSampleEngine::SetArrayForMaxElements() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  for (int i = 0; i < max_array_size; i++) {
    //const auto random_number_radius = common::GenerateRandomNumber(5.0f, 50.0f);
    const auto random_number_position_x = common::GenerateRandomNumber(0.0f, 1150.0f);
    const auto random_number_position_y = common::GenerateRandomNumber(0.0f, 800.0f);
    //const auto random_number_mass = common::GenerateRandomNumber(0.0f, 2e20f);
    const auto random_number_velocity_x = common::GenerateRandomNumber(0.0f, 200.0f);
    const auto random_number_velocity_y = common::GenerateRandomNumber(0.0f, 200.0f);
    const auto speed_orientation = static_cast<float>(std::pow(-1, i));

    circles_[i] = PhysicalCircle(core::Vec2<float>(random_number_position_x, random_number_position_y),
                                 core::Vec2<float>(random_number_velocity_x * speed_orientation, random_number_velocity_y),
                                 1e10f, 5.0f);
  }
}

//warning because variables implemented in SetVariable other than in constructor
CollisionSampleEngine::CollisionSampleEngine(const char *title, const int width, const int height)
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
    calculateFPS();


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
  const auto temporary = std::array<uint16_t, 3>{200, 0, 160};
  for (auto &_ : circles_) {
    renderer_->DrawFullCircle(_, temporary);
  }
}

void CollisionSampleEngine::BroadPhase(const float delta_time_sec) {// Update the circle's position
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
        if(Physic::AreTwoCirclesColliding(circles_[i], circles_[index]))
        {
          Physic::ResolveCollision(circles_[i], circles_[index]);
        }
      }
    }
  }
}

void CollisionSampleEngine::End()
{
  running_ = false;
  SDL_Quit();
}