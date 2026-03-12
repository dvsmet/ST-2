// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_
#include <cmath>
#include <stdexcept>

class Circle {
 public:
  explicit Circle(double radius = 0.0);

  void setRadius(double radius);
  void setFerence(double ference);
  void setArea(double area);

  double getRadius() const;
  double getFerence() const;
  double getArea() const;

 private:
  static constexpr double kPi = 3.141592653589793238462643383279502884;

  double radius_ = 0.0;
  double ference_ = 0.0;
  double area_ = 0.0;

  static void validateNonNegativeFinite(double value, const char* fieldName);
  void recalcFromRadius();
  void recalcFromFerence();
  void recalcFromArea();
};
#endif  // INCLUDE_CIRCLE_H_
