#pragma once

#include "../engine/shell/Window.h"
#include "../engine/screen/Frame.h"
#include "../engine/graphic/Model.h"
#include "../engine/objects/Camera.h"

class MainWindow: public Window
{
private:
	Camera* sceneCamera = nullptr;

	Frame* frame = nullptr;

	Shader* shader = nullptr;
	Shader* strokeShader = nullptr;
	Shader* frameShader = nullptr;

	Model* mainModel = nullptr;

	vector<GLboolean>* keys = nullptr;

public:
	MainWindow();
	~MainWindow();

protected:
	void movement();

	void onCreate();
	void onRender();

	// Events
		// Mouse
	void onMouseDrag(GLdouble x, GLdouble y);
	void onMouseScroll(GLdouble xOffset, GLdouble yOffset);
	// KeyBoard
	void onKeyDown(GLint key, GLint scanCode, GLint mode);
	void onKeyUp(GLint key, GLint scanCode, GLint mode);
};

