#pragma once

#include "Engine/REngine.h"
#include "Engine/shell/FApplication.h"
#include "example/MainWindow.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    Engine = new REngine();
    
    Engine->PreInit();
    Engine->Init();
    Engine->PostInit();

    while (Engine->IsEngineActive())
    {
        Engine->PreTick();
        Engine->Tick();
        Engine->PostTick();
    }
    
    // FApplication application;
    //
    // application.addWindow(new MainWindow());

    return 0;
}