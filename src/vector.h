#pragma once

class Vector {
  public:
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    double dot(const Vector& other) const;
    double length() const;

  private:
    double _x;
    double _y;
    double _z;
};

Vector operator*(double t, const Vector& v);
