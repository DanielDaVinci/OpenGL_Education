#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>

#include "OpenGL_Modules/Shader.h"
#include "OpenGL_Modules/Texture.h"
#include "Drawing.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
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

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;

    glewInit();

    int winWidth, winHeight;
    glfwGetFramebufferSize(window, &winWidth, &winHeight);
    glViewport(0, 0, winWidth, winHeight);

    glEnable(GL_DEPTH_TEST);


    Shader shader("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");


    vector<GLfloat> starVertices = getStarVertices(5, 2.0f, 0.775f);
    vector<GLfloat> cubeVertices = getCubeVertices();


    GLuint starVBO, starVAO;

    glGenVertexArrays(1, &starVAO);
    glGenBuffers(1, &starVBO);
    glBindVertexArray(starVAO);

    glBindBuffer(GL_ARRAY_BUFFER, starVBO);
    glBufferData(GL_ARRAY_BUFFER, starVertices.size() * sizeof(GLfloat), &starVertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    GLuint cubeVBO, cubeVAO;

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(GLfloat), &cubeVertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    Texture texture1(GL_TEXTURE_2D, "Data/Textures/BUMPS.BMP", ColorFormat::RGB);
    texture1.Bind();

    texture1.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture1.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    texture1.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture1.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

    texture1.UnBind();


    Texture texture2(GL_TEXTURE_2D, "Data/Textures/CUBE.BMP", ColorFormat::RGB);
    texture2.Bind();

    texture2.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture2.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    texture2.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    texture2.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    texture2.setParameter(GL_TEXTURE_BORDER_COLOR, borderColor);

    texture2.UnBind();


    GLfloat currentTime = glfwGetTime();
    GLfloat lastTime = currentTime;
    GLfloat deltaTime = 0.0f;

    GLfloat rotateSpeed = 90.0f;


    glm::mat4 view(1.0f);

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(60.0f), (GLfloat)winWidth / winHeight, 0.1f, 100.0f);


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        currentTime = (GLfloat)glfwGetTime();
        deltaTime = currentTime - lastTime;


        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLuint modelLoc = glGetUniformLocation(shader.getProgram(), "model");

        GLuint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        shader.Use();

        // Star
        texture1.Bind();

        glm::mat4 starModel(1.0f);
        starModel = glm::translate(starModel, glm::vec3(-2.5f, 0.0f, -7.5f));
        starModel = glm::rotate(starModel, glm::radians(currentTime * rotateSpeed), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(starModel));

        glBindVertexArray(starVAO);
        glDrawArrays(GL_TRIANGLES, 0, starVertices.size());
        glBindVertexArray(0);


        // Cube
        texture2.Bind();

        glm::mat4 cubeModel(1.0f);
        cubeModel = glm::translate(cubeModel, glm::vec3(2.5f, 0.0f, -7.5f));
        cubeModel = glm::scale(cubeModel, glm::vec3(2.0f, 2.0f, 2.0f));
        cubeModel = glm::rotate(cubeModel, glm::radians(-1.0f * currentTime * rotateSpeed), glm::vec3(1.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, cubeVertices.size());
        glBindVertexArray(0);


        lastTime = currentTime;
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &starVAO);
    glDeleteBuffers(1, &starVBO);

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    glfwTerminate();
    return 0;
}