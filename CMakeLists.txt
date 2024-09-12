cmake_minimum_required(VERSION 3.17)
project(game_motor_engine)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest CONFIG REQUIRED)

#profiler
if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)
add_subdirectory(api/)

add_executable(main main.cc)
target_link_libraries(main PRIVATE api core)


option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)