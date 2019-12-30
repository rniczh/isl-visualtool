#pragma once

// not implementened yet
#include <string>

#include "isl_generator.hpp"

namespace islv {

// CRTP TODO
class PointsPicture {           // 2D
public:
  std::vector<long> xpoints;
  std::vector<long> ypoints;
};


class PlotEngine {
public:
  PlotEngine();
  void attach(islgen::VisualObject &);
  void clear();
  void flush();

  std::pair<int, int> interval = std::make_pair(0, 10);
  std::string title = "";
  std::vector<PointsPicture> points_pictures;
private:
};
} // namespace islv

// using Point  = std::pair<long, long>;
// using Points = std::vector<Point>;
// using Group  = std::vector<Points>;

// class VisualObject {
// public:
//   // some methods need to reflect to image
//   // e.g. reshape functions
//   int dimension;                // The demision of the polytope

// private:
//   // Points points;

// };
