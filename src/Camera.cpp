#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f); // identity matrix
	glm::mat4 projection = glm::mat4(1.0f); // identity matrix

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane); // perspective projection matrix
	// i.e. we create a perspective projection matrix that projects 3D points onto a 2D plane
	// FOVdeg is the field of view angle in degrees
	// width and height are the width and height of the window
	// nearPlane and farPlane are the near and far planes of the frustum for clipping

	// Sets new camera matrix
	cameraMatrix = projection * view; // camera matrix is the product of the projection matrix and the view matrix
	// i.e. we create a camera matrix that projects 3D points onto a 2D plane
	// and then we look at the scene from the camera's position
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}



void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up)); // normalize the cross product of the orientation and the up vector
		// i.e. we get the direction of the camera's left side
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up)); // normalize the cross product of the orientation and the up vector
		// i.e. we get the direction of the camera's right side
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	// Handles camera rotation with left and right arrow keys
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		// Rotate camera left (yaw left) - rotate Orientation around Up axis
		Orientation = glm::rotate(Orientation, glm::radians(-sensitivity * 0.01f), Up);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		// Rotate camera right (yaw right) - rotate Orientation around Up axis
		Orientation = glm::rotate(Orientation, glm::radians(sensitivity * 0.01f), Up);
	}
}