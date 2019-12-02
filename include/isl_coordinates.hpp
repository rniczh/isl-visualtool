#pragma once

#include "isl/set.h"
#include "isl/point.h"

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
