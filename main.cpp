#include <cstring>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "algorithms.hpp"
#include "pathfinding.hpp"

std::tuple<int, int> getGridSize(const sf::RenderWindow &window)
{
    sf::Vector2u windowSize = window.getSize();
    return {(windowSize.x - 5) / 55, (windowSize.y - 5) / 55};
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "error, no algorithm chosen\n";
        return EXIT_FAILURE;
    }

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pathfinding");
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    auto [gridSizeX, gridSizeY] = getGridSize(window);

    Grid grid(gridSizeX, gridSizeY);

    grid.setStart(138);
    grid.setEnd(160);

    bool keyS = false;
    bool keyE = false;
    bool run = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Key::R)
                {
                    grid.init();
                }
                if (event.key.code == sf::Keyboard::Key::Space)
                {
                    run = true;
                }

                if (event.key.code == sf::Keyboard::Key::S)
                {
                    keyS = true;
                    keyE = false;
                }
                else if (event.key.code == sf::Keyboard::Key::E)
                {
                    keyE = true;
                    keyS = false;
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Key::S)
                {
                    keyS = false;
                }
                else if (event.key.code == sf::Keyboard::Key::E)
                {
                    keyE = false;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    std::optional<unsigned int> vertex = grid.getVertex(x, y, window.getSize());
                    if (!keyS && !keyE && vertex)
                    {
                        grid.removeVertex(*vertex);
                    }
                    if (keyS && vertex)
                    {
                        grid.setStart(*vertex);
                    }
                    if (keyE && vertex)
                    {
                        grid.setEnd(*vertex);
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        if (run)
        {
            if (strcmp("bfs", argv[1]) == 0)
            {
                bfs(grid, window);
            }
            else if (strcmp("dfs", argv[1]) == 0)
            {
                return 0;
            }
            // TBD

            run = false;
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
