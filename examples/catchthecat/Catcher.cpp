#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* w)
{
  auto path = generatePath(w);
  if(!path.empty())
  {
    return path[0];
  }
  return randomMove(w);
}
