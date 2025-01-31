#pragma once

#include "Runtime/Core/Object/RObject.h"

class RWidget : public RObject
{
public:
    RWidget();
    ~RWidget() override;

    virtual void Draw() = 0;
    
};
