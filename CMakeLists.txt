## The top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.18.3)

# Set up project name
project(OLAS VERSION 1.0)

### ADDER STUFF
# Option for weather or not to use the Adder lib
option(USE_ADDER "A simple library for adding two ints." ON)

if (USE_ADDER)
    # Build the Adder library
    add_subdirectory(Adder)

    list(APPEND EXTRA_LIBS Adder)
    list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Adder)

endif()
###

# Setup config files
configure_file(OLASConfig.h.in OLASConfig.h)

# actually build something:
# build into an object called whatever the project name is
add_executable(${PROJECT_NAME} 
    main.cpp
)

# The binary dir is where we write OLAS_Config.h out to
# This will have the version number
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# Download all the submodules
find_path(Git QUIET)
if (GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/.git)
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Updating submodules...")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "Git submodule update failed with ${GIT_SUBMOD_RESULT}")
        else()
            message(STATUS "Done updating submodules")
        endif()
    endif()
endif()

# Check all the submodules (make sure they exist)
if (NOT EXISTS ${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt)
    message(FATAL_ERROR "The glfw submodule was not downloaded!")
endif()

# Build the glfw library
add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        external/glfw/include
        ${EXTRA_INCLUDES}
)

# paths from the build folder
target_link_directories(${PROJECT_NAME} 
    PUBLIC
        external/glfw/src
        ${EXTRA_LIBS}
)

# link that library to our executable
# leave off "lib" prefix and ".a" extension
target_link_libraries(${PROJECT_NAME} 
    glfw
    ${EXTRA_LIBS}
)