#include "colony.hpp"
#include <cmath>
#include <iostream>

Colony::Colony(Map &map, uint ants_count) {
  this->map = map;
  this->ants_count = ants_count;

  l_min = CalculateGreedyPathLen();

  best_path_len = l_min;
}

void Colony::FindPathIteration() {
  best_path_len = std::numeric_limits<int>::max();

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

void Colony::GetBestPath(std::vector<int> &path, float &path_len) {
  path = best_path;
  path_len = best_path_len;
}

void Colony::RunAnt(float &path_len, std::vector<int> &path) {
  std::set<int> unvisited_cities;
  for (int i = 0; i < map.GetCitiesCount(); i++) {
    unvisited_cities.insert(i);
  }

  int first_city = random_int(0, map.GetCitiesCount() - 1);

  int current_city = first_city;
  path.push_back(current_city);
  unvisited_cities.erase(first_city);

  path_len = 0;

  while (!unvisited_cities.empty()) {
    int next_city = ChooseNextCity(current_city, unvisited_cities);
    int closest_city = GetClosestCity(current_city, unvisited_cities);

    uint64_t road_id = map.GetRoadId(current_city, next_city);
    Map::Road road = map.GetRoad(road_id);

    uint64_t closest_road_id = map.GetRoadId(current_city, closest_city);
    Map::Road closest_road = map.GetRoad(closest_road_id);

    path_len += road.distance;

    path.push_back(next_city);

    unvisited_cities.erase(next_city);
    current_city = next_city;
  }

  uint64_t final_road_id = map.GetRoadId(current_city, first_city);
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

  float x = 0;
  for (int c : unvisited_cities) {
    float desire = GetTranstionDesire(c, current_city);
    x += desire;

    if (x > rand_number) {
      return c;
    }
  }

  return *unvisited_cities.rbegin();
}

float Colony::GetTranstionDesire(int from_city, int to_city) {
  const float alpha = 2, beta = 3;

  uint64_t road_id = map.GetRoadId(from_city, to_city);
  Map::Road road = map.GetRoad(road_id);

  float desire =
      std::pow(road.pheromone, alpha) * std::pow(1.0f / road.distance, beta);

  return desire;
}

void Colony::UpdatePheromoneOnPath(std::vector<int> &path, float path_len) {
  float pheramone_amount = (l_min / path_len);

  for (int i = 0; i < path.size() - 1; i++) {
    int from = path[i];
    int to = path[i + 1];

    uint64_t road_id = map.GetRoadId(from, to);

    if (added_pheromone_on_roads.contains(road_id)) {
      added_pheromone_on_roads[road_id] += pheramone_amount;
    } else {
      added_pheromone_on_roads[road_id] = pheramone_amount;
    }
  }
}

void Colony::UpdatePheromone() {
  map.AddPheromone(added_pheromone_on_roads);

  added_pheromone_on_roads.clear();
}

float Colony::CalculateGreedyPathLen() {
  std::set<int> unvisited_cities;
  for (int i = 0; i < map.GetCitiesCount(); i++) {
    unvisited_cities.insert(i);
  }

  int first_city = random_int(0, map.GetCitiesCount() - 1);

  int current_city = first_city;
  unvisited_cities.erase(first_city);

  float path_len = 0;

  while (!unvisited_cities.empty()) {
    int closest_city = GetClosestCity(current_city, unvisited_cities);

    uint64_t road_id = map.GetRoadId(current_city, closest_city);
    Map::Road road = map.GetRoad(road_id);

    path_len += road.distance;

    unvisited_cities.erase(closest_city);

    current_city = closest_city;
  }

  uint64_t final_road_id = map.GetRoadId(current_city, first_city);
  Map::Road final_road = map.GetRoad(final_road_id);

  path_len += final_road.distance;

  return path_len;
}

int Colony::GetClosestCity(int current_city, std::set<int> &cities) {
  int closest_city = *cities.begin();
  float closest_city_dist =
      map.GetRoad(map.GetRoadId(current_city, closest_city)).distance;

  for (int c : cities) {
    float dist = map.GetRoad(map.GetRoadId(current_city, c)).distance;

    if (dist < closest_city_dist) {
      closest_city = c;
      closest_city_dist = dist;
    }
  }

  return closest_city;
}
