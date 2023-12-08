#include "glm_format.hpp"
#include "map.hpp"
#include <iostream>

int main() {
  Map map;

  map.GenerateCities(50, {10, 10});

  return 0;
}
