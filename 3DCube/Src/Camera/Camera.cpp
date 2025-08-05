#include "Camera.h"
#include "Debuger.h"

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!camera) return;

    switch (key)
    {
    case GLFW_KEY_W:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            camera->m_Position.z += -0.1;
        }  
        break;
    case GLFW_KEY_S:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("S key pressed\n");
        break;
    case GLFW_KEY_A:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("A key pressed\n");
        break;
    case GLFW_KEY_D:
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            LOG("D key pressed\n");
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
         camera->m_ViewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-MouseDelta.x * camera->MouseSensitivity), camera->m_Up)) * camera->m_ViewDirection;
         camera->m_ViewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-MouseDelta.y * camera->MouseSensitivity), glm::cross(camera->m_ViewDirection, camera->m_Up))) * camera->m_ViewDirection;
         camera->m_OldMousePosition = NewMouseposition;
	 }

	
	
}

 Camera::Camera(GLFWwindow* window) : m_Position(0.0f, 0.0f, 3.0f), m_ViewDirection(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f), m_OldMousePosition(0.0f, 0.0f)
{
    glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

 void Camera::UpdateCameraPosition(GLFWwindow* window)
 {
     if (!window) return;

     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
         m_Position += m_ViewDirection * MovementSensitivity;
     if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
         m_Position += m_ViewDirection * -MovementSensitivity;
     if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
         m_Position += glm::cross(m_Up, m_ViewDirection) * MovementSensitivity;
     if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
         m_Position += glm::cross(m_Up, m_ViewDirection) * -MovementSensitivity;
     if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
         m_Position += m_Up * MovementSensitivity;
     if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
         m_Position += m_Up * -MovementSensitivity;

 }



