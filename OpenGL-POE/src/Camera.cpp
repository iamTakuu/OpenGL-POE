#include <glm/gtx/vector_angle.hpp>

#include "../Headers/Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	this->width = width;
	this->height = height;
	this->Position = position;

	this->Orientation = glm::vec3(0.0f, 1.5f, -1.0f);
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Makes camera look in the right direction from the right position
	viewMatrix = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	camMatrix = projectionMatrix * viewMatrix;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}


// Rough draft of the camera movement. Will be improved later.
// Only swaps to se
void Camera::Input(GLFWwindow* window)
{

	/*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position = camCenter;*/
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camMatrix = glm::rotate(camMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		camMatrix = glm::translate(camMatrix, glm::vec3(0.1f, -0.1f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camMatrix = camMatrix = glm::rotate(camMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		camMatrix = glm::translate(camMatrix, glm::vec3(-0.1f, -0.1f, 0.0f));
	}
		

}