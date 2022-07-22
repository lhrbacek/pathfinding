#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <optional>
#include <vector>
#include <SFML/Graphics.hpp>

enum State
{
    notVisited,
    visited,
    finished
};

class Vertex
{
public:
    std::vector<unsigned int> neighbors = {}; // indexes of vertices array
    State state = notVisited;
    bool start = false;
    bool end = false;
    bool removed = false;
    std::optional<unsigned int> predecessor;

    void setPosition(unsigned int x, unsigned int y);

    void setStart(bool set);

    void setEnd(bool set);

    void setRemoved(bool set);

    void setState(State s);

    void setPath();

    void draw(sf::RenderWindow &window);

private:
    sf::RectangleShape shape{sf::Vector2f(50.f, 50.f)};
};

class Grid
{
public:
    std::vector<Vertex> vertices;
    int sizeX;
    int sizeY;
    unsigned int start = 0;
    unsigned int end;

    void init();

    void setStart(unsigned int vertex);

    void setEnd(unsigned int vertex);

    std::optional<unsigned int> getVertex(int x, int y, sf::Vector2u windowSize) const;

    void removeVertex(unsigned int v);

    void makePath();

    void draw(sf::RenderWindow &window);

    Grid(int gridSizeX, int gridSizeY);
};

#endif // PATHFINDING_H
