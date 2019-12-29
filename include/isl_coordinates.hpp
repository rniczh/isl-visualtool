#pragma once

#include "isl/point.h"
#include "isl/set.h"

#include <iostream>
#include <vector>

using Point = std::vector<long>;
using Points = std::vector<Point>;
using Sets = std::vector<isl_set>;

isl_stat extract_coordinate(isl_point *p, void *v);

struct TransferObject {
  isl_size dim;
  Points &points;
};

class Coordinate {
public:
  Coordinate();

private:
  // std::map<isl_id, Polygon> polygons;
  // std::vector<Polygon> polygons;
};
