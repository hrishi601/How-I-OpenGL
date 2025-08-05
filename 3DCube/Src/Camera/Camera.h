#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <GLFW/glfw3.h>

class Camera {

public:

	Camera(GLFWwindow* window);
	inline glm::mat4 GetWorldToViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_ViewDirection,m_Up); }
	glm::vec2 m_OldMousePosition;

	void UpdateCameraPosition(GLFWwindow* window);
	inline void SetMouseSens(float& Value) { MouseSensitivity = Value; };
	inline void SetMovementSens(float& Value) { MovementSensitivity = Value; };

private:

	glm::vec3 m_Position;
	glm::vec3 m_ViewDirection;
	const glm::vec3 m_Up;
	float MouseSensitivity = 0.25;
	float MovementSensitivity = 0.025;

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	
	

};
