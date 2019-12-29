#pragma once

#include "isl_coordinates.hpp"

#include <string>

namespace {
using Arrows = std::vector<std::pair<Point, Point>>;
};

namespace islgen {

enum visual_type {
  points,
  relations,
};

class VisualObject {
public:
  unsigned int parametric_value;
  Points points;
  Arrows arrows;
  void add_statement(std::string set_name,
                     std::vector<std::string> dim_name_vec, Points points);

private:
};

template <typename isl_data> VisualObject parse_from_isl_data(isl_data *data) {
  VisualObject res;

  // construct the visual object from isl_set
  if (typeid(isl_data *) == typeid(isl_set *)) {
    std::cout << "=> visual object parse from set\n";

    isl_size dim = isl_set_dim(data, isl_dim_set);

    std::vector<std::string> id_string_vec;

    // Extract the dimension 'naming' from the set
    for (isl_size i = 0; i < dim; ++i) {
      id_string_vec.push_back(
          isl_id_get_name(isl_set_get_dim_id(data, isl_dim_set, i)));
    }

    Points points;
    TransferObject object{
        dim,
        points,
    };

    // extract coordinate from the set and store into the object
    isl_stat status = isl_set_foreach_point(data, extract_coordinate, &object);
    if (status == isl_stat_error) {
      std::cerr << "fail to extract coordinate from the set and store into the "
                   "object\n";
      exit(1);
    }

    isl_space *space = isl_set_get_space(data);
    isl_size space_dim = isl_space_dim(space, isl_dim_set);
    isl_id *id = isl_space_get_dim_id(space, isl_dim_set, 0);

    // VisualObject
    //   statment name
    //   demision name vector
    //   points vec
    res.add_statement(isl_set_get_tuple_name(data), id_string_vec,
                      object.points);
    return res;

  } else if (typeid(isl_data *) == typeid(isl_map *)) {
    // std::cout << "visual object parse from map\n";
    // TODO
    std::cerr << "cannot process isl_map currently QQ\n";
    exit(1);
  }

  return res;
}

} // namespace islgen
