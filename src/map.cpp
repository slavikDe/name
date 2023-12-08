#include "map.hpp"
#include "random.hpp"

Map::Map() {}

void Map::GenerateCities(uint count, glm::fvec2 map_size) {
  for (int i = 0; i < count; i++) {
    glm::fvec2 new_city;
    new_city.x = random_float(0, map_size.x);
    new_city.y = random_float(0, map_size.y);

    cities.push_back(new_city);
  }
}

size_t Map::GetCitiesCount() {
  return cities.size();
}

Map::Road &Map::GetRoad(uint64_t road_id) {
  return roads[road_id];
}

uint64_t Map::GetRoadId(int city1_index, int city2_index) {
  if (city1_index > city2_index) {
    std::swap(city1_index, city2_index);
  }

  RoadId id_union;
  id_union.city_indexes[0] = city1_index;
  id_union.city_indexes[1] = city2_index;

  return id_union.road_id;
}

void Map::CreateEmptyRoads() {
  roads.clear();

  for (uint32_t i = 0; i < cities.size() - 1; i++) {
    for (uint32_t j = i + 1; j < cities.size(); j++) {
      Road road;
      road.distance = glm::distance(cities[i], cities[j]);
      road.pheromone = 0;

      uint64_t road_id = GetRoadId(i, j);
      roads[road_id] = road;
    }
  }
}
