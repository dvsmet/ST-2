// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include <limits>

#include "circle.h"
#include "tasks.h"

namespace {
constexpr double kPi = 3.141592653589793238462643383279502884;
constexpr double kEps = 1e-9;
}  // namespace

TEST(Circle, ConstructorSetsRadiusAndRecalculates) {
  Circle c(2.0);
  EXPECT_NEAR(c.getRadius(), 2.0, kEps);
  EXPECT_NEAR(c.getFerence(), 2.0 * kPi * 2.0, kEps);
  EXPECT_NEAR(c.getArea(), kPi * 4.0, kEps);
}

TEST(Circle, DefaultConstructorCreatesZeroCircle) {
  Circle c;
  EXPECT_NEAR(c.getRadius(), 0.0, kEps);
  EXPECT_NEAR(c.getFerence(), 0.0, kEps);
  EXPECT_NEAR(c.getArea(), 0.0, kEps);
}

TEST(Circle, SetRadiusUpdatesFerenceAndArea) {
  Circle c;
  c.setRadius(5.5);
  EXPECT_NEAR(c.getRadius(), 5.5, kEps);
  EXPECT_NEAR(c.getFerence(), 2.0 * kPi * 5.5, kEps);
  EXPECT_NEAR(c.getArea(), kPi * 5.5 * 5.5, kEps);
}

TEST(Circle, SetRadiusZeroMakesAllZero) {
  Circle c(10.0);
  c.setRadius(0.0);
  EXPECT_NEAR(c.getRadius(), 0.0, kEps);
  EXPECT_NEAR(c.getFerence(), 0.0, kEps);
  EXPECT_NEAR(c.getArea(), 0.0, kEps);
}

TEST(Circle, SetFerenceUpdatesRadiusAndArea) {
  Circle c;
  c.setFerence(10.0);
  const double r = 10.0 / (2.0 * kPi);
  EXPECT_NEAR(c.getFerence(), 10.0, kEps);
  EXPECT_NEAR(c.getRadius(), r, kEps);
  EXPECT_NEAR(c.getArea(), kPi * r * r, kEps);
}

TEST(Circle, SetFerenceZeroMakesAllZero) {
  Circle c(10.0);
  c.setFerence(0.0);
  EXPECT_NEAR(c.getFerence(), 0.0, kEps);
  EXPECT_NEAR(c.getRadius(), 0.0, kEps);
  EXPECT_NEAR(c.getArea(), 0.0, kEps);
}

TEST(Circle, SetAreaUpdatesRadiusAndFerence) {
  Circle c;
  c.setArea(50.0);
  const double r = std::sqrt(50.0 / kPi);
  EXPECT_NEAR(c.getArea(), 50.0, kEps);
  EXPECT_NEAR(c.getRadius(), r, kEps);
  EXPECT_NEAR(c.getFerence(), 2.0 * kPi * r, kEps);
}

TEST(Circle, SetAreaZeroMakesAllZero) {
  Circle c(10.0);
  c.setArea(0.0);
  EXPECT_NEAR(c.getArea(), 0.0, kEps);
  EXPECT_NEAR(c.getRadius(), 0.0, kEps);
  EXPECT_NEAR(c.getFerence(), 0.0, kEps);
}

TEST(Circle, SetRadiusThenSetFerenceKeepsConsistency) {
  Circle c;
  c.setRadius(1.0);
  c.setFerence(2.0 * kPi * 3.0);
  EXPECT_NEAR(c.getRadius(), 3.0, kEps);
  EXPECT_NEAR(c.getArea(), kPi * 9.0, kEps);
}

TEST(Circle, SetFerenceThenSetAreaKeepsConsistency) {
  Circle c;
  c.setFerence(2.0 * kPi * 2.0);
  c.setArea(kPi * 16.0);
  EXPECT_NEAR(c.getRadius(), 4.0, kEps);
  EXPECT_NEAR(c.getFerence(), 2.0 * kPi * 4.0, kEps);
}

TEST(Circle, NegativeRadiusThrows) {
  Circle c;
  EXPECT_THROW(c.setRadius(-1.0), std::invalid_argument);
}

TEST(Circle, NegativeFerenceThrows) {
  Circle c;
  EXPECT_THROW(c.setFerence(-1.0), std::invalid_argument);
}

TEST(Circle, NegativeAreaThrows) {
  Circle c;
  EXPECT_THROW(c.setArea(-1.0), std::invalid_argument);
}

TEST(Circle, NaNRadiusThrows) {
  Circle c;
  EXPECT_THROW(c.setRadius(std::numeric_limits<double>::quiet_NaN()),
               std::invalid_argument);
}

TEST(Circle, InfinityAreaThrows) {
  Circle c;
  EXPECT_THROW(c.setArea(std::numeric_limits<double>::infinity()),
               std::invalid_argument);
}

TEST(Tasks, EarthRopeGapDefaultIsAddedLengthOverTwoPi) {
  const double gap = earthRopeGapMeters();
  const double expected = 1.0 / (2.0 * kPi);
  EXPECT_NEAR(gap, expected, 1e-9);
}

TEST(Tasks, EarthRopeGapDoesNotDependOnEarthRadius) {
  const double g1 = earthRopeGapMeters(6378.1, 1.0);
  const double g2 = earthRopeGapMeters(10.0, 1.0);
  EXPECT_NEAR(g1, g2, 1e-9);
}

TEST(Tasks, EarthRopeGapZeroAddedLengthIsZero) {
  EXPECT_NEAR(earthRopeGapMeters(6378.1, 0.0), 0.0, 1e-12);
}

TEST(Tasks, EarthRopeGapInvalidArgumentsThrow) {
  EXPECT_THROW(earthRopeGapMeters(-1.0, 1.0), std::invalid_argument);
  EXPECT_THROW(earthRopeGapMeters(1.0, -1.0), std::invalid_argument);
}

TEST(Tasks, PoolCostsDefaultMatchesStatement) {
  const PoolCosts c = poolCosts();
  const double expected_area = kPi * (4.0 * 4.0 - 3.0 * 3.0);
  const double expected_concrete = expected_area * 1000.0;
  const double expected_fence = (2.0 * kPi * 4.0) * 2000.0;
  EXPECT_NEAR(c.concrete_cost, expected_concrete, 1e-9);
  EXPECT_NEAR(c.fence_cost, expected_fence, 1e-9);
  EXPECT_NEAR(c.total_cost, expected_concrete + expected_fence, 1e-9);
}

TEST(Tasks, PoolCostsZeroTrackWidthHasZeroConcreteCost) {
  const PoolCosts c = poolCosts(3.0, 0.0, 1000.0, 2000.0);
  EXPECT_NEAR(c.concrete_cost, 0.0, 1e-9);
  EXPECT_NEAR(c.fence_cost, 2.0 * kPi * 3.0 * 2000.0, 1e-9);
  EXPECT_NEAR(c.total_cost, c.fence_cost, 1e-9);
}

TEST(Tasks, PoolCostsCustomPricesScaleLinearly) {
  const PoolCosts c = poolCosts(3.0, 1.0, 10.0, 20.0);
  const double expected_area = kPi * (4.0 * 4.0 - 3.0 * 3.0);
  const double expected_concrete = expected_area * 10.0;
  const double expected_fence = (2.0 * kPi * 4.0) * 20.0;
  EXPECT_NEAR(c.concrete_cost, expected_concrete, 1e-9);
  EXPECT_NEAR(c.fence_cost, expected_fence, 1e-9);
  EXPECT_NEAR(c.total_cost, expected_concrete + expected_fence, 1e-9);
}

TEST(Tasks, PoolCostsInvalidArgumentsThrow) {
  EXPECT_THROW(poolCosts(-1.0, 1.0, 1000.0, 2000.0), std::invalid_argument);
  EXPECT_THROW(poolCosts(1.0, -1.0, 1000.0, 2000.0), std::invalid_argument);
  EXPECT_THROW(poolCosts(1.0, 1.0, -1.0, 2000.0), std::invalid_argument);
  EXPECT_THROW(poolCosts(1.0, 1.0, 1000.0, -1.0), std::invalid_argument);
}
