#include "colony.hpp"

void Colony::FindPathIteration() {
  for (int i = 0; i < ants_count; i++) {
    float path_len;
    std::vector<int> path;

    RunAnt(path_len, path);

	// TODO save best path to best_path and best_path_len
  }

  UpdatePheromone();
}

void Colony::RunAnt(float &path_len, std::vector<int> &path) {
  std::set<int> unvisited_cities;
  // TODO all cities indexes to unvisited cities;

  int first_city = 0; // todo choose random first city

  int current_city = first_city;
  path.push_back(current_city);

  path_len = 0;

  while (!unvisited_cities.empty()) {
    int next_city = ChooseNextCity(current_city, unvisited_cities);

    Map::Road road; // TODO get road

    path_len += road.distance;

    path.push_back(next_city);
  }

  Map::Road final_road; // TODO get final road
  path_len += final_road.distance;
  path.push_back(first_city);

  UpdatePheromoneOnPath(path, path_len);
}

int Colony::ChooseNextCity(int current_city, std::set<int> unvisited_cities) {}
