#include <glm/gtx/vector_angle.hpp>

#include "../Headers/Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	this->width = width;
	this->height = height;
	this->Position = position;

	camLeft = glm::vec3(0.5f, 0.5f, 2.0f);
	camRight = glm::vec3(-0.5f, 0.5f, 2.0f);
	camCenter = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up); // Generates a view matrix
	glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane); // Generates a projection matrix
	// Exports the camera matrices to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

// Rough draft of the camera movement. Will be improved later.
// Only swaps to se
void Camera::Input(GLFWwindow* window)
{

	/*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position = camCenter;*/
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (Position == camLeft)
		{
			Position = camRight;
		}
		else if (Position == camRight)
		{
			Position = camCenter;
		}
		else if (Position == camCenter)
		{
			Position = camLeft;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (Position == camRight)
		{
			Position = camLeft;
		}
		else if (Position == camLeft)
		{
			Position = camCenter;
		}
		else if (Position == camCenter)
		{
			Position = camRight;
		}
	}
		

}