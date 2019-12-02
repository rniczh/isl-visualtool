#pragma once

#include "isl/map.h"
#include "isl/set.h"
#include "isl/union_map.h"
#include "isl/union_set.h"

#include "isl/space.h"
#include "isl/id.h"
#include <vector>
#include <map>

namespace {

class Polygon {
  using Point = std::pair<long, long>;
  using Points = std::vector<Point>;

public:
  void add_point(Point p) { points.push_back(p); }

private:
  Points points;
};

class Coordinate {
public:
  Coordinate();

private:
  // std::map<isl_id, Polygon> polygons;
  // std::vector<Polygon> polygons;
};

} // namespace

namespace islv {

/// This is the majaor class for using ISL visualization tool.
class ISLVContext {
public:
  ISLVContext() {};
  ISLVContext(ISLVContext &) = delete;
  ISLVContext &operator=(const ISLVContext &) = delete;
  ~ISLVContext() {};

  isl_stat plot(isl_union_set *);
  isl_stat plot(isl_set *);
  isl_stat plot(isl_basic_set *);

  isl_stat plot(isl_union_map *);
  isl_stat plot(isl_map *);
  isl_stat plot(isl_basic_map *);

  void plot_map(isl_map *map);

private:
  std::vector<Coordinate> coordinates;

};

} // namespace islv
