#include "Circle.h"
#include "Renderer.h"
#include "Window.h"
#include <iostream>
#include <vector>
#include <random>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
        return -1;
    }

    Window window("Window", 800, 600);
    const Renderer renderer(window);

    // Create a vector to store multiple circles
    std::vector<Circle> circles = {
        {400, 300, 20, 0, 0, 0.0f, 0.8f},
        {200, 150, 20, 0, 0, 10.2f, 0.8f},
        {600, 450, 80, 0, 0, 10.2f, 0.8f},
        {300, 400, 20, 0, 0, 10.2f, 0.8f}
    };

    std::vector<Rectangle> rectangles = {
        {0, 300, 27, 15, 0, 0.0f, 0.8f},
        {250, 150, 200, 50, 0, 10.2f, 0.8f},
        {580, 450, 80, 80, 0, 10.2f, 0.8f},
        {100, 400, 24, 83, 0, 10.2f, 0.8f}
    };

    Uint32 lastTime = SDL_GetTicks(); // Time at the beginning of the main loop
    Uint32 currentTime, deltaTime;

    // Main loop
    bool running = true;
    SDL_Event event;

    srand(time(NULL));
    while (running) {
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        const float deltaTimeSec = static_cast<float>(deltaTime) / 1000.0f; // Convert to seconds

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update physics for each circle
        for (auto& circle : circles) {
            circle.Update(deltaTimeSec, 600); // Update each circle's physics
        }


        const auto llllll = rand() % (255);
        const auto llllli = rand() % (255);
        const auto lllllr = rand() % (255);
        const auto llllle = rand() % (255);
        const auto llllls = rand() % (255);
        const auto llllld = rand() % (255);

        renderer.SetDrawColor(0,0,0,255);
        // Clear the screen
        renderer.ClearScreen();


        const auto time = deltaTime / 1000;
        if(time % 2) {
            // Draw each circle
            renderer.SetDrawColor(llllll, llllli, lllllr, 255);
        }
        //drawing
        for (const auto& circle : circles) {
            renderer.DrawCircle(circle);
        }
        if(time % 2) {

            renderer.SetDrawColor(llllle, llllls, llllld, 255);

        }

        for (const auto& rec : rectangles) {
            renderer.DrawRectangle(rec);
        }


        // Present the rendered frame
        renderer.Present();
    }

    SDL_Quit();
    return 0;
}
