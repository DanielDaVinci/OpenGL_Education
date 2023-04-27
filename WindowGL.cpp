#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>

using namespace std;

ostream& operator << (ostream& out, glm::vec3& vector)
{
    out << vector.x << " " << vector.y << " " << vector.z;
    return out;
}

#include "OpenGL_Modules/Shader.h"
#include "OpenGL_Modules/Texture.h"
#include "OpenGL_Modules/Camera.h"

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

    Shader shader("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");
    Shader lightShader("Data/Shaders/shader.vs", "Data/Shaders/lamp_lightShader.frag");

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Texture texture(GL_TEXTURE_2D, "Data/Textures/Container.png", ColorFormat::RGB);
    texture.Bind();

    texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    GLfloat borderColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    texture.setParameter(GL_TEXTURE_BORDER_COLOR, borderColor);

    texture.UnBind();

    Texture specTexture(GL_TEXTURE_2D, "Data/Textures/Container_specular.png", ColorFormat::RGBA);
    specTexture.Bind();

    specTexture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    specTexture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    specTexture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    specTexture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    specTexture.setParameter(GL_TEXTURE_BORDER_COLOR, borderColor);

    specTexture.UnBind();

    GLfloat currentTime = glfwGetTime();
    GLfloat lastTime = currentTime;
    GLfloat deltaTime = 0.0f;

    GLfloat rotateSpeed = 90.0f;

    glm::mat4 lightModel(1.0f);

    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    shader.Use();
    shader.setUniform("material.diffuse", 0);
    shader.setUniform("material.specular", 1);
    shader.setUniform("material.shininess", 32.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        currentTime = (GLfloat)glfwGetTime();
        deltaTime = currentTime - lastTime;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Main Cube
        shader.Use();

        shader.setUniform("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader.setUniform("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setUniform("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
        shader.setUniform("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

        for (int i = 0; i < 4; i++)
        {
            shader.setUniform(("pointLights[" + to_string(i) + "].position").c_str(), pointLightPositions[i]);
            shader.setUniform(("pointLights[" + to_string(i) + "].ambient").c_str(), glm::vec3(0.05f, 0.05f, 0.05f));
            shader.setUniform(("pointLights[" + to_string(i) + "].diffuse").c_str(), glm::vec3(0.5f, 0.5f, 0.5f));
            shader.setUniform(("pointLights[" + to_string(i) + "].specular").c_str(), glm::vec3(1.0f, 1.0f, 1.0f));
            shader.setUniform(("pointLights[" + to_string(i) + "].constant").c_str(), 1.0f);
            shader.setUniform(("pointLights[" + to_string(i) + "].linear").c_str(), 0.22f);
            shader.setUniform(("pointLights[" + to_string(i) + "].quadratic").c_str(), 0.20f);
        }

        shader.setUniform("spotLight.position", sceneCamera.getPosition());
        shader.setUniform("spotLight.direction", sceneCamera.getFrontDirection());
        shader.setUniform("spotLight.innerAngle", glm::cos(glm::radians(12.5f)));
        shader.setUniform("spotLight.outerAngle", glm::cos(glm::radians(15.5f)));
        shader.setUniform("spotLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setUniform("spotLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setUniform("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setUniform("spotLight.constant", 1.0f);
        shader.setUniform("spotLight.linear", 0.09f);
        shader.setUniform("spotLight.quadratic", 0.032f);

        shader.setUniform("viewPos", sceneCamera.getPosition());
        shader.setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shader.setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

        do_movement(deltaTime);
        view = sceneCamera.getViewMatrix();

        projection = sceneCamera.getProjectionMatrix();

        shader.setUniform("view", view);
        shader.setUniform("projection", projection);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        glActiveTexture(GL_TEXTURE1);
        specTexture.Bind();

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i] - glm::vec3(0.0f, 0.0f, 2.0f));
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setUniform("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        texture.UnBind();
        specTexture.UnBind();

        // Lamp
        lightShader.Use();

        view = sceneCamera.getViewMatrix();

        projection = sceneCamera.getProjectionMatrix();

        lightShader.setUniform("view", view);
        lightShader.setUniform("projection", projection);

        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            lightModel = glm::mat4(1.0f);
            lightModel = glm::translate(lightModel, pointLightPositions[i]);
            lightModel = glm::scale(lightModel, glm::vec3(0.2f));
            lightShader.setUniform("model", lightModel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        lastTime = currentTime;
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}