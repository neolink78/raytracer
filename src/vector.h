#pragma once

class Vector {
  public:
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vector add(const Vector& other) const;

  private:
    double _x;
    double _y;
    double _z;
};
