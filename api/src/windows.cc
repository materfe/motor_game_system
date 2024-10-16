﻿//
// Created by Mat on 02.10.2024.
//
#include <iostream>
#include "window.h"

Window::Window(const char *title, const int width, const int height) {
    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}

Window::~Window() {
    SDL_DestroyWindow(window_);
}
