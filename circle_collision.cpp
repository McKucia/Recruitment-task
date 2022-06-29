#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 1000), "Circle collision");
    sf::CircleShape circle(100.f);
	sf::RectangleShape rectangle(sf::Vector2f(50, 100));

    circle.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle);
		window.draw(rectangle);
        window.display();
    }

    return 0;
}