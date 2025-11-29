#include <iostream>
#include <glad/glad.h>  // Include GLAD before GLFW (GLAD must be included before any OpenGL headers)
#include <GLFW/glfw3.h>
#include <cmath>
#include "../headers/shaderClass.h"
#include "../headers/VAO.h"
#include "../headers/VBO.h"
#include "../headers/EBO.h"

// to save memory, we just need to store the vertices of the outer triangle and the inner midpoints to draw all 3 triangles
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
}; // the position must be between -1.0 and 1.0, because the viewport is also between -1.0 and 1.0

// to save memory, we can use indices to draw the triangles
GLuint indices[] = { 
    0, 3, 5, // lower left triangle
    3, 2, 4, // lower right triangle
    5, 4, 1, // upper triangle
};

int main() {

    // Note : all openGL object are accessed by references
    
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
    
    Shader shaderProgram("../resources/shaders/default.vert", "../resources/shaders/default.frag"); // Create a shader program

    // Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	// VAO1.LinkVBO(VBO1, 0);
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


    while (!glfwWindowShouldClose(window)) { // loop until the window is closed

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the background color to a light blue color, 
        glClear(GL_COLOR_BUFFER_BIT); // clean the buffer and assign new to it

        shaderProgram.activate(); // Activate the shader program

        VAO1.Bind(); // Bind the VAO

        int startIndex = 0;
        // glDrawArrays(GL_TRIANGLES, startIndex, noOfVertices); // Draw the triangles
        int noOfIndices = sizeof(indices) / sizeof(indices[0]);
        glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0); // Draw the triangles using the indices
        glfwSwapBuffers(window); // Swap the back buffer with the front buffer

        glfwPollEvents(); // Poll for events because GLFW needs to process the events
    }

    VAO1.Delete(); // Delete the VAO
    VBO1.Delete(); // Delete the VBO
    EBO1.Delete(); // Delete the EBO
    shaderProgram.deleteShader(); // Delete the shader program

    glfwDestroyWindow(window); // Destroy the window
    glfwTerminate(); // Clean up GLFW when the program is done

    return 0; // Return success
}