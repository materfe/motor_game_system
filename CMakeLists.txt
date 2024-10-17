cmake_minimum_required(VERSION 3.17)
project(game_motor_engine)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMAKE_PREFIX_PATH to help CMake find SDL2
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/vcpkg/vcpkg/installed/x64-windows/share/sdl2")

# Enable testing and find necessary packages
enable_testing()
find_package(GTest CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

#profiler
if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

#subdirectories
add_subdirectory(core/)
add_subdirectory(api/)

# Store SDL2 libraries in a variable
set(SDL2_LIBRARIES
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

# Link SDL2 libraries and include directories to the api library
target_link_libraries(api PUBLIC ${SDL2_LIBRARIES})

# Add SDL2 include directories to api
if(NOT SDL2_INCLUDE_DIRS)
    get_target_property(SDL2_INCLUDE_DIRS SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
endif()

target_include_directories(api PUBLIC ${SDL2_INCLUDE_DIRS})

#main
add_executable(main main.cc)

add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/vcpkg/vcpkg/installed/x64-windows/bin/SDL2.dll"
        $<TARGET_FILE_DIR:main>
)

#if(MSVC)
#    # Force to always compile with W4
#    if(CMAKE_CXX_FLAGS MATCHES "/W[3]")
#        string(REGEX REPLACE "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#    else()
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3" "/WX")
#    endif()
#elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
#    # Update if necessary
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
#endif()

# Link core and api libraries to the main executable
target_link_libraries(main PRIVATE api core)
target_link_libraries(main PRIVATE imgui::imgui)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)