//
// Created by Mat on 13.10.2024.
//

#include "game_engine.h"

void GameEngine::SetVariablesToNothing() {
    timer = 0.0f;
    deltaTime = 0.0f;
    lastTime = 0.0f;
    currentTime = 0.0f;
    window = nullptr;
    renderer = nullptr;
    running = true;
}
GameEngine::GameEngine(const char *title, int width, int height)
    : windowHeight(height), windowWidth(width), windowTitle(title),
      planets({Planet(400.0f, 300.0f, 20.0f, 30.0f, 1.0f), Planet(400.0f, 300.0f, 5.0f, 0.0f, 0.0f)}) {
    SetVariablesToNothing();
    Begin();
}


void GameEngine::Begin() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
        running = false;
    }

    window = new Window(windowTitle, windowWidth, windowHeight);
    renderer = new Renderer(*window);

    lastTime = SDL_GetTicks();
    srand(time(nullptr));
}
void GameEngine::Update() {
    SDL_Event event;
    while (running) {
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        const float deltaTimeSec = static_cast<float>(deltaTime) / 1000.0f;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                End();
            }
        }

        // Update the circle's orbit position
        for (auto &_: planets) {
            _.Update(deltaTimeSec); // Update circle's position based on its angular velocity
        }

        renderer->SetDrawColor(0, 0, 0, 255); //black color
        renderer->ClearScreen();

        renderer->SetDrawColor(255, 245, 220, 255);
        // Draw the orbiting circle
        for (const auto &_: planets) {
            renderer->DrawPlanet(_);
        }

        renderer->Present();
    }
}
void GameEngine::End() {
    delete renderer;
    delete window;
    SDL_Quit();
    running = false;
}

