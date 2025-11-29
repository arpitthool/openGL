#include <iostream>
#include <glad/glad.h>  // Include GLAD before GLFW (GLAD must be included before any OpenGL headers)
#include <GLFW/glfw3.h>
#include <cmath>

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";

const char* fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

int main() {

    // Note : all openGL object are accessed by references
    
    glfwInit(); // Initialize GLFW

    // tell the GLFW version we are using i.e. 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // tell the GLFW that we are using the core profile i.e. only the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // to save memory, we just need to store the vertices of the outer triangle and the inner midpoints to draw all 3 triangles
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3))/3, 0.0f, // left bottom corner of the triangle
        0.5f, -0.5f* float(sqrt(3))/3, 0.0f, // right bottom corner of the triangle
        0.0f, 0.5f* float(sqrt(3))*2/3, 0.0f, // top corner of the triangle
        -0.5f/2, 0.5f * float(sqrt(3))/6, 0.0f, // inner left 
        0.5f/2, 0.5f* float(sqrt(3))/6, 0.0f, // inner right 
        0.0f, -0.5f* float(sqrt(3))/3, 0.0f, // inner bottom

    }; // the position must be between -1.0 and 1.0, because the viewport is also between -1.0 and 1.0

    // to save memory, we can use indices to draw the triangles
    GLint indices[] = { 
        0, 3, 5, // lower left triangle
        3, 2, 4, // lower right triangle
        5, 4, 1, // upper triangle
    };

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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Set the source code of the vertex shader
    glCompileShader(vertexShader); // Compile the vertex shader

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Set the source code of the fragment shader
    glCompileShader(fragmentShader); // Compile the fragment shader

    GLuint shaderProgram = glCreateProgram(); // Create a shader program object
    glAttachShader(shaderProgram, vertexShader); // Attach the vertex shader to the shader program
    glAttachShader(shaderProgram, fragmentShader); // Attach the fragment shader to the shader program
    glLinkProgram(shaderProgram); // Link the shader program

    glDeleteShader(vertexShader); // Delete the vertex shader
    glDeleteShader(fragmentShader); // Delete the fragment shader

    GLuint VAO, VBO, EBO;
    int noOfObjects = 1, noOfVertices = 3;
    glGenVertexArrays(noOfObjects, &VAO); // Generate a vertex array object
    glGenBuffers(noOfObjects, &VBO); // Generate a buffer object
    glGenBuffers(noOfObjects, &EBO); // Generate a buffer object for the indices

    glBindVertexArray(VAO); // Bind the vertex array object

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy the vertices data to the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the buffer object for the indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Copy the indices data to the buffer

    int positionOfVertexAttribute = 0;
    glVertexAttribPointer(positionOfVertexAttribute, noOfVertices, GL_FLOAT, GL_FALSE, noOfVertices * sizeof(float), (void*)0); // Set the vertex attribute pointer
    glEnableVertexAttribArray(positionOfVertexAttribute); // Enable the vertex attribute

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer object
    glBindVertexArray(0); // Unbind the vertex array object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer object for the indices

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the background color to a light blue color, 
    // the last parameter is the alpha value which is 1.0f for fully opaque

    glClear(GL_COLOR_BUFFER_BIT); // clean the buffer and assign new to it

    // now to show the color we need to swap the back buffer with the front buffer
    glfwSwapBuffers(window); // Swap the back buffer with the front buffer

    while (!glfwWindowShouldClose(window)) { // loop until the window is closed

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the background color to a light blue color, 
        glClear(GL_COLOR_BUFFER_BIT); // clean the buffer and assign new to it

        glUseProgram(shaderProgram); // Use the shader program
        glBindVertexArray(VAO); // Bind the vertex array object
        int startIndex = 0;
        // glDrawArrays(GL_TRIANGLES, startIndex, noOfVertices); // Draw the triangles
        int noOfIndices = sizeof(indices) / sizeof(indices[0]);
        glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0); // Draw the triangles using the indices
        glfwSwapBuffers(window); // Swap the back buffer with the front buffer

        glfwPollEvents(); // Poll for events because GLFW needs to process the events
    }

    glDeleteVertexArrays(noOfObjects, &VAO); // Delete the vertex array object
    glDeleteBuffers(noOfObjects, &VBO); // Delete the buffer object
    glDeleteProgram(shaderProgram); // Delete the shader program
    glDeleteBuffers(noOfObjects, &EBO); // Delete the buffer object for the indices

    glfwDestroyWindow(window); // Destroy the window
    glfwTerminate(); // Clean up GLFW when the program is done

    return 0; // Return success
}