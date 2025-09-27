cmake_minimum_required(VERSION 3.16)
project(BuzzyDefender)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-all)

# Add executable
add_executable(BuzzyDefender
    code/main.cpp
    code/ECE_Buzzy.cpp
    code/ECE_LaserBlast.cpp
    code/ECE_Enemy.cpp
)

# Include directories
target_include_directories(BuzzyDefender PRIVATE ${SFML2_INCLUDE_DIRS})

# Link libraries
target_link_libraries(BuzzyDefender ${SFML2_LIBRARIES})

# Set compiler flags
target_compile_options(BuzzyDefender PRIVATE ${SFML2_CFLAGS_OTHER})