#include <iostream>
#include <glad/glad.h>  // Include GLAD before GLFW (GLAD must be included before any OpenGL headers)
#include <GLFW/glfw3.h>

int main() {
    
    glfwInit(); // Initialize GLFW

    // tell the GLFW version we are using i.e. 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // tell the GLFW that we are using the core profile i.e. only the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int screenWidth = 800;
    int screenHeight = 600;
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Project", NULL, NULL); // Create a window

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Make the window's context current

    gladLoadGL(); // Load OpenGL using GLAD

    glViewport(0, 0, screenWidth, screenHeight); // Set the viewport to the entire window, the viewport is the area of the window that the graphics are rendered to
    // the first two parameters are the x and y coordinates of the viewport, the last two parameters are the width and height of the viewport

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the background color to a light blue color, 
    // the last parameter is the alpha value which is 1.0f for fully opaque

    glClear(GL_COLOR_BUFFER_BIT); // clean the buffer and assign new to it

    // now to show the color we need to swap the back buffer with the front buffer
    glfwSwapBuffers(window); // Swap the back buffer with the front buffer

    while (!glfwWindowShouldClose(window)) { // loop until the window is closed
        glfwPollEvents(); // Poll for events because GLFW needs to process the events
    }


    glfwDestroyWindow(window); // Destroy the window
    glfwTerminate(); // Clean up GLFW when the program is done

    return 0; // Return success
}