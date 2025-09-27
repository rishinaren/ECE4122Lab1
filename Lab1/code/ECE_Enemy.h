#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class ECE_Enemy : public sf::Sprite
{
private:
    sf::Texture texture;
    sf::Vector2f velocity;
    float speed;
    bool movingRight;
    static std::mt19937 randomGenerator;
    static std::uniform_int_distribution<int> fireProbability;
    sf::Vector2f windowSize;

public:
    ECE_Enemy();
    ~ECE_Enemy();
    
    // Load texture and initialize
    bool initialize(const std::string& texturePath, sf::Vector2f winSize);
    
    // Update enemy movement
    void update(float deltaTime);
    
    // Move enemy (left/right and down when hitting walls)
    void move(float deltaTime);
    
    // Check if should fire laser at random intervals
    bool shouldFire();
    
    // Check collision with other objects
    bool checkCollision(const sf::Sprite& other);
    
    // Get firing position (bottom center of enemy)
    sf::Vector2f getFiringPosition();
    
    // Set movement direction
    void setMovingRight(bool right);
    bool isMovingRight() const;
    
    // Move down (when hitting wall)
    void moveDown();
    
    // Check boundaries
    bool hitLeftWall() const;
    bool hitRightWall() const;
};