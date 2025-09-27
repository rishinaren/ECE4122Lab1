#pragma once
#include <SFML/Graphics.hpp>

class ECE_LaserBlast : public sf::Sprite
{
private:
    sf::Texture texture;
    sf::Vector2f velocity;
    bool active;
    sf::RectangleShape laserShape; // Simple rectangle for laser visualization

public:
    ECE_LaserBlast();
    ~ECE_LaserBlast();
    
    // Initialize laser blast
    bool initialize();
    
    // Fire laser from position with direction
    void fire(sf::Vector2f startPos, sf::Vector2f direction);
    
    // Update laser position
    void update(float deltaTime);
    
    // Check collision with other objects
    bool checkCollision(const sf::Sprite& other);
    
    // Check if laser is active
    bool isActive() const;
    
    // Deactivate laser
    void deactivate();
    
    // Get bounds for collision detection
    sf::FloatRect getBounds() const;
    
    // Draw laser (custom draw since we use RectangleShape)
    void draw(sf::RenderWindow& window);
};