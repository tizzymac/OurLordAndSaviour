## The top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.18.3)

# Set up project name
project(OLAS)

# actually build something:
# build into an object called whatever the project name is
add_executable(${PROJECT_NAME} 
    main.cpp
)

# Build the Adder library
add_subdirectory(Adder)
# Build the glfw library
add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        Adder
        external/glfw/include
)

# Specify where to find the Adder library
# paths from the build folder
target_link_directories(${PROJECT_NAME} 
    PUBLIC
        Adder
        external/glfw/src
)

# link that library to our executable
# leave off "lib" prefix and ".a" extension
target_link_libraries(${PROJECT_NAME} adder glfw)