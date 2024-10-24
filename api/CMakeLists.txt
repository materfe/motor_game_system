file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(api ${SRC_FILES} ${HEADER_FILES})
target_include_directories(api PUBLIC include/)

add_executable(api_test
        test/test_math_circle.cc
        test/test_aabb.cc)


target_link_libraries(api PRIVATE core)
target_link_libraries(api_test PRIVATE api)

if(ENABLE_PROFILING)
    target_link_libraries(api PUBLIC Tracy::TracyClient)
    target_compile_definitions(api PUBLIC TRACY_ENABLE=1)
endif(ENABLE_PROFILING)

target_link_libraries(api_test PRIVATE core GTest::gtest GTest::gtest_main)