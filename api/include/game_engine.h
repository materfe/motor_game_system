//
// Created by Mat on 13.10.2024.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <imgui_internal.h>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Window.h"
#include "planet.h"
#include <iostream>
#include <chrono>
#include <array>

class GameEngine {
private:
    int windowHeight;
    int windowWidth;
    float timer;
    bool running;

    const char *windowTitle;
    std::array<Planet, 2> planets;

    Uint32 lastTime;
    Uint32 currentTime;
    Uint32 deltaTime;

    Window *window;
    Renderer *renderer;

public:
    void SetVariablesToNothing();

    GameEngine(const char *title, int width, int height);

    ~GameEngine() {
        End();
    }

    // Initialize the game engine
    void Begin();

    // Main game loop
    void Update();

    // Cleanup and end the game
    void End();
};


#endif //GAME_ENGINE_H
