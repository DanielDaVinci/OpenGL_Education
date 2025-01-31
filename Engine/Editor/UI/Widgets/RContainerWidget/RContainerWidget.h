#pragma once
#include "Editor/UI/Widgets/Widget/RWidget.h"

#include <vector>
#include <memory>

class RContainerWidget : public RWidget
{
public:
    RContainerWidget();
    ~RContainerWidget();

    void Draw() override;

protected:
    virtual void DrawChild();

private:
    std::vector<std::shared_ptr<RWidget>> ChildrenWidgets;
    
};
