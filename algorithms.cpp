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

// void cmp();

// void bestFirstSearch(Grid &g, sf::RenderWindow &window, float (*heuristic)(unsigned int))
// {
//     std::priority_queue<std::tuple<unsigned int, float>> queue;
//     queue.emplace((g.start, heuristic(g.start)));
//     g.vertices[g.start].setState(State::visited);

//     while (!queue.empty())
//     {
//         auto [v, d] = queue.top();
//         queue.pop();

//         for (unsigned int n : g.vertices[v].neighbors)
//         {
//             if (g.vertices[n].state == State::notVisited)
//             {
//                 queue.emplace(n, heuristic(n));
//                 g.vertices[n].setState(State::visited);
//                 g.vertices[n].predecessor = v;

//                 window.clear();
//                 g.draw(window);
//                 window.display();
//             }
//         }

//         g.vertices[v].setState(State::finished);

//         window.clear();
//         g.draw(window);
//         window.display();

//         if (g.vertices[g.end].predecessor)
//         {
//             return;
//         }
//     }
// }
