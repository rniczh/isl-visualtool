#include "islplot.hpp"
#include "isl_coordinates.hpp"
#include "plot_engine.hpp"

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

  isl_stat status = isl_set_foreach_point(set, extract_coordinate, &object);
  if (status == isl_stat_error) {
    return status;
  }

  isl_space *space = isl_set_get_space(set);
  isl_size space_dim = isl_space_dim(space, isl_dim_set);
  isl_id *id = isl_space_get_dim_id(space, isl_dim_set, 0);

  // print out the demision naming for each
  for (auto &s : id_string_vec) {
    std::cout << s << " ";
  }

  std::cout << "\n";

  // what structure for printing
  std::cout << "plot: " << isl_set_to_str(set) << std::endl;
  std::cout << "{ ";

  // print out each points
  for (auto &p : object.points) {
    std::cout << "(";
    for (isl_size i = 0; i < dim; ++i) {
      std::cout << " " << p.at(i);
    }
    std::cout << " )";
  }
  puts("} ");
  return isl_stat_ok;
}

isl_stat ISLVContext::plot(isl_basic_set *bset) {
  isl_set *set = isl_set_from_basic_set(bset);
  return this->plot(set);
}

} // namespace islv
