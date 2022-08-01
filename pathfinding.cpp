#include "pathfinding.hpp"

#include <cmath>
#include <iostream>

void Vertex::setPosition(unsigned int x, unsigned int y)
{
    shape.setPosition(x, y);
}

void Vertex::setStart(bool set)
{
    start = set;
    if (set)
    {
        shape.setFillColor(sf::Color::Green);
        distance = 0;
    }
    else
    {
        shape.setFillColor(sf::Color::White);
        distance = std::numeric_limits<int>::max();
    }
}

void Vertex::setEnd(bool set)
{
    end = set;
    if (set)
    {
        shape.setFillColor(sf::Color::Red);
    }
    else
    {
        shape.setFillColor(sf::Color::White);
    }
}

void Vertex::setRemoved(bool set)
{
    removed = set;
    if (set)
    {
        shape.setFillColor(sf::Color(169, 169, 169));
    }
    else
    {
        shape.setFillColor(sf::Color::White);
    }
}

void Vertex::setState(State s)
{
    state = s;
    if (start || end)
    {
        return;
    }
    switch (state)
    {
    case notVisited:
        shape.setFillColor(sf::Color::White);
        break;
    case visited:
        shape.setFillColor(sf::Color::Blue);
        break;
    case finished:
        shape.setFillColor(sf::Color::Cyan);
        break;
    default:
        break;
    }
}

void Vertex::setPath()
{
    shape.setFillColor(sf::Color(255, 127, 0));
}

void Vertex::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void Grid::init()
{
    vertices.clear();

    for (int i = 0; i < sizeX * sizeY; i++)
    {
        Vertex v;
        v.setPosition(5 + (i % sizeX) * 55, 5 + (i / sizeX) * 55);

        if (i - sizeX >= 0) // top neighbor
        {
            v.neighbors.push_back(i - sizeX);
        }
        if (i % sizeX != 0) // left neighbor
        {
            v.neighbors.push_back(i - 1);
        }
        if (i + sizeX < sizeX * sizeY) // bottom neighbor
        {
            v.neighbors.push_back(i + sizeX);
        }
        if (i % sizeX != sizeX - 1) // right neighbor
        {
            v.neighbors.push_back(i + 1);
        }
        vertices.push_back(std::move(v));
    }

    vertices[start].setStart(true);
    vertices[end].setEnd(true);
}

void Grid::setStart(unsigned int vertex)
{
    vertices[start].setStart(false);
    vertices[vertex].setStart(true);
    start = vertex;
}

void Grid::setEnd(unsigned int vertex)
{
    vertices[end].setEnd(false);
    vertices[vertex].setEnd(true);
    end = vertex;
}

// TODO clarify magic numbers
std::optional<unsigned int> Grid::getVertex(int x, int y, sf::Vector2u windowSize) const
{
    if (x < 5 || y < 5)
    {
        return {};
    }
    x -= 5;
    y -= 5;
    if (x % 55 > 49 || y % 55 > 49) // clicked between vertices
    {
        return {};
    }

    int col = x / 55;
    int row = y / 55;
    if (col >= sizeX || row >= sizeY)
    {
        return {};
    }
    return col + row * 23;
}

void Grid::removeVertex(unsigned int v)
{
    for (unsigned int n : vertices[v].neighbors)
    {
        vertices[n].neighbors.erase(std::find(vertices[n].neighbors.begin(), vertices[n].neighbors.end(), v));
    }
    vertices[v].neighbors.clear();
    vertices[v].setRemoved(true);
}

void Grid::makePath()
{
    if (!(vertices[end].predecessor))
    {
        return;
    }

    unsigned int v = *(vertices[end].predecessor);
    while (v != start)
    {
        vertices[v].setPath();
        v = *(vertices[v].predecessor);
    }
    std::cout << vertices[end].distance << std::endl;
}

void Grid::draw(sf::RenderWindow &window)
{
    for (Vertex v : vertices)
    {
        v.draw(window);
    }
}

Grid::Grid(int gridSizeX, int gridSizeY)
    : sizeX(gridSizeX), sizeY(gridSizeY), end(gridSizeX * gridSizeY - 1)
{
    init();
}

unsigned int manhattanDistance(unsigned int v1, unsigned int v2, unsigned int gridSizeX)
{
    int x1 = v1 % gridSizeX;
    int y1 = v1 / gridSizeX;
    int x2 = v2 % gridSizeX;
    int y2 = v2 / gridSizeX;
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

float euclideanDistance(unsigned int v1, unsigned int v2, unsigned int gridSizeX)
{
    int x1 = v1 % gridSizeX;
    int y1 = v1 / gridSizeX;
    int x2 = v2 % gridSizeX;
    int y2 = v2 / gridSizeX;
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
