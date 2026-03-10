// Copyright 2026 UNN-CS
#include "tasks.h"

#include <cmath>
#include <stdexcept>

#include "circle.h"

double earthRopeGapMeters(double earth_radius_km, double added_length_m) {
  if (!std::isfinite(earth_radius_km) || earth_radius_km < 0.0) {
    throw std::invalid_argument(
        "earth_radius_km must be finite and non-negative");
  }
  if (!std::isfinite(added_length_m) || added_length_m < 0.0) {
    throw std::invalid_argument(
        "added_length_m must be finite and non-negative");
  }

  const double earth_radius_m = earth_radius_km * 1000.0;
  Circle earth(earth_radius_m);
  const double original = earth.getFerence();

  Circle rope;
  rope.setFerence(original + added_length_m);
  return rope.getRadius() - earth_radius_m;
}

PoolCosts poolCosts(double pool_radius_m,
                    double track_width_m,
                    double concrete_cost_per_m2,
                    double fence_cost_per_m) {
  if (!std::isfinite(pool_radius_m) || pool_radius_m < 0.0) {
    throw std::invalid_argument(
        "pool_radius_m must be finite and non-negative");
  }
  if (!std::isfinite(track_width_m) || track_width_m < 0.0) {
    throw std::invalid_argument(
        "track_width_m must be finite and non-negative");
  }
  if (!std::isfinite(concrete_cost_per_m2) || concrete_cost_per_m2 < 0.0) {
    throw std::invalid_argument(
        "concrete_cost_per_m2 must be finite and non-negative");
  }
  if (!std::isfinite(fence_cost_per_m) || fence_cost_per_m < 0.0) {
    throw std::invalid_argument(
        "fence_cost_per_m must be finite and non-negative");
  }

  const double outer_radius_m = pool_radius_m + track_width_m;

  Circle inner(pool_radius_m);
  Circle outer(outer_radius_m);

  const double track_area = outer.getArea() - inner.getArea();
  const double fence_length = outer.getFerence();

  PoolCosts out;
  out.concrete_cost = track_area * concrete_cost_per_m2;
  out.fence_cost = fence_length * fence_cost_per_m;
  out.total_cost = out.concrete_cost + out.fence_cost;
  return out;
}
