#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "pathfinding.hpp"

enum heuristic
{
    greedyH,
    astarH
};

void bfs(Grid &g, sf::RenderWindow &window);

bool dfsRec(unsigned int v, Grid &g, sf::RenderWindow &window);

void dfs(Grid &g, sf::RenderWindow &window);

void bestFirstSearch(Grid &g, sf::RenderWindow &window, enum heuristic);

void greedy(Grid &g, sf::RenderWindow &window);

void AStar(Grid &g, sf::RenderWindow &window);

#endif // ALGORITHMS
