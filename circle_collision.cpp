#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <iostream>
#include <tuple>

const float WIDTH = 900, HEIGHT = 600;
const sf::Vector2f recLocalPos(570.0f, 260.0f);

float findDistance(float &fromX, float &fromY, float &toX, float &toY){
    float a = std::abs(fromX - toX);
    float b = std::abs(fromY - toY);
 
    return std::sqrt((a * a) + (b * b));
}

bool isColliding(const sf::CircleShape &circle, const sf::RectangleShape &rectangle) {
    float circleX = circle.getPosition().x;
    float circleY = circle.getPosition().y;

    float rectX = recLocalPos.x - rectangle.getSize().x / 2;
    float rectY = recLocalPos.y - rectangle.getSize().y / 2;

    float angleRad = rectangle.getRotation() * M_PI / 180;
    float rectCenterX = rectangle.getPosition().x;
    float rectCenterY = rectangle.getPosition().y;
    
    float cx = std::cos(-angleRad) * (circleX - rectCenterX) - std::sin(-angleRad) * (circleY - rectCenterY) + rectCenterX;
    float cy = std::sin(-angleRad) * (circleX - rectCenterX) + std::cos(-angleRad) * (circleY - rectCenterY) + rectCenterY;
    
    float closestX, closestY;

    if (cx  < rectX)
        closestX = rectX;
    else if (cx  > rectX + rectangle.getSize().x)
        closestX = rectX + rectangle.getSize().x;
    else
        closestX = cx;
    
    if (cy < rectY) 
        closestY = rectY;
    else if (cy > rectY + rectangle.getSize().y)
        closestY = rectY + rectangle.getSize().y;
    else 
        closestY = cy;
    
    bool collision = false;
     
    float distance = findDistance(cx, cy, closestX, closestY);

    if (distance < circle.getRadius())
        collision = true;
    else
        collision = false;

    return collision;
}

int main()
{
    sf::ContextSettings settings(0U, 0U, 20, 1U, 1U, 0U, false);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Circle collision", sf::Style::Close, settings);
    window.setFramerateLimit(60);
    sf::CircleShape circle(90.f);
	sf::RectangleShape rectangle(sf::Vector2f(50.0f, 100.0f));

    circle.setFillColor(sf::Color(237, 28, 36));
	rectangle.setFillColor(sf::Color(255, 174, 201));

    circle.setOutlineThickness(3);
    rectangle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::Black);

    sf::FloatRect circlePos = circle.getLocalBounds();
    circle.setOrigin(circlePos.left + circlePos.width / 2.0f, circlePos.top  + circlePos.height / 2.0f);
    circle.setPosition(sf::Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));

    sf::FloatRect rectanglePos = rectangle.getLocalBounds();
    rectangle.setOrigin(rectanglePos.left + rectanglePos.width / 2.0f, rectanglePos.top  + rectanglePos.height / 2.0f);
    rectangle.setPosition(recLocalPos);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            rectangle.rotate(3.0f);
        
        auto colliding = isColliding(circle, rectangle);

        if(colliding) {
            circle.setFillColor(sf::Color(34, 176, 75));
            rectangle.setFillColor(sf::Color(181, 230, 29));
        }
        else {
            circle.setFillColor(sf::Color(237, 28, 36));
            rectangle.setFillColor(sf::Color(255, 174, 201));
        }

        window.clear(sf::Color::White);
        window.draw(circle);
		window.draw(rectangle);
        window.display();
    }

    return 0;
}