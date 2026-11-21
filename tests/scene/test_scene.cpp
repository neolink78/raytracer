#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>
#include <optional>

#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "scene/scene.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

static const Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
static const Material red(Colour(1, 0, 0));
static const Material blue(Colour(0, 0, 1));

TEST_CASE("the nearest hit wins even when its shape was added last") {
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));
    scene.add(std::make_unique<Plane>(Vector(0, 0, 2), Vector(0, 0, -1), blue));

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(0, 0, 1));
}

TEST_CASE("the nearest hit wins when its shape was added first") {
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));
    scene.add(std::make_unique<Plane>(Vector(0, 0, 20), Vector(0, 0, -1), blue));

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    requireColoursEqual(hit->material.colour(), Colour(1, 0, 0));
}

TEST_CASE("a ray that misses every shape hits nothing") {
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, red));

    REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}

TEST_CASE("the scene keeps the direction to the light as a unit vector") {
    Scene scene(Vector(0, 3, -4));

    requireVectorsEqual(scene.toLight(), Vector(0, 0.6, -0.8));
}
