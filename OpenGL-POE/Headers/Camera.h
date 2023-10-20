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
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
		// Orientation of the camera
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		// Up vector of the camera
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		// Camera matrix
		glm::mat4 camMatrix = glm::mat4(1.0f);

		int width;
		int height;

		float speed = 0.1f;
		bool needsUpdate;
		//float sensitivity = 100.0f;

		// Takes in the width and height of the window, and the position of the camera
		Camera(int width, int height, glm::vec3 position);

		// Updates the camera matrix to the Vertex Shader
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

		// Exports the camera matrix to a shader
		void Matrix(Shader& shader, const char* uniform);

		// Processes input received from any keyboard-like input system.
		void Input(GLFWwindow* window);

		void rotateMatrix(GLfloat angle, glm::vec3 axis);
		void initMatrix(float FOVdeg, float nearPlane, float farPlane);

	private:
		// 3 Set points for the camera to move to
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);

};


#endif // !CAMERA_CLASS_H

