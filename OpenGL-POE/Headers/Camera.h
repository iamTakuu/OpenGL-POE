#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
	public:
		// Position of the camera
		glm::vec3 Position;
		// Orientation of the camera
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		// Up vector of the camera
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		int width;
		int height;

		float speed = 0.1f;
		//float sensitivity = 100.0f;

		Camera(int width, int height, glm::vec3 position);

		// Set up the camera perspective, and the view matrix to the shader.
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

		// Processes input received from any keyboard-like input system.
		void Input(GLFWwindow* window);

	private:
		// 3 Set points for the camera to move to
		glm::vec3 camLeft;
		glm::vec3 camRight;
		glm::vec3 camCenter;

};


#endif // !CAMERA_CLASS_H

