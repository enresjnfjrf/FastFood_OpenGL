#include "Camera.h"

Camera::Camera(glm::vec3 position)
    :position(position), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f), pitch(0.0f), speed(1.0f), sensitivity(0.1f), fov(45.0f), znear(0.1f), zfar(1000.0f), aspectratio(16.f / 9.f)
{}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(fov, aspectratio, znear, zfar);
}

void Camera::ProcessKeyboard(int key, float deltaTime)
{
    float velocity = speed * deltaTime;
    if (key == GLFW_KEY_W) position += glm::normalize(front) * velocity;
    if (key == GLFW_KEY_S) position -= glm::normalize(front) * velocity;
    if (key == GLFW_KEY_A) position -= glm::normalize(glm::cross(front, up)) * velocity;
    if (key == GLFW_KEY_D) position += glm::normalize(glm::cross(front, up)) * velocity;
    if (key == GLFW_KEY_SPACE) position.y += velocity;
    if (key == GLFW_KEY_LEFT_CONTROL) position.y -= velocity;
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}

glm::vec3 Camera::GetPosition()
{
    return position;
}

glm::vec3 Camera::GetUp()
{
    return up;
}

glm::vec3 Camera::GetFront()
{
    return front;
}