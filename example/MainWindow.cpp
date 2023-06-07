#include "MainWindow.h"

MainWindow::MainWindow(): Window("Window", 1200, 800)
{
	setWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	setWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	setWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	setWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewExperimental = GL_TRUE;
    glewInit();

    keys = vector<GLboolean>(1024, 0);
}

MainWindow::~MainWindow()
{
    delete sceneCamera;
    delete frame;
    delete shader;
    delete strokeShader;
    delete frameShader;
    delete mainModel;
}

void MainWindow::movement()
{
    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
        sceneCamera->setPosition(sceneCamera->getPosition() + sceneCamera->getFrontDirection() * cameraSpeed);
    if (keys[GLFW_KEY_S])
        sceneCamera->setPosition(sceneCamera->getPosition() - sceneCamera->getFrontDirection() * cameraSpeed);
    if (keys[GLFW_KEY_A])
        sceneCamera->setPosition(sceneCamera->getPosition() - sceneCamera->getRightDirection() * cameraSpeed);
    if (keys[GLFW_KEY_D])
        sceneCamera->setPosition(sceneCamera->getPosition() + sceneCamera->getRightDirection() * cameraSpeed);
}

void MainWindow::onCreate()
{
	auto sizes = getFrameBufferSize();
    
    sceneCamera = new Camera(800, 600, 45.0f, { 0.0f, 0.0f, 0.0f }, { 0.0f, -90.0f, 0.0f });

	frame = new Frame(sizes.first, sizes.second);

	shader = new Shader("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");
	strokeShader = new Shader("Data/Shaders/strokeShader.vs", "Data/Shaders/strokeShader.frag");
	frameShader = new Shader("Data/Shaders/frameShader.vs", "Data/Shaders/frameShader.frag");

	mainModel = new Model("resources/objects/backpack/backpack.obj");
}

void MainWindow::onRender()
{
    movement();

    frame->Bind();

    glEnable(GL_DEPTH_TEST);

    //setName(to_string(int(1.0f / deltaTime)));

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();
    shader->setUniform("pointLight.position", sceneCamera->getPosition());
    shader->setUniform("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    shader->setUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setUniform("pointLight.constant", 1.0f);
    shader->setUniform("pointLight.linear", 0.22f);
    shader->setUniform("pointLight.constant", 0.20f);
    shader->setUniform("viewPos", sceneCamera->getPosition());

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

    shader->setUniform("model", model);
    shader->setUniform("view", sceneCamera->getViewMatrix());
    shader->setUniform("projection", sceneCamera->getProjectionMatrix());

    mainModel->Draw(*shader);

    frame->Bind(0);
}

void MainWindow::onGUI()
{
    ImGui::Begin("My Scene");

    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;

    frame->Resize(window_width, window_height);
    glViewport(0, 0, window_width, window_height);
    sceneCamera->setScreenWidth(window_width);
    sceneCamera->setScreenHeight(window_height);

    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage(
        (void*)frame->getTextureID(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    ImVec2 vec2 = ImGui::GetCursorScreenPos();
    setName(to_string(vec2.x) + " " + to_string(vec2.y));

    ImGui::End();
}

void MainWindow::onMouseDrag(GLdouble x, GLdouble y)
{
//    static GLdouble lastX = 400, lastY = 300;
//
//    GLfloat xoffset = x - lastX;
//    GLfloat yoffset = lastY - y;
//    lastX = x;
//    lastY = y;
//
//    GLfloat sensitivity = 0.05f;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    glm::vec3 angles = sceneCamera->getAngle();
//    angles.x += yoffset;
//    angles.y += xoffset;
//
//    angles.x = glm::clamp(angles.x, -89.0f, 89.0f);
//
//    sceneCamera->setAngle(angles);
}

void MainWindow::onMouseScroll(GLdouble xOffset, GLdouble yOffset)
{
    GLfloat zoomSpeed = 1.0f;
    GLfloat FOV = sceneCamera->getFOV() - yOffset * zoomSpeed;
    sceneCamera->setFOV(glm::max(glm::min(FOV, 60.0f), 1.0f));
}

void MainWindow::onKeyDown(GLint key, GLint scanCode, GLint mode)
{
    if (key == GLFW_KEY_ESCAPE)
        Close();

    keys[key] = GL_TRUE;
}

void MainWindow::onKeyUp(GLint key, GLint scanCode, GLint mode)
{
    keys[key] = GL_FALSE;
}
