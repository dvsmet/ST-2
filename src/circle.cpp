// Copyright 2022 UNN-CS
#include "circle.h"

#include <string>

namespace {
bool isFinite(double v) {
  return std::isfinite(v);
}
}  // namespace

Circle::Circle(double radius) {
  setRadius(radius);
}

void Circle::validateNonNegativeFinite(double value, const char* fieldName) {
  if (!isFinite(value)) {
    throw std::invalid_argument(std::string(fieldName) +
                                " must be a finite number");
  }
  if (value < 0.0) {
    throw std::invalid_argument(std::string(fieldName) +
                                " must be non-negative");
  }
}

void Circle::recalcFromRadius() {
  ference_ = 2.0 * kPi * radius_;
  area_ = kPi * radius_ * radius_;
}

void Circle::recalcFromFerence() {
  if (ference_ == 0.0) {
    radius_ = 0.0;
    area_ = 0.0;
    return;
  }
  radius_ = ference_ / (2.0 * kPi);
  area_ = kPi * radius_ * radius_;
}

void Circle::recalcFromArea() {
  if (area_ == 0.0) {
    radius_ = 0.0;
    ference_ = 0.0;
    return;
  }
  radius_ = std::sqrt(area_ / kPi);
  ference_ = 2.0 * kPi * radius_;
}

void Circle::setRadius(double radius) {
  validateNonNegativeFinite(radius, "radius");
  radius_ = radius;
  recalcFromRadius();
}

void Circle::setFerence(double ference) {
  validateNonNegativeFinite(ference, "ference");
  ference_ = ference;
  recalcFromFerence();
}

void Circle::setArea(double area) {
  validateNonNegativeFinite(area, "area");
  area_ = area;
  recalcFromArea();
}

double Circle::getRadius() const {
  return radius_;
}

double Circle::getFerence() const {
  return ference_;
}

double Circle::getArea() const {
  return area_;
}
