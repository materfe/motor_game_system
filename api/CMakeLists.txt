file(GLOB_RECURSE SRC_FILES src/*.cc samples/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h samples/*.h)

add_library(api ${SRC_FILES} ${HEADER_FILES})
target_include_directories(api PUBLIC include/)

add_executable(api_test
        test/test_collision_trigger.cc
        test/test_contact_listener.cc)

add_executable(trigger_sample samples/trigger/trigger_sample.cc)

target_link_libraries(api PRIVATE core)
target_link_libraries(api_test PRIVATE api)
target_link_libraries(trigger_sample PRIVATE api)
target_link_libraries(trigger_sample PRIVATE core)

if(ENABLE_PROFILING)
    target_link_libraries(api PUBLIC Tracy::TracyClient)
    target_compile_definitions(api PUBLIC TRACY_ENABLE=1)
endif(ENABLE_PROFILING)

target_link_libraries(api_test PRIVATE core GTest::gtest GTest::gtest_main)