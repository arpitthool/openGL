#include <iostream>
#include <glad/glad.h>  // Include GLAD before GLFW (GLAD must be included before any OpenGL headers)
#include <GLFW/glfw3.h>
#include <cmath>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// to save memory, we just need to store the vertices of the outer triangle and the inner midpoints to draw all 3 triangles
// GLfloat vertices[] =
// { //               COORDINATES                  /     COLORS           //
// 	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
// 	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
// 	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
// 	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
// 	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
// 	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
// }; // the position must be between -1.0 and 1.0, because the viewport is also between -1.0 and 1.0

// // to save memory, we can use indices to draw the triangles
// GLuint indices[] = { 
//     0, 3, 5, // lower left triangle
//     3, 2, 4, // lower right triangle
//     5, 4, 1, // upper triangle
// };

// Square
// GLfloat vertices[] =
// { //               COORDINATES                  /     COLORS           //
// 	-0.5f, -0.5f , 0.0f,     1.0f, 0.0f,  0.0f, 0.0f, 0.0f, // Lower left corner
// 	 -0.5f, 0.5f , 0.0f,     0.0f, 1.0f,  0.0f, 0.0f, 1.0f, // upper left corner
// 	 0.5f,  0.5f , 0.0f,     0.0f, 0.0f,  1.0f, 1.0f, 1.0f, // Upper right corner
// 	 0.5f, -0.5f , 0.0f,     1.0f, 1.0f,  1.0f, 1.0f, 0.0f  // Lower right corner
// }; // the position must be between -1.0 and 1.0, because the viewport is also between -1.0 and 1.0

// // to save memory, we can use indices to draw the triangles
// GLuint indices[] = { 
//     0, 2, 1, // upper triangle
//     0, 3, 2, // lower triangle
// };

// Pyramid
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // Link the position attribute to the VAO
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Link the color attribute to the VAO
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Link the texture coordinate attribute to the VAO 
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // Get the location of the scale uniform

    // textures
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    int noOfChannels = 4;
    unsigned char* bytes = stbi_load("../resources/textures/brick.png", &widthImg, &heightImg, &numColCh, noOfChannels);

    GLuint texture;
    int noOfTextures = 1;
    glGenTextures( noOfTextures, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0"); // Get the location of the texture uniform
    shaderProgram.activate(); // Activate the shader program
    glUniform1i(tex0Uni, 0); // Set the texture unit to 0

    // float rotationAngle = 30.0f;
    // double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST); // Enable depth testing 

    Camera camera(screenWidth, screenHeight, glm::vec3(0.0f, 0.5f, 2.0f));

    while (!glfwWindowShouldClose(window)) { // loop until the window is closed

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the background color to a light blue color, 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean the buffer and assign new to it and we also clear the depth buffer

        shaderProgram.activate(); // Activate the shader program

        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // glm::mat4 model = glm::mat4(1.0f); // model matrix initialized to identity matrix
        // glm::mat4 view = glm::mat4(1.0f); // view matrix initialized to identity matrix
        // glm::mat4 proj = glm::mat4(1.0f); // projection matrix initialized to identity matrix

        // we rotate the world around the y-axis by 0.5 degrees per frame
        // double crntTime = glfwGetTime();
        // if(crntTime - prevTime >= 1.0 / 60.0) { // 60 frames per second
        //     rotationAngle += 0.5f;
        //     prevTime = crntTime;
        // }

        // // we rotate the world around the y-axis 
        // model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        // // now our camera is at the origin looking at the negative z-axis ( into the screen )
        // // instead of moving the camera, we move the the world around the camera
        // view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        // proj = glm::perspective(glm::radians(45.0f), (float)(screenWidth )/ (float)(screenHeight), 0.1f, 100.0f); // 45 degree field of view, aspect ratio, near plane, far plane
        // // this means we will only see objects that are between 0.1 units and 100 units from the camera, otherwise they will be clipped

        // int modelLoc = glGetUniformLocation(shaderProgram.ID, "model"); // Get the location of the model uniform
        // int viewLoc = glGetUniformLocation(shaderProgram.ID, "view"); // Get the location of the view uniform
        // int projLoc = glGetUniformLocation(shaderProgram.ID, "proj"); // Get the location of the projection uniform

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Set the model matrix
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); // Set the view matrix
        // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj)); // Set the projection matrix

        // glUnifo rm1f(uniID, 0.5f); // Set the scale to 0.5, so we actually set the length 1 + 0.5 = 1.5 times the original length, 
        // this should be called after the shader program is activated

        glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture to the texture unit

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
    glDeleteTextures(noOfTextures, &texture); // Delete the texture

    return 0; // Return success
}