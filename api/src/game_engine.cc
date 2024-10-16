//
// Created by Mat on 13.10.2024.
//

#include "game_engine.h"

void GameEngine::SetVariablesToNothing() {
    timer = 0.0f;
    delta_time_ = 0.0f;
    last_time_ = 0.0f;
    current_time_ = 0.0f;
    window_ = nullptr;
    renderer_ = nullptr;
    running_ = true;
}

//warning because variables implemented in SetVariable other than in constructor
GameEngine::GameEngine(const char *title, const int width, const int height)
    : window_height_(height), window_width_(width), window_title_(title),
      planets_({Planet(400.0f, 300.0f, 20.0f, 30.0f, 10.0f), Planet(400.0f, 300.0f, 5.0f, 0.0f, 0.0f)}) {
    SetVariablesToNothing();
    Begin();
}


void GameEngine::Begin() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
        running_ = false;
    }

    window_ = new Window(window_title_, window_width_, window_height_);
    renderer_ = new Renderer(*window_);

    last_time_ = SDL_GetTicks();
    srand(time(nullptr));
}
void GameEngine::Update() {
    SDL_Event event;

    const auto random_color_1 = rand() % 255;
    const auto random_color_2 = rand() % 255;
    const auto random_color_3 = rand() % 255;
    while (running_) {
        current_time_ = SDL_GetTicks();
        delta_time_ = current_time_ - last_time_;
        last_time_ = current_time_;

        const float deltaTimeSec = static_cast<float>(delta_time_) / 1000.0f;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                End();
            }
        }

        // Update the circle's orbit position
        for (auto &_: planets_) {
            _.Update(deltaTimeSec); // Update circle's position based on its angular velocity
        }

        renderer_->SetDrawColor(0, 0, 0, 255); //black color
        renderer_->ClearScreen();

        // Draw the orbiting circle

        for (const auto &_: planets_) {
            renderer_->SetDrawColor(random_color_1, random_color_2, random_color_3, 255);
            renderer_->DrawPlanet(_);
        }

        renderer_->Present();
    }
}
void GameEngine::End() {
    delete renderer_;
    delete window_;
    SDL_Quit();
    running_ = false;
}

