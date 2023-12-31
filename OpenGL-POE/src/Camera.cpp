#include <glm/gtx/vector_angle.hpp>

#include "../Headers/Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	this->width = width;
	this->height = height;
	this->Position = position;

	this->Orientation = glm::vec3(0.0f, 0.0f, -1.0f);

}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Makes camera look in the right direction from the right position
	viewMatrix = glm::lookAt(Position, Position + Orientation, Up);
	
	// Adds perspective to the scene
	projectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	camMatrix = projectionMatrix * viewMatrix;
	//Log the position of the camera
	//std::cout << "Camera Position: " << Position.x << ", " << Position.y << ", " << Position.z << std::endl;
	//std::cout << "Camera Orientation: " << Orientation.x << ", " << Orientation.y << ", " << Orientation.z << std::endl;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}


void Camera::Inputs(GLFWwindow* window, bool camLocked)
{
	//You Can then disable mouse inputs when its not needed.
	if(!camLocked)
	{
		HandleKeyInputs(window);
		HandleMouseInputs(window);
	}
	else
	{
		HandleCycle(window);
	}
	
}
void Camera::HandleMouseInputs(GLFWwindow* window)
{
	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}
void Camera::HandleKeyInputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}
}
void Camera::HandleCycle(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		MoveTo(cam_coords[0]);
	}if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		MoveTo(cam_coords[1]);
	}if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		MoveTo(cam_coords[2]);
	}
}
void Camera::MoveTo(const CamCoords& coords)
{
	// Calculate the new orientation to point towards the target position
	//glm::vec3 newOrientation = glm::normalize(targetPosition - Position);
	// Log this new orientation
	//std::cout << "New Orientation: " << newOrientation.x << ", " << newOrientation.y << ", " << newOrientation.z << std::endl;
	
	// Calculate the new up vector based on the current up vector
	// glm::vec3 newUp = glm::normalize(glm::cross(newOrientation, glm::cross(Orientation, Up)));

	// Set the new orientation and up vectors*
	//Orientation = newOrientation;
	//Up = newUp;

	// Set the camera position to the target position
	Position = coords.Position;
	Orientation = coords.Orientation;

	// Update the view matrix to reflect the changes
	//viewMatrix = glm::lookAt(Position, Position + Orientation, Up);

	// Recalculate the camera matrix
	//camMatrix = projectionMatrix * viewMatrix;
}
