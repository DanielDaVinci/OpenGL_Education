#pragma once

#include "engine/shell/Application.h"
#include "example/MainWindow.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    Application application;

    MainWindow mainWindow = MainWindow();

    application.addWindow(&mainWindow);

    return 0;
}