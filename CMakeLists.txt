#setup
cmake_minimum_required(VERSION 3.17)
project(game_motor_engine)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMAKE_PREFIX_PATH to help CMake find SDL2
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/vcpkg/vcpkg/installed/x64-windows/share/sdl2")

#enable test and packages
enable_testing()
find_package(GTest CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

#profiler
if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

#subdirectories
add_subdirectory(core/)
add_subdirectory(api/)

#main
add_executable(main main.cc)

add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/vcpkg/vcpkg/installed/x64-windows/bin/SDL2.dll"
        $<TARGET_FILE_DIR:main>
)

#target links
target_link_libraries(main PRIVATE api core)
target_link_libraries(main
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)