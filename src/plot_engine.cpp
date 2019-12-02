#include "plot_engine.hpp"

namespace plt = matplotlibcpp;

using Point  = std::pair<long, long>;
using Points = std::vector<Point>;
using Group  = std::vector<Points>;

class VisualObject {
public:
  // some methods need to reflect to image
  // e.g. reshape functions



private:
  Points points;
};

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
