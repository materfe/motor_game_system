#include "api/include/game_engine.h"





int main(int argc, char* argv[]) {
    GameEngine gameEngine("Orbit Simulation", 1200, 800);
    gameEngine.Update();
    return 0;
}
