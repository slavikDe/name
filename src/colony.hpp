#pragma once
#include "map.hpp"
#include <set>

class Colony {
public:
  Colony(Map &map, uint ants_count);

  void FindPathIteration();

  void GetBestPath();

private:
  void RunAnt(float &path_len, std::vector<int> &path);

  int ChooseNextCity(int current_city, std::set<int> unvisited_cities);

  float GetTranstionProbability(int from_city, int to_city);

  void UpdatePheromoneOnPath(std::vector<int> &path, float path_len);

  void UpdatePheromone();

private:
  Map map;
  int ants_count;

  std::vector<int> best_path;
  std::vector<int> best_path_len;

  std::map<int, float> added_pheromone_on_roads; 
};
