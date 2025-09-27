#include "ECE_Buzzy.h"
#include <iostream>

ECE_Buzzy::ECE_Buzzy() : speed(200.0f), windowSize(800.0f, 600.0f)
{
}

ECE_Buzzy::~ECE_Buzzy()
{
}

bool ECE_Buzzy::initialize(const std::string& texturePath, sf::Vector2f winSize)
{
    windowSize = winSize;
    
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Error loading Buzzy texture: " << texturePath << std::endl;
        return false;
    }
    
    setTexture(texture);
    
    // Scale sprite to reasonable size (adjust as needed)
    float scaleX = 50.0f / texture.getSize().x;
    float scaleY = 50.0f / texture.getSize().y;
    setScale(scaleX, scaleY);
    
    // Start at top center of screen
    setPosition(windowSize.x / 2.0f - getGlobalBounds().width / 2.0f, 50.0f);
    
    return true;
}

void ECE_Buzzy::update(sf::Keyboard::Key key)
{
    sf::Vector2f currentPos = getPosition();
    
    if (key == sf::Keyboard::Left)
    {
        currentPos.x -= speed * 0.016f; // Assuming ~60 FPS
    }
    else if (key == sf::Keyboard::Right)
    {
        currentPos.x += speed * 0.016f; // Assuming ~60 FPS
    }
    
    setPosition(currentPos.x, currentPos.y);
    checkBoundaries();
}

bool ECE_Buzzy::checkCollision(const sf::Sprite& other)
{
    return getGlobalBounds().intersects(other.getGlobalBounds());
}

void ECE_Buzzy::setPosition(float x, float y)
{
    sf::Sprite::setPosition(x, y);
}

sf::Vector2f ECE_Buzzy::getPosition() const
{
    return sf::Sprite::getPosition();
}

void ECE_Buzzy::checkBoundaries()
{
    sf::Vector2f pos = getPosition();
    sf::FloatRect bounds = getGlobalBounds();
    
    // Keep within screen boundaries
    if (pos.x < 0)
    {
        pos.x = 0;
    }
    else if (pos.x + bounds.width > windowSize.x)
    {
        pos.x = windowSize.x - bounds.width;
    }
    
    setPosition(pos.x, pos.y);
}