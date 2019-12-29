#include "isl_generator.hpp"
#include "isl_schedule.hpp"
#include <vector>
#include <typeinfo>

// TODO
using namespace islgen;



template <typename isl_data> VisualObject parse(isl_data *data) {
  VisualObject res;
  return res;
}

void VisualObject::add_statement(std::string set_name,
                                 std::vector<std::string> dim_name_vec,
                                 Points points) {
  // TODO
  // DEBUG
  //   statement name:
  std::cout << "statement name: ";
  std::cout << set_name << std::endl;
  //   demision name:
  std::cout << "demision name: ";
  for (auto &s : dim_name_vec) {
    std::cout << s << " ";
  }
  std::cout << "\n";
  //   points:
  std::cout << "set points: \n";
  for (auto &p : points) {
    std::cout << "( ";
    for (auto &d : p) {
      std::cout << d << " ";
    }
    std::cout << ")";
  }
  std::cout << std::endl;

  //
}
