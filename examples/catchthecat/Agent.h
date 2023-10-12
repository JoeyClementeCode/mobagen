#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
class World;

using namespace std;

class Agent {
public:
  explicit Agent() = default;
  static Point2D randomMove(World*);
  static vector<Point2D> generatePath(World* w);
  static vector<Point2D> getNeighbors(Point2D point, World* w, unordered_map<Point2D, bool>& visited, const unordered_set<Point2D>& frontier);
  virtual Point2D Move(World*) = 0;
};

#endif  // AGENT_H
