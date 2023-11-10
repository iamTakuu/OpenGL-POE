#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <vector>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"
struct CamCoords
{
	glm::vec3 Position;
	glm::vec3 Orientation;
};

class Camera
{
	public:
		// Position of the camera
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
		// Orientation of the camera
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		// Up vector of the camera
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		int width;
		int height;

		float speed = 0.1f;
		float sensitivity = 100.0f;

		// Takes in the width and height of the window, and the position of the camera
		Camera(int width, int height, glm::vec3 position);

		// Updates the camera matrix to the Vertex Shader
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

		// Exports the camera matrix to a shader
		void Matrix(Shader& shader, const char* uniform);
	
		void Inputs(GLFWwindow* window, bool camLocked);
		void HandleMouseInputs(GLFWwindow* window);
		void HandleKeyInputs(GLFWwindow* window);
		void HandleCycle(GLFWwindow* window);
		void MoveTo(const CamCoords& coords);

	private:
		// 3 Set points for the camera to move to
	// Camera matrix
		glm::mat4 camMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
	
		glm::mat4 m_identity = glm::mat4(1.0f);

		bool firstClick = true;
	

	const std::vector<CamCoords> cam_coords
	{
		CamCoords{glm::vec3(0.0f, 0.0f, 80.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
		CamCoords{glm::vec3(42.6f, 40.0f, 47.0f), glm::vec3(-0.57f, -0.52f, -0.64f)},
		CamCoords{glm::vec3(-48.0f, 46.5f, -39.0f), glm::vec3(0.62f, -0.61f, 0.48f)}
	};

};


#endif // !CAMERA_CLASS_H

