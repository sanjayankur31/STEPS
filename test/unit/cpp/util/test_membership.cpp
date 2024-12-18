#include <algorithm>
#include <list>
#include <vector>

#include "util/collections.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace steps::util;  // NOLINT

// global arrays for test data

float X[] = {5, 3, 1, 2, 4, 6, 5, 7, 2, 3};
float E[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

#define ARRSZ(a) (sizeof(a) / sizeof((a)[0]))
constexpr int n_X = ARRSZ(X);
constexpr int n_E = ARRSZ(E);

bool M[n_E] = {false, false, false, true, true, true, true, true, true, true, false};


TEST_CASE("Membership_SimpleScalar") {
    auto v = map_membership(E, X);
    REQUIRE(std::equal(v.begin(), v.end(), std::begin(M)));
}

TEST_CASE("Membership_MixedContainers") {
    std::vector<float> x_vec(std::begin(X), std::end(X));
    std::list<float> e_list(std::begin(E), std::end(E));

    auto v = map_membership(e_list, x_vec);
    REQUIRE(std::equal(v.begin(), v.end(), std::begin(M)));
}

TEST_CASE("Membership_ImplicitConversion") {
    double dbl_x[n_X];
    std::copy(std::begin(X), std::end(X), std::begin(dbl_x));

    auto v = map_membership(E, dbl_x);
    REQUIRE(std::equal(v.begin(), v.end(), std::begin(M)));
}

TEST_CASE("Membership_CustomHash") {
    int silly_hash_count = 0;

    auto v = map_membership(E, X, [&silly_hash_count](float) -> size_t {
        return ++silly_hash_count, 0;
    });
    REQUIRE(std::equal(v.begin(), v.end(), std::begin(M)));

    REQUIRE(silly_hash_count > 0);
}
