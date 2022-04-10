#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <math.h>
#include <sstream>
#include <time.h>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Clock Clock;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(390, 390), "snek",
                            sf::Style::Default, settings);

    std::vector<sf::Vector2i> charles;

    sf::Vector2i dir(1, 0);
    sf::Vector2i lastdir(1, 0);

    sf::Vector2i fruit(15, 10);

    charles.push_back(sf::Vector2i(10, 10));
    charles.push_back(sf::Vector2i(9, 10));

    sf::Image gameboard;
    gameboard.create(40, 40, sf::Color(255, 255, 255));

    sf::Sprite display;
    sf::Texture texture;

    texture.loadFromImage(gameboard);
    display.setTexture(texture);

    display.setScale(10, 10);

    bool lost = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
	std::cout<<1/Clock.getElapsedTime().asSeconds()<<std::endl;
        if (!lost)
        {

            if (Clock.getElapsedTime().asMilliseconds() >= 150)
            {

                Clock.restart();

                charles.push_back(charles[charles.size() - 1] + dir);
                lastdir = dir;
                if (charles[charles.size() - 1] != fruit)
                {
                    charles.erase(charles.begin());
                }
                else
                {
                    bool invalid = true;
                    while (invalid)
                    {
                        fruit = sf::Vector2i(rand() % 20, rand() % 20);
                        invalid = false;
                        for (int i = 0; i < charles.size(); i++)
                        {
                            if (charles[i] == fruit)
                            {
                                invalid = true;
                            }
                        }
                    }
                }
            }

            if (charles[charles.size() - 1].x >= 20)
            {
                lost = true;
            }
            else if (charles[charles.size() - 1].x < 0)
            {
                lost = true;
            }
            else if (charles[charles.size() - 1].y >= 20)
            {
                lost = true;
            }
            else if (charles[charles.size() - 1].y < 0)
            {
                lost = true;
            }
            else
            {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    // left key is pressed: move our character
                    if (lastdir.x != 1)
                    {
                        dir = sf::Vector2i(-1, 0);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    // left key is pressed: move our character
                    if (lastdir.x != -1)
                    {
                        dir = sf::Vector2i(1, 0);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    // left key is pressed: move our character
                    if (lastdir.y != 1)
                    {
                        dir = sf::Vector2i(0, -1);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    // left key is pressed: move our character
                    if (lastdir.y != -1)
                    {
                        dir = sf::Vector2i(0, 1);
                    }
                }

                gameboard.create(40, 40, sf::Color(255, 255, 255));
                for (int i = charles.size() - 1; i >= 0; i--)
                {
                    gameboard.setPixel(charles[i].x * 2, charles[i].y * 2, sf::Color(0, 200 - (((100 - (400 / (charles.size() + 3))) * i) / charles.size()), 255));

                    if (i != 0)
                    {
                        gameboard.setPixel(charles[i].x + charles[i - 1].x, charles[i].y + charles[i - 1].y, sf::Color(0, 200 - (((100 - (400 / (charles.size() + 3))) * (i - 0.5)) / charles.size()), 255));
                    }
                }

                for (int i = 0; i < charles.size() - 1; i++)
                {
                    if (charles[i] == charles[charles.size() - 1])
                    {
                        lost = true;
                    }
                }
            }

            gameboard.setPixel(fruit.x * 2, fruit.y * 2, sf::Color(255, 0, 0));
        }
        texture.loadFromImage(gameboard);
        window.draw(display);
        window.display();
    }

    return EXIT_SUCCESS;
}
