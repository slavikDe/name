#pragma once
#include <glm/glm.hpp>
#include <map>
#include <vector>

class Map {
public:
  struct Road {
    float distance;
    float pheromone;
  };

private:
  union RoadId {
    uint32_t city_indexes[2];
    uint64_t road_id;
  };

public:
  Map();

  void GenerateCities(uint count, glm::fvec2 map_size);

  size_t GetCitiesCount();

  Road &GetRoad(uint64_t road_id);

  uint64_t GetRoadId(int city1_index, int city2_index);

private:
  void CreateEmptyRoads();

private:
  std::vector<glm::fvec2> cities;
  std::map<uint64_t, Road> roads;
};
