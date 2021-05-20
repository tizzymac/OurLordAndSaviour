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

target_include_directories(${PROJECT_NAME}
    PRIVATE
        Adder
)

# Specify where to find the Adder library
target_link_directories(${PROJECT_NAME} 
    PRIVATE
        Adder
)

# link that library to our executable
target_link_libraries(${PROJECT_NAME} adder)