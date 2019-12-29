#pragma once

#include "isl_coordinates.hpp"

namespace {
using Arrows = std::vector<std::pair<Point, Point>>;
};

enum visual_type {
  points,
  relations,
};

class VisualObject {
public:
  unsigned int parametric_value;
  Points points;
  Arrows arrows;
  void add_statement();

  // VisualObject();
private:

};
