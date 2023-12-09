#include "colony.hpp"
#include "glm_format.hpp"
#include "map.hpp"
#include <iostream>

int main() {
  Map map;

  map.GenerateCities(150, {50, 50});

  Colony colony(map, 35);

  float best_path_len;
  std::vector<int> best_path;

  colony.GetBestPath(best_path, best_path_len);
  std::cout << "initial min path: " << best_path_len << std::endl;

  for (int i = 0; i < 100; i++) {
    colony.FindPathIteration();

    colony.GetBestPath(best_path, best_path_len);
    std::cout << "min path: " << best_path_len << std::endl;
  }

  return 0;
}
