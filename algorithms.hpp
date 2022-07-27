#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "pathfinding.hpp"

void bfs(Grid &g, sf::RenderWindow &window);

bool dfsRec(unsigned int v, Grid &g, sf::RenderWindow &window);

void dfs(Grid &g, sf::RenderWindow &window);

#endif // ALGORITHMS
