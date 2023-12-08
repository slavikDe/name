#include "colony.hpp"
#include <cmath>

void Colony::FindPathIteration() {
  for (int i = 0; i < ants_count; i++) {
    float path_len;
    std::vector<int> path;

    RunAnt(path_len, path);

    if (best_path_len > path_len) {
      best_path_len = path_len;
      best_path = path;
    }
  }

  UpdatePheromone();
}

void Colony::RunAnt(float &path_len, std::vector<int> &path) {
  std::set<int> unvisited_cities;
  for (int i = 0; i < map.GetCitiesCount(); i++) {
    unvisited_cities.insert(i);
  }

  int first_city = random_int(0, map.GetCitiesCount());

  int current_city = first_city;
  path.push_back(current_city);
  unvisited_cities.erase(first_city);

  path_len = 0;

  while (!unvisited_cities.empty()) {
    int next_city = ChooseNextCity(current_city, unvisited_cities);

    int road_id = map.GetRoadId(current_city, next_city);
    Map::Road road = map.GetRoad(road_id);

    path_len += road.distance;

    path.push_back(next_city);

    unvisited_cities.erase(next_city);
    current_city = next_city;
  }

  int final_road_id = map.GetRoadId(current_city, first_city);
  Map::Road final_road = map.GetRoad(final_road_id);

  path_len += final_road.distance;
  path.push_back(first_city);

  UpdatePheromoneOnPath(path, path_len);
}

int Colony::ChooseNextCity(int current_city, std::set<int> unvisited_cities) {
  float sum = 0;

  for (int c : unvisited_cities) {
    sum += GetTranstionDesire(c, current_city);
  }

  float rand_number = random_float(0, sum);

  int x = 0;
  for (int c : unvisited_cities) {
    x += GetTranstionDesire(c, current_city);

    if (x <= rand_number) {
      return c;
    }
  }

  return *unvisited_cities.rbegin();
}

float Colony::GetTranstionDesire(int from_city, int to_city) {
  int road_id = map.GetRoadId(from_city, to_city);
  Map::Road road = map.GetRoad(road_id);

  return std::pow(road.pheromone, 2) * std::pow(1 / road.distance, 3);
}

void Colony::UpdatePheromoneOnPath(std::vector<int> &path, float path_len) {
  float pheramone_amount;
  
}

void Colony::UpdatePheromone() {}
