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
