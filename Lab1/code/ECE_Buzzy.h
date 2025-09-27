#pragma once
#include <SFML/Graphics.hpp>

class ECE_Buzzy : public sf::Sprite
{
private:
    sf::Texture texture;
    float speed;
    sf::Vector2f windowSize;

public:
    ECE_Buzzy();
    ~ECE_Buzzy();
    
    // Load texture and initialize
    bool initialize(const std::string& texturePath, sf::Vector2f winSize);
    
    // Update position based on input
    void update(sf::Keyboard::Key key);
    
    // Check collision with other objects  
    bool checkCollision(const sf::Sprite& other);
    
    // Get/Set position
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    
    // Boundary checking
    void checkBoundaries();
};