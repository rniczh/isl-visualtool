#pragma once

// not implementened yet
#include <string>

#include "isl_generator.hpp"

namespace islv {
class PlotEngine {
public:
  PlotEngine();
  void attach(islgen::VisualObject &);
  void set_width_height(size_t width, size_t height);
  void clear();
  void flush();

private:
  std::string title = "";
  std::pair<int, int> interval = std::make_pair(0,10);
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
