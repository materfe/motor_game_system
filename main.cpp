#include <chrono>
#include <imgui_internal.h>
#include "circle.h"
#include "renderer.h"
#include "window.h"
#include <iostream>
#include <vector>
#include "common.h"
#include <random>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window window("Window", 800, 600);
    const renderer renderer(window);

    // Create a vector to store multiple circles
    std::vector<circle> circles = {
        {400, 300, 20, 0, 0, 0.0f, 0.8f},
        {200, 150, 20, 0, 0, 10.2f, 0.8f},
        {600, 450, 80, 0, 0, 10.2f, 0.8f},
        {300, 400, 20, 0, 0, 10.2f, 0.8f}
    };

    std::vector<rectangle> rectangles = {
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

    // ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    // ImGui_ImplSDLRenderer2_Init(renderer);

    srand(time(NULL));
    float timer = 0.0f;

    while (running) {
        currentTime = SDL_GetTicks();
        const auto time_laped_in_seconds = currentTime / 1000;
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
        deltaTime = 0;

        if(static_cast<int>(timer) % 2) {
            // Draw each circle
            renderer.SetDrawColor(llllll, llllli, lllllr, 255);
        }
        //drawing
        for (const auto& circle : circles) {
            renderer.DrawCircle(circle);
        }
        if(static_cast<int>(timer) % 2) {
            renderer.SetDrawColor(llllle, llllls, llllld, 255);
        }

        //std::cout << "timer : [" << timer << "]\n";
        //std::cout << "delta : [" << currentTime / 1000 << "]\n";
        // if(timer >= 2) {
        //     timer = 0.0f;
        // }
        timer += static_cast<float>(time_laped_in_seconds);

        for (const auto& rec : rectangles) {
            renderer.DrawRectangle(rec);
        }
        func();

        // Start the Dear ImGui frame
        // ImGui_ImplSDLRenderer2_NewFrame();
        // ImGui_ImplSDL2_NewFrame();
        // ImGui::NewFrame();
        //
        // ImGui::Begin("Splash Online");
        // //...
        // //ImGui::End();
        //
        // ImGui::Render();
        // ImGuiIO& io = ImGui::GetIO();
        // SDL_RenderSetScale(renderer,
        //     io.DisplayFramebufferScale.x,
        //     io.DisplayFramebufferScale.y);
        // //Update screen
        // ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);


        // Present the rendered frame
        renderer.Present();
    }

    SDL_Quit();
    return 0;
}
