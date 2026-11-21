include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(raytracer_tests test_greeting.cpp math/test_vector.cpp)
target_link_libraries(raytracer_tests PRIVATE raytracer_core raytracer_warnings Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(raytracer_tests)
