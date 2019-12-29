#include "plot_engine.hpp"
#include <cmath>

// plotting lib
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

namespace islv {
PlotEngine::PlotEngine() {}
void PlotEngine::attach(islgen::VisualObject &visual_object) {

  // std::vector<Point> &ps = visual_object.points; //
}

void PlotEngine::clear() {}

void PlotEngine::flush() {
  // Prepare data.
  int n = 5000;
  std::vector<double> x(n), y(n), z(n), w(n, 2);
  for (int i = 0; i < n; ++i) {
    x.at(i) = i * i;
    y.at(i) = sin(2 * M_PI * i / 360.0);
    z.at(i) = log(i);
  }
  plt::xlim(0, 1000 * 1000);

  // Set the size ofm output image to 1200x780 pixels
  // plt::figure_size(1200, 780);
  // // Plot line from given x and y data. Color is selected automatically.
  plt::plot(x, y, "hello");
  // // Plot a red dashed line from given x and y data.
  plt::plot(x, w, "r--");
  // Plot a line whose name will show up as "log(x)" in the legend.
  plt::named_plot("log(x)", x, z);
  // Set x-axis to interval [0,1000000]

  // Add graph title
  plt::title("Sample figure");
  // Enable legend.
  plt::legend();

  plt::save("./basic.png");
  plt::close();
  // Save the image (file format is determined by the extension)

  // plt::show();
}
} // namespace islv

// void PlotEngine::flush() { std::cout << "hello world"; }

// namespace plt = matplotlibcpp;

// void plot_set_points(isl_set *set) {
//   Points set_of_data;
//   isl_set_foreach_point(set, extract_coordinate, &set_of_data);

//   // Using the plot-engine to reflect the image plot
//   // args.plot_engine -> ctx
//   // ctx.setup_points(...) <async
//   // ctx.flush() -> plot data <wait the points
//   for (auto p : set_of_data) {
//     std::cout << p.first << " " << p.second << std::endl;
//   }
// }

// auto plottis() -> void {
//   int n = 1000;
//   std::vector<double> x, y, z;

//   for (int i = 0; i < n; i++) {
//     x.push_back(i * i);
//     y.push_back(sin(2 * M_PI * i / 360.0));
//     z.push_back(log(i));

//     if (i % 10 == 0) {
//       // Clear previous plot
//       plt::clf();
//       // Plot line from given x and y data. Color is selected automatically.
//       plt::plot(x, y);
//       // Plot a line whose name will show up as "log(x)" in the legend.
//       plt::named_plot("log(x)", x, z);

//       // Set x-axis to interval [0,1000000]
//       plt::xlim(0, n * n);

//       // Add graph title
//       plt::title("Sample figure");
//       // Enable legend.
//       plt::legend();
//       // Display plot continuously
//       plt::pause(0.01);
//     }
//   }
// }
