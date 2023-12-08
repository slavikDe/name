#include "random.hpp"

static std::random_device device;
static std::mt19937 generator(device());

float random_float(float min, float max) {
  auto dist = std::uniform_real_distribution<float>(min, max);

  return dist(generator);
}

int random_int(int min, int max){
  auto dist = std::uniform_int_distribution<int>(min, max);
  
  return dist(generator);
}
