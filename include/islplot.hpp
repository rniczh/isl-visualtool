#pragma once

#include "isl/map.h"
#include "isl/set.h"
#include "isl/union_map.h"
#include "isl/union_set.h"

#include "isl/space.h"
#include "isl/id.h"

#include "isl_coordinates.hpp"
#include "plot_engine.hpp"

#include <vector>
#include <map>

namespace {

class Plane {



};

class Polygon {
  // using Point = std::pair<long, long>;
  // using Points = std::vector<Point>;

public:
  void add_point(Point p) { points.push_back(p); }

private:
  Points points;
};

} // namespace

namespace islv {

/// This is the majaor class for using ISL visualization tool.
class ISLVContext {
public:
  ISLVContext(PlotEngine &engine) : plot_engine(engine) {};
  ISLVContext(ISLVContext &) = delete;
  ISLVContext &operator=(const ISLVContext &) = delete;
  ~ISLVContext() {};

  isl_stat plot(isl_union_set *);
  isl_stat plot(isl_set *);
  isl_stat plot(isl_basic_set *);

  isl_stat plot(isl_union_map *);
  isl_stat plot(isl_map *);
  isl_stat plot(isl_basic_map *);

private:
  std::vector<Coordinate> coordinates;
  PlotEngine &plot_engine;
};

} // namespace islv
