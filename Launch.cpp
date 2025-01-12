#pragma once

#include "Engine/REngine.h"

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

    return 0;
}