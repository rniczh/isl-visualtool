#include "islplot.hpp"
#include "isl_coordinates.hpp"
#include "isl_generator.hpp"
#include "plot_engine.hpp"

// namespace plt = matplotlibcpp;
#include <string>

namespace {
// Wrapping the ISLVContext::plot(isl_set *set)
isl_stat plot_each_set(isl_set *set, void *user) {
  islv::ISLVContext *ctx = reinterpret_cast<islv::ISLVContext *>(user);
  return ctx->plot(set);
}
} // namespace

namespace islv {

isl_stat ISLVContext::plot(isl_union_set *uset) {
  isl_stat ok = isl_union_set_foreach_set(uset, plot_each_set, this);
  return ok;
}

isl_stat ISLVContext::plot(isl_set *set) {
  // construct a visual object
  std::cout << "[ISL PLOT]\nplot: " << isl_set_to_str(set) << std::endl;


  islgen::VisualObject visual_object = islgen::gen_visual_object(set);

  plot_engine.attach(visual_object);
  plot_engine.flush();
  // plot_engine.interval = std::make_pair(visual_object.interval);
  // VisualObject visual_object;
  // //   statment name
  // //   demision name vector
  // //   points vec
  // visual_object.add_statement(isl_set_get_tuple_name(set), id_string_vec,
  //                             object.points);

  // plot_engine.flush();

  // plot_engine.attach(visual_object);

  // name, demision vector, points
  // visual_object.add_statement();

  //   isl pattern: (with isl language)

  // for (auto &p : object.points) {
  //   // dim_x.push_back(p.at(0));
  //   // dim_y.push_back(p.at(1));

  //   // for (isl_size i = 0; i < dim; ++i) {
  //   //   dim_vec[i].push_back(p.at(i));
  //   // }
  //   std::cout << "( ";
  //   for (auto &d : p) {
  //     std::cout << d << " ";
  //   }
  //   std::cout << ")\n";

  //   // std::cout << "(";
  //   // for (isl_size i = 0; i < dim; ++i) {
  //   //   std::cout << " " << p.at(i);
  //   // }
  //   // std::cout << " )";
  // }

  // // _plt.plot(dimX, dimY, marker, markersize=size, color=color, lw=0)

  // // print out the demision naming for each

  // std::cout << "\n";

  // // what structure for printing
  // std::cout << "plot: " << isl_set_to_str(set) << std::endl;

  // // create a visaul object
  // VisualObject visual_object;

  // visual_object.points = object.points;

  // std::cout << isl_set_get_tuple_name(set);

  // // std::cout << "{ ";

  // // plt::plot();

  // // // plt::quiver(x, y, u, v);
  // // plt::show();
  // // print out each points
  // std::vector<std::vector<long>> dim_vec;

  // for (auto &p : object.points) {
  //   // dim_x.push_back(p.at(0));
  //   // dim_y.push_back(p.at(1));

  //   // for (isl_size i = 0; i < dim; ++i) {
  //   //   dim_vec[i].push_back(p.at(i));
  //   // }
  //   std::cout << "( ";
  //   for (auto &d: p) {
  //     std::cout << d << " ";
  //   }
  //   std::cout << ")\n";

  //   // std::cout << "(";
  //   // for (isl_size i = 0; i < dim; ++i) {
  //   //   std::cout << " " << p.at(i);
  //   // }
  //   // std::cout << " )";
  // }

  // create a visual object
  // VisualObject vo = create_visual_object("name");
  // plt::plot(dim_vec[0], dim_y, ".");
  // plt::show();
  // puts("} ");
  return isl_stat_ok;
}

isl_stat ISLVContext::plot(isl_basic_set *bset) {
  isl_set *set = isl_set_from_basic_set(bset);
  return this->plot(set);
}

} // namespace islv
