#pragma once

#include "isl_coordinates.hpp"

namespace {
  using Arrows = std::vector<std::pair<Point, Point>>;
};

class VisualObject {
public:
  Points points;
  Arrows arrows;
private:
};
