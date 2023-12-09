#pragma once
#include "map.hpp"
#include "random.hpp"
#include <set>

class Colony {
public:
  Colony(Map &map, uint ants_count);

  void FindPathIteration();

  void GetBestPath(std::vector<int> &path, float &path_len);

private:
  void RunAnt(float &path_len, std::vector<int> &path);

  int ChooseNextCity(int current_city, std::set<int> unvisited_cities);

  float GetTranstionDesire(int from_city, int to_city);

  void UpdatePheromoneOnPath(std::vector<int> &path, float path_len);

  void UpdatePheromone();

  float CalculateGreedyPathLen();
  int GetClosestCity(int current_city, std::set<int> &cities);

private:
  Map map;
  int ants_count;

  float l_min;

  std::vector<int> best_path;
  float best_path_len;

  std::map<uint64_t, float> added_pheromone_on_roads;
};
