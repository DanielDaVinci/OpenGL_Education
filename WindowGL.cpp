#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>

using namespace std;

ostream& operator << (ostream& out, glm::vec3& vector)
{
    out << vector.x << " " << vector.y << " " << vector.z;
    return out;
}

#include "engine/graphic/Shader.h"
#include "engine/objects/Camera.h"
#include "engine/graphic/Model.h"
#include "engine/screen/Frame.h"

Camera sceneCamera = Camera(800, 600, 45.0f, { 0.0f, 0.0f, 0.0f }, { 0.0f, -90.0f, 0.0f });

bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

GLfloat lastX = 400, lastY = 300;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static GLfloat firstMouse = true;

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    glm::vec3 angles = sceneCamera.getAngle();
    angles.x += yoffset;
    angles.y += xoffset;

    angles.x = glm::clamp(angles.x, -89.0f, 89.0f);

    sceneCamera.setAngle(angles);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    GLfloat zoomSpeed = 1.0f;
    GLfloat FOV = sceneCamera.getFOV() - yoffset * zoomSpeed;
    sceneCamera.setFOV(glm::max(glm::min(FOV, 60.0f), 1.0f));
}

void do_movement(GLfloat deltaTime)
{
    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
        sceneCamera.setPosition(sceneCamera.getPosition() + sceneCamera.getFrontDirection() * cameraSpeed);
    if (keys[GLFW_KEY_S])
        sceneCamera.setPosition(sceneCamera.getPosition() - sceneCamera.getFrontDirection() * cameraSpeed);
    if (keys[GLFW_KEY_A])
        sceneCamera.setPosition(sceneCamera.getPosition() - sceneCamera.getRightDirection() * cameraSpeed);
    if (keys[GLFW_KEY_D])
        sceneCamera.setPosition(sceneCamera.getPosition() + sceneCamera.getRightDirection() * cameraSpeed);
}

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, (1920 - WIDTH) / 2, (1080 - HEIGHT) / 2);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastX = xpos;
    lastY = ypos;

    glewExperimental = GL_TRUE;

    glewInit();

    int winWidth, winHeight;
    glfwGetFramebufferSize(window, &winWidth, &winHeight);
    glViewport(0, 0, winWidth, winHeight);

    glEnable(GL_DEPTH_TEST);

    Frame frame(winWidth, winHeight);

    Shader shader("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");
    Shader strokeShader("Data/Shaders/strokeShader.vs", "Data/Shaders/strokeShader.frag");
    Shader frameShader("Data/Shaders/frameShader.vs", "Data/Shaders/frameShader.frag");

    Model ourModel("resources/objects/backpack/backpack.obj");
    Model secondModel = ourModel;

    GLfloat currentTime = glfwGetTime();
    GLfloat lastTime = currentTime;
    GLfloat deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        currentTime = (GLfloat)glfwGetTime();
        deltaTime = currentTime - lastTime;

        frame.Bind();

        glEnable(GL_DEPTH_TEST);

        do_movement(deltaTime);

        glfwSetWindowTitle(window, to_string(int(1.0f / deltaTime)).c_str());

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        //shader.setUniform("spotLight.position", sceneCamera.getPosition());
        //shader.setUniform("spotLight.direction", sceneCamera.getFrontDirection());
        //shader.setUniform("spotLight.innerAngle", glm::cos(glm::radians(12.5f)));
        //shader.setUniform("spotLight.outerAngle", glm::cos(glm::radians(17.5f)));
        //shader.setUniform("spotLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        //shader.setUniform("spotLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        //shader.setUniform("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        //shader.setUniform("spotLight.constant", 1.0f);
        //shader.setUniform("spotLight.linear", 0.22f);
        //shader.setUniform("spotLight.constant", 0.20f);

        shader.setUniform("pointLight.position", sceneCamera.getPosition());
        shader.setUniform("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        shader.setUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setUniform("pointLight.constant", 1.0f);
        shader.setUniform("pointLight.linear", 0.22f);
        shader.setUniform("pointLight.constant", 0.20f);

        shader.setUniform("viewPos", sceneCamera.getPosition());

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

        shader.setUniform("model", model);
        shader.setUniform("view", sceneCamera.getViewMatrix());
        shader.setUniform("projection", sceneCamera.getProjectionMatrix());

        ourModel.Draw(shader);

        frame.Bind(0);
        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        frame.Draw(frameShader);

        lastTime = currentTime;
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}