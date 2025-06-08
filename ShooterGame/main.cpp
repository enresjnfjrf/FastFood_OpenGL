#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Building.h"
#include "Room.h"

int type_light = 0;

struct ModelTransform
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(0.5f, 0.5f, 0.5f);

    void setScale(float s) {
        scale.x = s;
        scale.y = s;
        scale.z = s;
    }
};

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

void processInput(GLFWwindow* window, Camera& camera, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_D, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_SPACE, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_LEFT_CONTROL, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        type_light = 0;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        type_light = 1;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        type_light = 2;
}

Light* flashLight, * blueLight, * redLight, * sunLight;

int main(void)
{
    const int vert = 36;
    float vertices[vert * 3] = {
        // Передняя грань
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // Задняя грань
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,

         // Левая грань
         -0.5f, -0.5f, -0.5f,
         -0.5f, -0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f, -0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f,  0.5f, -0.5f,

         // Правая грань
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,

          // Нижняя грань
          -0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, -0.5f,
           0.5f, -0.5f,  0.5f,
          -0.5f, -0.5f, -0.5f,
           0.5f, -0.5f,  0.5f,
          -0.5f, -0.5f,  0.5f,

          // Верхняя грань
          -0.5f,  0.5f, -0.5f,
          -0.5f,  0.5f,  0.5f,
           0.5f,  0.5f,  0.5f,
          -0.5f,  0.5f, -0.5f,
           0.5f,  0.5f,  0.5f,
           0.5f,  0.5f, -0.5f,
    };

    GLFWwindow* window;
#pragma region WINDOW INIT
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, 1280, 720);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

#pragma endregion

    Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));

    Shader* light_shader = new Shader("shaders\\light.vert", "shaders\\light.frag");
    Shader* model_shader = new Shader("shaders\\model.vert", "shaders\\model.frag");
    Shader* wall_shader = new Shader("shaders\\wall.vert", "shaders\\wall.frag");

    //Model drone("model/drone/Drone.obj", false);
    Model BusterDrone("model/drone2/source/model/BusterDrone.obj", false);
    Model People("model/people_small/people.obj", true);
    Model Donut("model/people_donut/obj file.obj", true);
    Model Baran("model/people_baran/obj file.obj", true);

    //Здание
    Building building;
    //new Room(x, y, z, width, height, lenght, thickness);

    // MainRoom
    Room* mainRoom = new Room(0.0f, 0.0f, 0.0f, 5.0f, 4.0f, 5.0f, 0.1f);
    float x = mainRoom->getX();
    float y = mainRoom->getY();
    float z = mainRoom->getZ();
    float width = mainRoom->getWidth();
    float height = mainRoom->getHeight();
    float length = mainRoom->getLength();
    float thickness = mainRoom->getThickness();
    mainRoom->createWall(x - thickness, y - thickness, z, width, thickness, length);
    /*mainRoom->createWall(x, y, z, width, height / 3.0f, thickness);
    mainRoom->createWall(x, y + (2.0f * height) / 3.0f, z, width, height / 3.0f, thickness);
    mainRoom->createWall(x - thickness, y, z - thickness, thickness, height, length);
    mainRoom->createWall(x - length - thickness, y, z + width, -width, height, thickness);
    mainRoom->createWall(x - length - thickness, y, z + width, thickness, height, -length);*/
    building.addRoom(mainRoom);

    ModelTransform lightTrans = { glm::vec3(0.f, 0.f, 0.f),
                                  glm::vec3(0.f, 0.f, 0.f),
                                  glm::vec3(0.3f, 0.3f, 0.3f)
    };

    Material cubeMaterial = { glm::vec3(0.25, 0.20725, 0.20725),
                             glm::vec3(1, 0.829, 0.829),
                             glm::vec3(0.296648, 0.296648, 0.296648),
                             12.f };

#pragma region LIGHT INIT
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vert * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::vector<Light*> lights;
    int total_lights = 4;
    int active_lights = 0;
    
    redLight = new Light("RedLamp", true);
    redLight->initLikePointLight(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(1.0f, 0.2f, 0.2f),
        glm::vec3(1.0f, 0.2f, 0.2f),
        1.0f, 0.1f, 0.09f
        );
    redLight->turnOff();
    lights.push_back(redLight);

    blueLight = new Light("BlueLamp", true);
    blueLight->initLikePointLight(
        glm::vec3(0.0f, 3.0f, 0.0f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.2f, 0.2f, 1.0f),
        glm::vec3(1.0f, 0.2f, 1.0f),
        1.0f, 0.1f, 0.09f
    );
    blueLight->turnOff();
    lights.push_back(blueLight);

    sunLight = new Light("Sun", true);
    sunLight->initLikeDirectionalLight(
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(0.3f, 0.3f, 0.3f),
        glm::vec3(0.6f, 0.6f, 0.6f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    //sunLight->turnOff();
    lights.push_back(sunLight);

    flashLight = new Light("FlashLight", true);
    flashLight->initLikeSpotLight(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::radians(10.f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.7f, 0.7f, 0.6f),
        glm::vec3(0.8f, 0.8f, 0.6f),
        1.0f, 0.1f, 0.1f
    );
    flashLight->turnOff();
    lights.push_back(flashLight);

#pragma endregion

    float lastFrame = 0.0f;
    float lastX = 1280.0f / 2.0f;
    float lastY = 720.0f / 2.0f;
    glfwSetCursorPos(window, lastX, lastY);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.f, 1.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera, deltaTime);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        camera.ProcessMouse(xoffset, yoffset);

        flashLight->setPosition(camera.GetPosition() - camera.GetUp() * 0.1f);
        flashLight->setDirection(camera.GetFront());
        //redLight->setPosition(glm::vec3(2.f, 0.8f * cos(glfwGetTime() * 2), 1.5f * sin(glfwGetTime() * 2)));
        //blueLight->setPosition(glm::vec3(2.f, 0.8f * cos(glfwGetTime() * 2 + glm::pi<float>()), 1.5f * sin(glfwGetTime() * 2 + glm::pi<float>())));

        glm::mat4 p = camera.GetProjectionMatrix();
        glm::mat4 v = camera.GetViewMatrix();
        glm::mat4 pv = p * v;
        glm::mat4 model;

        //LIGHT
        light_shader->Use();
        light_shader->SetMatrix4F("pv", pv);
        glBindVertexArray(VAO);

        //RedLight
        lightTrans.position = redLight->getPosition();
        lightTrans.setScale(0.1f);
        model = glm::mat4(1.f);
        model = glm::translate(model, lightTrans.position);
        model = glm::scale(model, lightTrans.scale);
        light_shader->SetMatrix4F("model", model);
        light_shader->SetVec3("lightColor", glm::vec3(1.0f, 0.2f, 0.2f));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ////BlueLight
        lightTrans.position = blueLight->getPosition();
        model = glm::mat4(1.f);
        model = glm::translate(model, lightTrans.position);
        model = glm::scale(model, lightTrans.scale);
        light_shader->SetMatrix4F("model", model);
        light_shader->SetVec3("lightColor", glm::vec3(0.2f, 0.2f, 1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //////White_people model
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model_shader->Use();
        model_shader->SetMatrix4F("pv", pv);
        model_shader->SetMatrix4F("model", model);
        model_shader->SetFloat("shininess", 64.0f);
        model_shader->SetVec3("viewPos", camera.GetPosition());
        People.Draw(model_shader);

        //////People_donut model
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model_shader->SetMatrix4F("model", model);
        Donut.Draw(model_shader);

        //////Baran model
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model_shader->SetMatrix4F("model", model);
        Baran.Draw(model_shader);

        //Здание
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
        wall_shader->Use();
        wall_shader->SetMatrix4F("pv", pv);
        wall_shader->SetMatrix4F("model", model);
        building.Draw();

        active_lights = 0;
        for (int i = 0; i < lights.size(); i++)
        {
            active_lights += lights[i]->putInshader(model_shader, active_lights);
        }
        model_shader->SetInt("lights_count", active_lights);

        //backpack.Draw(model_shader);
        //chair.Draw(model_shader);
        //drone.Draw(model_shader);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //delete polygon_shader;
    delete light_shader;
    delete model_shader;
    delete wall_shader;
    for (Light* light : lights) {
        delete light;
    }
    lights.clear();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}