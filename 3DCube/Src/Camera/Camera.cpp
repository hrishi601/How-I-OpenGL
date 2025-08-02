#include "Camera.h"
#include "Debuger.h"

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_REPEAT)
        LOG("E key pressed");

    switch (key)
    {
    case GLFW_KEY_W:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("W key pressed");
        break;
    case GLFW_KEY_S:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("S key pressed");
        break;
    case GLFW_KEY_A:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("A key pressed");
        break;
    case GLFW_KEY_D:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("D key pressed");
        break;
    }
}

 void Camera::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    
     Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
     if (!camera) return;

     if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
     {
         glm::vec2 NewMouseposition = glm::vec2(xpos, ypos);
         glm::vec2 MouseDelta = NewMouseposition - camera->m_OldMousePosition;

         if (glm::length(MouseDelta) > 25.0f)
         {
             camera->m_OldMousePosition = NewMouseposition;
             return;
         }

         camera->m_ViewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(MouseDelta.x), camera->m_Up)) * camera->m_ViewDirection;
         camera->m_ViewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(MouseDelta.y), glm::cross(camera->m_ViewDirection, camera->m_Up))) * camera->m_ViewDirection;
         camera->m_OldMousePosition = NewMouseposition;
	 }

	
	
}

 Camera::Camera(GLFWwindow* window) : m_Position(0.0f, 0.0f, 3.0f), m_ViewDirection(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f), m_OldMousePosition(0.0f, 0.0f)
{
    glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}



