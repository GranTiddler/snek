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
    // set basic sfml stuff
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Clock Clock;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(390, 390), "snek",
                            sf::Style::Default, settings);
    
    // this is the main body of the snake, his name is charles 
    std::vector<sf::Vector2i> charles;

    // sets direction to right
    sf::Vector2i dir(1, 0);
    sf::Vector2i lastdir(1, 0);

    //sets the fruit position
    sf::Vector2i fruit(15, 10);

    // make charles a little bit longer
    charles.push_back(sf::Vector2i(10, 10));
    charles.push_back(sf::Vector2i(9, 10));

    // make an image to draw the thing on the screen
    sf::Image gameboard;
    gameboard.create(40, 40, sf::Color(255, 255, 255));
	

    // texture to draw the image to
    sf::Sprite display;
    sf::Texture texture;

    texture.loadFromImage(gameboard);
    display.setTexture(texture);

    // make texture the right size
    display.setScale(10, 10);

    bool lost = false;

    // main window loop
    while (window.isOpen())
    {
	//get if game has been closed
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
	    
	// main game loop
        if (!lost)
        {
	    // get if time is long enough to advance the snake
            if (Clock.getElapsedTime().asMilliseconds() >= 150)
            {	
                Clock.restart();

		// move snake forward
                charles.push_back(charles[charles.size() - 1] + dir);
                lastdir = dir;
		// if snake is on a fruit make it longer
                if (charles[charles.size() - 1] != fruit)
                {
                    charles.erase(charles.begin());
                }
		// moves the fruit to an empty space
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
	    // set game to lost if charles has hit the wall
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
		// sets direction to whatever key was pressed last as long as that direction isn't oposite the current one
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                     // set direction to left
                    if (lastdir.x != 1)
                    {
                        dir = sf::Vector2i(-1, 0);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    // set direction to right
                    if (lastdir.x != -1)
                    {
                        dir = sf::Vector2i(1, 0);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                     // set direction to up
                    if (lastdir.y != 1)
                    {
                        dir = sf::Vector2i(0, -1);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                     // set direction to down
                    if (lastdir.y != -1)
                    {
                        dir = sf::Vector2i(0, 1);
                    }
                }
		// clears the board with white
                gameboard.create(40, 40, sf::Color(255, 255, 255));
                for (int i = charles.size() - 1; i >= 0; i--)
                {
		    // sets all main body pixels with a color that is gotten with a really bad equation that keeps it from changing too much in a short period
                    gameboard.setPixel(charles[i].x * 2, charles[i].y * 2, sf::Color(0, 200 - (((100 - (400 / (charles.size() + 3))) * i) / charles.size()), 255));

                    if (i != 0)
                    {
			// sets the pixels between all the main ones so it can leave a space between
                        gameboard.setPixel(charles[i].x + charles[i - 1].x, charles[i].y + charles[i - 1].y, sf::Color(0, 200 - (((100 - (400 / (charles.size() + 3))) * (i - 0.5)) / charles.size()), 255));
                    }
                }
		// checks if charles has run into himself
                for (int i = 0; i < charles.size() - 1; i++)
                {
                    if (charles[i] == charles[charles.size() - 1])
                    {
                        lost = true;
                    }
                }
            }
	    // sets the pixel with the fruit to red
            gameboard.setPixel(fruit.x * 2, fruit.y * 2, sf::Color(255, 0, 0));
        }
	    
	// displays texture on the screen
        texture.loadFromImage(gameboard);
        window.draw(display);
        window.display();
    }

    return EXIT_SUCCESS;
}
