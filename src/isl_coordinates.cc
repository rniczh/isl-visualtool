#include "isl_coordinates.hpp"

isl_stat extract_coordinate(isl_point *p, void *v) {
  TransferObject *data = reinterpret_cast<TransferObject *>(v);

  Point point;
  for (isl_size i = 0; i < data->dim; ++i) {
    auto *v = isl_point_get_coordinate_val(p, isl_dim_set, i);
    if (not v) {
      return isl_stat_error;
    }

    long n = isl_val_get_num_si(v);
    point.push_back(n);
  }
  data->points.push_back(std::move(point));

  return isl_stat_ok;
}
