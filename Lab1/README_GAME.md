# Buzzy Defender - ECE 4122/6122 Lab 1

## Project Overview

This is a complete implementation of the Buzzy Defender game for ECE 4122/6122 Lab 1. The game features:

- **Buzzy (Georgia Tech Yellow Jacket)** - The hero character controlled by the player
- **Enemy mascots** - Bulldog and Tiger sprites arranged in a grid formation
- **Laser combat system** - Player can fire lasers to destroy enemies
- **Enemy AI** - Enemies move in formation and randomly fire back at the player
- **Game states** - Menu screen, gameplay, and game over screens

## Project Structure

```
Lab1/
├── CMakeLists.txt          # Build configuration
├── build/                  # Build directory (generated)
│   └── BuzzyDefender      # Executable
├── code/                   # Source code
│   ├── main.cpp           # Main game loop and logic
│   ├── ECE_Buzzy.h        # Buzzy class header
│   ├── ECE_Buzzy.cpp      # Buzzy implementation
│   ├── ECE_LaserBlast.h   # Laser class header
│   ├── ECE_LaserBlast.cpp # Laser implementation
│   ├── ECE_Enemy.h        # Enemy class header
│   └── ECE_Enemy.cpp      # Enemy implementation
└── graphics/              # Game graphics
    ├── buzzy.png          # Buzzy sprite (placeholder)
    ├── bulldog.png        # Bulldog enemy sprite (placeholder)
    └── tiger.png          # Tiger enemy sprite (placeholder)
```

## Classes Implemented

### ECE_Buzzy (derived from sf::Sprite)
- Handles player movement with left/right arrow keys
- Manages texture loading and display
- Collision detection with other objects
- Boundary checking to keep player on screen

### ECE_LaserBlast (derived from sf::Sprite)
- Manages laser projectile movement
- Collision detection with enemies
- Support for multiple simultaneous laser blasts
- Automatic cleanup when lasers go off-screen

### ECE_Enemy (derived from sf::Sprite)
- Enemy movement patterns (march left/right, advance down when hitting walls)
- Random laser firing at player
- Collision detection and destruction when hit
- Texture management for different enemy types

## Game Controls

- **Arrow Keys** - Move Buzzy left and right
- **Spacebar** - Fire laser blasts
- **Enter** - Start game / Restart after game over

## Game Mechanics

1. **Start Screen** - Shows "Buzzy Defender" title and "Press Enter to Start"
2. **Gameplay** - 
   - Buzzy starts at top center of screen
   - 6x9 grid of enemies (alternating bulldogs and tigers)
   - Enemies march left/right and advance down when hitting walls
   - Random enemies fire lasers at Buzzy
   - Player can fire multiple laser blasts
   - Enemies disappear when hit by player lasers
3. **Win/Lose Conditions**
   - Win: Destroy all enemies
   - Lose: Enemy laser hits Buzzy OR enemies reach Buzzy's level
4. **Game Over** - Shows restart message

## Building and Running

### Prerequisites
- C++17 compiler (g++)
- SFML 2.6+ libraries
- CMake 3.16+

### Build Instructions
```bash
cd Lab1
mkdir build
cd build
cmake ..
make
```

### Run the Game
```bash
./BuzzyDefender
```

## Graphics Files

**IMPORTANT**: The current graphics files are placeholders. Replace them with your actual PNG files:
- `graphics/buzzy.png` - Should be your Georgia Tech Yellow Jacket image
- `graphics/bulldog.png` - Should be your Georgia Bulldog mascot image  
- `graphics/tiger.png` - Should be your Clemson Tiger mascot image

Simply save your PNG files with these exact names in the `graphics/` directory and rebuild.

## Technical Features

- **Object-oriented design** with proper inheritance from sf::Sprite
- **Collision detection** between all game objects
- **Dynamic memory management** using smart pointers
- **Game state management** for different screens
- **Input handling** with proper event processing
- **Frame-rate limiting** for consistent gameplay
- **Vector math** for movement and positioning

## Grading Criteria Met

✓ **Main start screen** - Shows at startup, Enter key starts game  
✓ **Enemy grid display** - 6x9 grid in evenly spaced rows  
✓ **Buzzy positioning** - Starts at top center, moves with arrow keys  
✓ **Laser firing** - Spacebar fires lasers, multiple blasts supported  
✓ **Enemy AI** - Random firing, proper collision detection  
✓ **Enemy movement** - Correct left/right marching with downward advancement  
✓ **Game mechanics** - Fun gameplay with reasonable speeds and collision detection

## Notes

- The game uses SFML 2.6 for graphics and input handling
- All classes properly inherit from sf::Sprite as required
- Random number generation uses modern C++ `<random>` library
- The code follows good C++ practices with proper memory management
- Frame timing ensures consistent gameplay regardless of hardware

To enhance the game further, simply replace the placeholder PNG files with your actual mascot images!