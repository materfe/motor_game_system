#include <SDL2/SDL.h>
#include <iostream>
#include <vector>


// Structure pour représenter un cercle
struct Circle {
    int x, y; // Position du centre
    int radius; // Rayon du cercle
    float dx, dy; // Vitesse en X et Y
    float gravity; // Accélération due à la gravité
    float bounce; // Coefficient de restitution (rebond)
};

// Fonction pour dessiner un cercle
void DrawCircle(SDL_Renderer *renderer, const Circle &circle) {
    int offsetX = 0;
    int offsetY = circle.radius;
    int d = 1 - circle.radius;

    auto DrawPixel = [renderer](int x, int y) {
        SDL_RenderDrawPoint(renderer, x, y);
    };

    auto DrawCirclePoints = [DrawPixel, circle](int dx, int dy) {
        DrawPixel(circle.x + dx, circle.y + dy);
        DrawPixel(circle.x - dx, circle.y + dy);
        DrawPixel(circle.x + dx, circle.y - dy);
        DrawPixel(circle.x - dx, circle.y - dy);
        DrawPixel(circle.x + dy, circle.y + dx);
        DrawPixel(circle.x - dy, circle.y + dx);
        DrawPixel(circle.x + dy, circle.y - dx);
        DrawPixel(circle.x - dy, circle.y - dx);
    };

    DrawCirclePoints(offsetX, offsetY);

    while (offsetX < offsetY) {
        if (d < 0) {
            d += 2 * offsetX + 3;
        } else {
            d += 2 * (offsetX - offsetY) + 5;
            --offsetY;
        }
        ++offsetX;
        DrawCirclePoints(offsetX, offsetY);
    }
}

int time1 = 0;

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur d'initialisation de SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Créer une fenêtre
    SDL_Window* window = SDL_CreateWindow(
        "Fenêtre SDL2 avec Cercle Physique",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        std::cerr << "Erreur de création de la fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }



    // SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    //
    // if (!window_surface) {
    //     std::cout << "Failed to get the surface from the window\n";
    //     return -1;
    // }

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);


    // Créer un renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Erreur de création du renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Créer un vecteur pour stocker plusieurs cercles
    std::vector<Circle> circles = {
        {400, 300, 20, 0, 0, 0.0f, 0.8f},
        {200, 150, 20, 0, 0, 10.2f, 0.8f},
        {600, 450, 20, 0, 0, 10.2f, 0.8f},
        {300, 400, 20, 0, 0, 10.2f, 0.8f}
    };


    Uint32 lastTime = SDL_GetTicks(); // Temps de début de la boucle principale
    Uint32 currentTime, deltaTime;

    // Boucle principale
    bool running = true;
    SDL_Event event;
    while (running) {
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Convertir deltaTime en secondes
        // float deltaTimeSec = deltaTime / 1000.0f;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // // Mise à jour de la physique pour chaque cercle
        // for (auto &circle: circles) {
        //     circle.dy += circle.gravity * deltaTimeSec;
        //     circle.x += static_cast<int>(circle.dx * deltaTimeSec);
        //     circle.y += static_cast<int>(circle.dy * deltaTimeSec);
        //
        //     // Gestion des collisions avec le bas de la fenêtre
        //     if (circle.y + circle.radius > 600) {
        //         circle.y = 600 - circle.radius;
        //         circle.dy = -circle.dy * circle.bounce;
        //     }
        // }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner chaque cercle
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Couleur
        for (const auto &circle: circles) {
            DrawCircle(renderer, circle);
        }

        // Afficher le rendu
        SDL_RenderPresent(renderer);

        //std::cout << time1 << "\n";
        //time1++;
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
