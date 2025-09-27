#include "ECE_LaserBlast.h"
#include <iostream>

ECE_LaserBlast::ECE_LaserBlast() : velocity(0.0f, 0.0f), active(false)
{
}

ECE_LaserBlast::~ECE_LaserBlast()
{
}

bool ECE_LaserBlast::initialize()
{
    // Create a simple laser visualization using rectangle
    laserShape.setSize(sf::Vector2f(3.0f, 15.0f));
    laserShape.setFillColor(sf::Color::Yellow);
    active = false;
    
    return true;
}

void ECE_LaserBlast::fire(sf::Vector2f startPos, sf::Vector2f direction)
{
    laserShape.setPosition(startPos);
    velocity = direction;
    active = true;
}

void ECE_LaserBlast::update(float deltaTime)
{
    if (!active) return;
    
    sf::Vector2f currentPos = laserShape.getPosition();
    currentPos += velocity * deltaTime;
    laserShape.setPosition(currentPos);
    
    // Deactivate if laser goes off screen
    if (currentPos.y < 0 || currentPos.y > 600 || currentPos.x < 0 || currentPos.x > 800)
    {
        active = false;
    }
}

bool ECE_LaserBlast::checkCollision(const sf::Sprite& other)
{
    if (!active) return false;
    
    return laserShape.getGlobalBounds().intersects(other.getGlobalBounds());
}

bool ECE_LaserBlast::isActive() const
{
    return active;
}

void ECE_LaserBlast::deactivate()
{
    active = false;
}

sf::FloatRect ECE_LaserBlast::getBounds() const
{
    return laserShape.getGlobalBounds();
}

void ECE_LaserBlast::draw(sf::RenderWindow& window)
{
    if (active)
    {
        window.draw(laserShape);
    }
}