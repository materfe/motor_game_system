//
// Created by Mat on 11.11.2024.
//

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

#include "Sample_file/physical_collision_manager.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
#ifdef TRACY_ENABLE
  TracyCZoneN(game_engine_setup, "game_engine_setup", true)
#endif
  CollisionSampleEngine Engine("Trigger Simulation", 1200, 800);
#ifdef TRACY_ENABLE
  TracyCZoneEnd(game_engine_setup)
#endif

#ifdef TRACY_ENABLE
  TracyCZoneN(game_engine_update, "game_engine_update", true)
#endif

  Engine.Update();

#ifdef TRACY_ENABLE
  TracyCZoneEnd(game_engine_setup)
#endif
  return 0;
}