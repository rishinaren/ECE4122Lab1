#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include "ECE_Buzzy.h"
#include "ECE_LaserBlast.h"
#include "ECE_Enemy.h"

class BuzzyDefenderGame
{
private:
    sf::RenderWindow window;
    sf::Vector2f windowSize;
    
    // Game objects
    ECE_Buzzy buzzy;
    std::vector<std::unique_ptr<ECE_Enemy>> enemies;
    std::vector<std::unique_ptr<ECE_LaserBlast>> playerLasers;
    std::vector<std::unique_ptr<ECE_LaserBlast>> enemyLasers;
    
    // Game state
    enum GameState { MENU, PLAYING, GAME_OVER };
    GameState currentState;
    
    // UI Elements
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text gameOverText;
    
    // Timing
    sf::Clock clock;
    sf::Time lastShotTime;
    sf::Time shotCooldown;
    
    // Input handling
    bool spacePressed;
    
public:
    BuzzyDefenderGame() : 
        windowSize(800, 600),
        window(sf::VideoMode(static_cast<unsigned int>(windowSize.x), static_cast<unsigned int>(windowSize.y)), "Buzzy Defender"),
        currentState(MENU),
        shotCooldown(sf::milliseconds(200)),
        spacePressed(false)
    {
        window.setFramerateLimit(60);
        initializeGame();
    }
    
    void initializeGame()
    {
        // Initialize Buzzy
        buzzy.initialize("graphics/buzzy.png", windowSize);
        
        // Create enemy grid (9x6 as shown in the image)
        createEnemyGrid();
        
        // Setup UI text (using default font since we may not have a font file)
        setupUI();
        
        currentState = MENU;
    }
    
    void createEnemyGrid()
    {
        enemies.clear();
        
        const int rows = 6;
        const int cols = 9;
        const float startX = 100.0f;
        const float startY = 150.0f;
        const float spacingX = 70.0f;
        const float spacingY = 60.0f;
        
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                auto enemy = std::make_unique<ECE_Enemy>();
                
                // Alternate between bulldog and tiger based on row
                std::string texturePath;
                if (row % 2 == 0)
                {
                    texturePath = "graphics/bulldog.png";
                }
                else
                {
                    texturePath = "graphics/tiger.png";
                }
                
                if (enemy->initialize(texturePath, windowSize))
                {
                    float x = startX + col * spacingX;
                    float y = startY + row * spacingY;
                    enemy->setPosition(x, y);
                    
                    // Set initial movement direction for the group
                    enemy->setMovingRight(true);
                    
                    enemies.push_back(std::move(enemy));
                }
            }
        }
    }
    
    void setupUI()
    {
        // Create text elements (using built-in font)
        titleText.setString("Buzzy Defender");
        titleText.setCharacterSize(48);
        titleText.setFillColor(sf::Color::Red);
        titleText.setPosition(windowSize.x/2 - 150, 200);
        
        startText.setString("Press Enter to Start");
        startText.setCharacterSize(24);
        startText.setFillColor(sf::Color::Black);
        startText.setPosition(windowSize.x/2 - 100, 300);
        
        gameOverText.setString("Game Over! Press Enter to Restart");
        gameOverText.setCharacterSize(24);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(windowSize.x/2 - 150, windowSize.y/2);
    }
    
    void handleInput()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (currentState == MENU || currentState == GAME_OVER)
                    {
                        startNewGame();
                    }
                }
                
                if (event.key.code == sf::Keyboard::Space && currentState == PLAYING)
                {
                    if (!spacePressed && (clock.getElapsedTime() - lastShotTime) >= shotCooldown)
                    {
                        fireBuzzyLaser();
                        spacePressed = true;
                        lastShotTime = clock.getElapsedTime();
                    }
                }
            }
            
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    spacePressed = false;
                }
            }
        }
        
        // Handle continuous movement
        if (currentState == PLAYING)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                buzzy.update(sf::Keyboard::Left);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                buzzy.update(sf::Keyboard::Right);
            }
        }
    }
    
    void startNewGame()
    {
        currentState = PLAYING;
        createEnemyGrid();
        playerLasers.clear();
        enemyLasers.clear();
        buzzy.initialize("graphics/buzzy.png", windowSize);
    }
    
    void fireBuzzyLaser()
    {
        auto laser = std::make_unique<ECE_LaserBlast>();
        if (laser->initialize())
        {
            sf::Vector2f buzzyPos = buzzy.getPosition();
            sf::FloatRect buzzyBounds = buzzy.getGlobalBounds();
            sf::Vector2f startPos(buzzyPos.x + buzzyBounds.width/2, buzzyPos.y);
            sf::Vector2f direction(0, -300); // Shoot upward
            
            laser->fire(startPos, direction);
            playerLasers.push_back(std::move(laser));
        }
    }
    
    void fireEnemyLaser(ECE_Enemy* enemy)
    {
        auto laser = std::make_unique<ECE_LaserBlast>();
        if (laser->initialize())
        {
            sf::Vector2f startPos = enemy->getFiringPosition();
            sf::Vector2f direction(0, 200); // Shoot downward
            
            laser->fire(startPos, direction);
            enemyLasers.push_back(std::move(laser));
        }
    }
    
    void update(float deltaTime)
    {
        if (currentState != PLAYING) return;
        
        // Update enemies
        for (auto& enemy : enemies)
        {
            enemy->update(deltaTime);
            
            // Random enemy firing
            if (enemy->shouldFire())
            {
                fireEnemyLaser(enemy.get());
            }
        }
        
        // Update lasers
        for (auto& laser : playerLasers)
        {
            laser->update(deltaTime);
        }
        
        for (auto& laser : enemyLasers)
        {
            laser->update(deltaTime);
        }
        
        // Check collisions
        checkCollisions();
        
        // Clean up inactive lasers
        playerLasers.erase(
            std::remove_if(playerLasers.begin(), playerLasers.end(),
                [](const std::unique_ptr<ECE_LaserBlast>& laser) { return !laser->isActive(); }),
            playerLasers.end());
            
        enemyLasers.erase(
            std::remove_if(enemyLasers.begin(), enemyLasers.end(),
                [](const std::unique_ptr<ECE_LaserBlast>& laser) { return !laser->isActive(); }),
            enemyLasers.end());
        
        // Check win/lose conditions
        checkGameState();
    }
    
    void checkCollisions()
    {
        // Player lasers vs enemies
        for (auto& laser : playerLasers)
        {
            if (!laser->isActive()) continue;
            
            for (auto it = enemies.begin(); it != enemies.end(); ++it)
            {
                if (laser->checkCollision(**it))
                {
                    laser->deactivate();
                    enemies.erase(it);
                    break;
                }
            }
        }
        
        // Enemy lasers vs Buzzy
        for (auto& laser : enemyLasers)
        {
            if (laser->isActive() && laser->checkCollision(buzzy))
            {
                currentState = GAME_OVER;
                return;
            }
        }
    }
    
    void checkGameState()
    {
        // Win condition: all enemies destroyed
        if (enemies.empty())
        {
            currentState = GAME_OVER;
        }
        
        // Lose condition: enemies reach Buzzy's level
        for (const auto& enemy : enemies)
        {
            if (enemy->getPosition().y >= buzzy.getPosition().y - 50)
            {
                currentState = GAME_OVER;
            }
        }
    }
    
    void render()
    {
        window.clear(sf::Color(100, 149, 237)); // Cornflower blue background
        
        if (currentState == MENU)
        {
            window.draw(titleText);
            window.draw(startText);
        }
        else if (currentState == PLAYING)
        {
            // Draw game objects
            window.draw(buzzy);
            
            for (const auto& enemy : enemies)
            {
                window.draw(*enemy);
            }
            
            for (const auto& laser : playerLasers)
            {
                laser->draw(window);
            }
            
            for (const auto& laser : enemyLasers)
            {
                laser->draw(window);
            }
        }
        else if (currentState == GAME_OVER)
        {
            window.draw(gameOverText);
        }
        
        window.display();
    }
    
    void run()
    {
        while (window.isOpen())
        {
            float deltaTime = clock.restart().asSeconds();
            
            handleInput();
            update(deltaTime);
            render();
        }
    }
};

int main()
{
    try
    {
        BuzzyDefenderGame game;
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}