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
  isl_size dim = isl_set_dim(set, isl_dim_set);

  std::vector<std::string> id_string_vec;

  // Extract the dimension 'naming' from the set
  for (isl_size i = 0; i < dim; ++i) {
    id_string_vec.push_back(
        isl_id_get_name(isl_set_get_dim_id(set, isl_dim_set, i)));
  }

  Points points;
  TransferObject object{
      dim,
      points,
  };

  // extract coordinate from the set and store into the object
  isl_stat status = isl_set_foreach_point(set, extract_coordinate, &object);
  if (status == isl_stat_error) {
    return status;
  }

  isl_space *space = isl_set_get_space(set);
  isl_size space_dim = isl_space_dim(space, isl_dim_set);
  isl_id *id = isl_space_get_dim_id(space, isl_dim_set, 0);

  // construct a visual object
  VisualObject visual_object;

  plot_engine.flush();

  // plot_engine.attach(visual_object);

  // name, demision vector, points
  // visual_object.add_statement();

  //   isl pattern: (with isl language)
  std::cout << "[ISL PLOT]\nplot: " << isl_set_to_str(set) << std::endl;
  //   statement name:
  std::cout << "statement name: ";
  std::cout << isl_set_get_tuple_name(set) << std::endl;
  //   demision name:
  std::cout << "demision name: ";
  for (auto &s : id_string_vec) {
    std::cout << s << " ";
  }
  std::cout << "\n";
  //   points:
  std::cout << "set points: \n";
  for (auto &p : object.points) {
    std::cout << "( ";
    for (auto &d : p) {
      std::cout << d << " ";
    }
    std::cout << ")";
  }
  std::cout << std::endl;
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
