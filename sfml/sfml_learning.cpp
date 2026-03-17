#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

sf::Vector2f Collision(std::vector<sf::FloatRect> edges[4], sf::FloatRect shape, sf::Vector2f speed);



int main(int argc, char* argv[])
{
    const int W_width = 1280;
    const int W_height = 800;

    sf::Vector2f rectspeed(0.072,-0.023);
    sf::Vector2f circlespeed(0.072, -0.023);

    sf::RenderWindow window(sf::VideoMode(W_width, W_height), "SFML works!", sf::Style::Default);
    
    sf::RectangleShape rectangle(sf::Vector2f(4.f,4.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(8,8);

    


    sf::CircleShape circle(8.f);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(25.f,25.f);

    const sf::FloatRect edgeT(0, 0, W_width, 1);
    const sf::FloatRect edgeL(0, 0, 1, W_height);
    const sf::FloatRect edgeB(W_width, W_height, -W_width, -1);
    const sf::FloatRect edgeR(W_width, W_height, -1, -W_height);

    std::vector<sf::FloatRect> edges[4];

    edges->push_back(edgeT); edges->push_back(edgeL); edges->push_back(edgeB); edges->push_back(edgeR);
    
    
    sf::VertexArray lines(sf::LinesStrip, 5);
    lines[0].position = sf::Vector2f(35.f, 35.f); 
    lines[1].position = sf::Vector2f(55.f, 55.f); 
    lines[2].position = sf::Vector2f(45.f, 55.f);
    lines[3].position = sf::Vector2f(75.f, 75.f); 
    lines[4].position = sf::Vector2f(75.f, 35.f); 

    lines[0].color = sf::Color::Green;
    lines[2].color = sf::Color::Green;
    lines[4].color = sf::Color::Green;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::FloatRect circle_hb = circle.getGlobalBounds();
        sf::FloatRect rect_hb = rectangle.getGlobalBounds();

        
        
        circlespeed = Collision(edges, circle_hb, circlespeed);
        rectspeed = Collision(edges, rect_hb, rectspeed);

       
        circle.move(circlespeed);
        rectangle.move(rectspeed);
       
       
        window.clear();
        

        window.draw(lines);
        window.draw(circle);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}

sf::Vector2f Collision(std::vector<sf::FloatRect> edges[4], sf::FloatRect shape, sf::Vector2f speed) {
    if (edges->at(0).intersects(shape)) {
        speed.y *= -1;
    }
    if (edges->at(1).intersects(shape)) {
        speed.x *= -1;
    }
    if (edges->at(2).intersects(shape)) {
        speed.y *= -1;
    }
    if (edges->at(3).intersects(shape)) {
        speed.x *= -1;
    }

    return speed;
}
