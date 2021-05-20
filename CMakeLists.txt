cmake_minimum_required(VERSION 3.18.3)

# Set up project name
project(OLAS)

# actually build something:
# build into an object called whatever the project name is
add_executable(${PROJECT_NAME} main.cpp)