#include <glm/glm.hpp>
#include <iostream>

template <typename T>
std::ostream &operator<<(std::ostream &os, glm::vec<2, T> vec) {
  os << "{" << vec.x << ", " << vec.y << "}";

  return os;
}
