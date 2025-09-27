#include "ECE_Enemy.h"
#include <iostream>

// Static member initialization
std::mt19937 ECE_Enemy::randomGenerator(std::random_device{}());
std::uniform_int_distribution<int> ECE_Enemy::fireProbability(1, 1000);

ECE_Enemy::ECE_Enemy() : speed(50.0f), movingRight(true), windowSize(800.0f, 600.0f)
{
    velocity = sf::Vector2f(speed, 0.0f);
}

ECE_Enemy::~ECE_Enemy()
{
}

bool ECE_Enemy::initialize(const std::string& texturePath, sf::Vector2f winSize)
{
    windowSize = winSize;
    
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Error loading Enemy texture: " << texturePath << std::endl;
        return false;
    }
    
    setTexture(texture);
    
    // Scale sprite to reasonable size
    float scaleX = 40.0f / texture.getSize().x;
    float scaleY = 40.0f / texture.getSize().y;
    setScale(scaleX, scaleY);
    
    return true;
}

void ECE_Enemy::update(float deltaTime)
{
    move(deltaTime);
}

void ECE_Enemy::move(float deltaTime)
{
    sf::Vector2f currentPos = getPosition();
    
    if (movingRight)
    {
        currentPos.x += speed * deltaTime;
        if (hitRightWall())
        {
            movingRight = false;
            moveDown();
        }
    }
    else
    {
        currentPos.x -= speed * deltaTime;
        if (hitLeftWall())
        {
            movingRight = true;
            moveDown();
        }
    }
    
    setPosition(currentPos.x, currentPos.y);
}

bool ECE_Enemy::shouldFire()
{
    // Random chance to fire (adjust probability as needed)
    return fireProbability(randomGenerator) <= 2; // 0.2% chance per frame
}

bool ECE_Enemy::checkCollision(const sf::Sprite& other)
{
    return getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::Vector2f ECE_Enemy::getFiringPosition()
{
    sf::FloatRect bounds = getGlobalBounds();
    return sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height);
}

void ECE_Enemy::setMovingRight(bool right)
{
    movingRight = right;
}

bool ECE_Enemy::isMovingRight() const
{
    return movingRight;
}

void ECE_Enemy::moveDown()
{
    sf::Vector2f currentPos = getPosition();
    currentPos.y += 30.0f; // Move down by 30 pixels
    setPosition(currentPos.x, currentPos.y);
}

bool ECE_Enemy::hitLeftWall() const
{
    return getPosition().x <= 0;
}

bool ECE_Enemy::hitRightWall() const
{
    sf::FloatRect bounds = getGlobalBounds();
    return bounds.left + bounds.width >= windowSize.x;
}