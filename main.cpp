#include <GLFW/glfw3.h>
#include <iostream>
#include <OLASConfig.h>

#ifdef USE_ADDER
    #include <adder.hpp>
#endif

int main(int argc, char *argv[])
{
    std::cout << "Rejoice!" << std::endl;

#ifdef USE_ADDER
    std::cout << "Using Adder lib: " << add(2, 2) << std::endl;
#else
    std::cout << 2 + 2 << std::endl;
#endif

    std::cout << argv[0] << " Version: " << OLAS_VERSION_MAJOR << "." << OLAS_VERSION_MINOR << std::endl;

    GLFWwindow *window;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(300, 300, "Gears", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}