#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera :public Object{
    Window* window
public:
    Camera(GLFWwindow* window, int width, int height) : m_window(window), m_width(width), m_height(height) {
        // Initialize camera properties
        m_position = glm::vec3(0.0f, 0.0f, 3.0f);
        m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_yaw = -90.0f;
        m_pitch = 0.0f;
        m_movementSpeed = 2.5f;
        m_mouseSensitivity = 0.1f;
        m_fov = 45.0f;
    }

    // Process user input to update camera state
    void processInput(float deltaTime) {
        // Handle camera movement
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
            m_position += m_movementSpeed * deltaTime * m_front;
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
            m_position -= m_movementSpeed * deltaTime * m_front;
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_movementSpeed * deltaTime;
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
            m_position += glm::normalize(glm::cross(m_front, m_up)) * m_movementSpeed * deltaTime;

        // Handle mouse input for camera rotation
        double xPos, yPos;
        glfwGetCursorPos(m_window, &xPos, &yPos);
        if (m_firstMouse) {
            m_lastX = xPos;
            m_lastY = yPos;
            m_firstMouse = false;
        }

        float xOffset = xPos - m_lastX;
        float yOffset = m_lastY - yPos;
        m_lastX = xPos;
        m_lastY = yPos;

        xOffset *= m_mouseSensitivity;
        yOffset *= m_mouseSensitivity;

        m_yaw += xOffset;
        m_pitch += yOffset;

        if (m_pitch > 89.0f) m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = -89.0f;

        updateCameraVectors();
    }

    // Get the view matrix
    glm::mat4 getViewMatrix() const {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    // Get the projection matrix
    glm::mat4 getProjectionMatrix() const {
        return glm::perspective(glm::radians(m_fov), static_cast<float>(m_width) / m_height, 0.1f, 100.0f);
    }

private:
    // GLFW window reference
    GLFWwindow* m_window;

    // Window dimensions
    int m_width, m_height;

    // Camera attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    float m_yaw;
    float m_pitch;

    // Camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_fov;

    // Input tracking
    double m_lastX = 0.0;
    double m_lastY = 0.0;
    bool m_firstMouse = true;

    // Update front vector based on yaw and pitch
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
    }
};
