include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(raytracer_tests
    test_helpers.cpp
    test_greeting.cpp
    math/test_vector.cpp
    colour/test_colour.cpp
    geometry/test_ray.cpp
    render/test_camera.cpp
)
target_include_directories(raytracer_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(raytracer_tests PRIVATE raytracer_core raytracer_warnings Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(raytracer_tests)
