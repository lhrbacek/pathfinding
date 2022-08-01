#include <iostream>
#include <optional>
#include <queue>

#include "algorithms.hpp"

void bfs(Grid &g, sf::RenderWindow &window)
{
    std::queue<unsigned int> queue;
    queue.push(g.start);
    g.vertices[g.start].setState(State::visited);

    while (!queue.empty())
    {
        unsigned int v = queue.front();
        queue.pop();

        for (unsigned int n : g.vertices[v].neighbors)
        {
            if (g.vertices[n].state == State::notVisited)
            {
                queue.push(n);
                g.vertices[n].setState(State::visited);
                g.vertices[n].predecessor = v;
                g.vertices[n].distance = g.vertices[v].distance + 1;

                window.clear();
                g.draw(window);
                window.display();
            }
        }

        g.vertices[v].setState(State::finished);

        window.clear();
        g.draw(window);
        window.display();

        if (g.vertices[g.end].predecessor)
        {
            return;
        }
    }
}

bool dfsRec(unsigned int v, Grid &g, sf::RenderWindow &window)
{
    for (unsigned int n : g.vertices[v].neighbors)
    {
        if (g.vertices[n].state == State::notVisited)
        {
            g.vertices[n].setState(State::visited);
            g.vertices[n].predecessor = v;
            g.vertices[n].distance = g.vertices[v].distance + 1;
            if (g.vertices[g.end].predecessor)
            {
                return true;
            }

            window.clear();
            g.draw(window);
            window.display();

            if (dfsRec(n, g, window))
            {
                return true;
            }
        }
    }

    g.vertices[v].setState(State::finished);

    window.clear();
    g.draw(window);
    window.display();

    return false;
}

void dfs(Grid &g, sf::RenderWindow &window)
{
    g.vertices[g.start].setState(State::visited);
    dfsRec(g.start, g, window);
}

float heuristic(Grid &g, unsigned int v1, enum heuristic h)
{
    if (h == heuristic::greedyH)
    {
        return euclideanDistance(v1, g.end, g.sizeX);
    }
    else // if (h == heuristic::astarH)
    {
        return g.vertices[v1].distance + euclideanDistance(v1, g.end, g.sizeX);
    }
}

void greedy(Grid &g, sf::RenderWindow &window)
{
    bestFirstSearch(g, window, heuristic::greedyH);
}

void AStar(Grid &g, sf::RenderWindow &window)
{
    bestFirstSearch(g, window, heuristic::astarH);
}

void bestFirstSearch(Grid &g, sf::RenderWindow &window, enum heuristic h)
{
    auto cmp = [](std::tuple<unsigned int, float> left, std::tuple<unsigned int, float> right)
    { return std::get<1>(left) > std::get<1>(right); };

    std::priority_queue<std::tuple<unsigned int, float>,
                        std::vector<std::tuple<unsigned int, float>>,
                        decltype(cmp)>
        queue(cmp);

    queue.emplace(g.start, heuristic(g, g.start, h));
    g.vertices[g.start].setState(State::visited);

    while (!queue.empty())
    {
        auto [v, _] = queue.top();
        queue.pop();

        for (unsigned int n : g.vertices[v].neighbors)
        {
            if (g.vertices[v].distance + 1 < g.vertices[n].distance)
            {
                g.vertices[n].setState(State::visited);
                g.vertices[n].predecessor = v;
                g.vertices[n].distance = g.vertices[v].distance + 1;
                queue.emplace(n, heuristic(g, n, h));

                window.clear();
                g.draw(window);
                window.display();
            }
        }

        g.vertices[v].setState(State::finished);

        window.clear();
        g.draw(window);
        window.display();

        if (g.vertices[g.end].predecessor)
        {
            return;
        }
    }
}
