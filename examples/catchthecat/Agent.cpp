#include "World.h"
#include "Agent.h"

Point2D Agent::randomMove(World* w)
{
  // Get Random Number and Move In That Direction
  auto catPos = w->getCat();
  const int END_CONST = 5;
  auto randomNum = Random::Range(0, END_CONST);

  switch (randomNum)
  {
    case 0:
      return World::E(catPos);
    case 1:
      return World::W(catPos);
    case 2:
      return World::NE(catPos);
    case 3:
      return World::NW(catPos);
    case 4:
      return World::SW(catPos);
    case 5:
      return World::SE(catPos);
    default:
      break;
  }
}

std::vector<Point2D> Agent::generatePath(World* w)
{
  // Establish Frontier, Paths, Slots, Cat, Exit Point, and Neighbors (+ Initialization of Frontier)
  std::queue<Point2D> frontier;
  std::unordered_map<Point2D, Point2D> originalPath;
  std::vector<Point2D> path;
  std::unordered_set<Point2D> currentFrontier;
  std::unordered_map<Point2D, bool> visitedSlots;
  std::queue<Point2D> const newPath;
  Point2D const catPos = w->getCat();
  Point2D current{};
  Point2D exitPoint = Point2D(INT_MAX, INT_MAX);
  std::vector<Point2D> neighbors;

  frontier.push(catPos);
  currentFrontier.insert(catPos);
  originalPath[catPos] = Point2D(INT_MAX, INT_MAX);

  while (!frontier.empty() && exitPoint == Point2D(INT_MAX, INT_MAX))
  {
    current = frontier.front();
    frontier.pop();
    currentFrontier.erase(current);
    visitedSlots[current] = true;

    // Grab Neighbors
    neighbors = getNeighbors(current, w, visitedSlots, currentFrontier);

    // Adding to Frontier from Neighbors
    for(Point2D const n : neighbors)
    {
      originalPath[n] = current;
      frontier.push(n);
      currentFrontier.insert(n);

      if(w->catWinsOnSpace(n))
      {
        exitPoint = n;
        break;
      }
    }
  }

  current = exitPoint;

  while(current != w->getCat())
  {
    path.push_back(current);
    current = originalPath[current];
  }

  return path;
}


std::vector<Point2D> Agent::getNeighbors(Point2D point, World* w, std::unordered_map<Point2D, bool>& visitedSlots, const std::unordered_set<Point2D>& frontier)
{
  // Initialized Cat, And Each Direction via the World
  auto cat = w->getCat();
  std::vector<Point2D> neighbors;
  auto East = World::E(point);
  auto West = World::W(point);
  auto Northeast = World::NE(point);
  auto Northwest = World::NW(point);
  auto Southwest = World::SW(point);
  auto Southeast = World::SE(point);


  // Check if visited, if is a wall, is in the frontier, is the cat
  if(!visitedSlots[East] && !w->getContent(East) && !frontier.contains(East) && East != cat)
  {
    neighbors.push_back(World::E(point));
  }

  if(!visitedSlots[West] && !w->getContent(West) && !frontier.contains(West) && West != cat)
  {
    neighbors.push_back(World::W(point));
  }

  if(!visitedSlots[Northeast] && !w->getContent(Northeast) && !frontier.contains(Northeast) && Northeast != cat)
  {
    neighbors.push_back(World::NE(point));
  }

  if(!visitedSlots[Northwest] && !w->getContent(Northwest) && !frontier.contains(Northwest) && Northwest != cat)
  {
    neighbors.push_back(World::NW(point));
  }

  if(!visitedSlots[Southwest] && !w->getContent(Southwest) && !frontier.contains(Southwest) && Southwest != cat)
  {
    neighbors.push_back(World::SW(point));
  }

  if(!visitedSlots[Southeast] && !w->getContent(Southeast) && !frontier.contains(Southeast) && Southeast != cat)
  {
    neighbors.push_back(World::SE(point));
  }

  return neighbors;
}