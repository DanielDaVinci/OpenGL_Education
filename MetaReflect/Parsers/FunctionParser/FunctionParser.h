#pragma once
#include "../Parser.h"

class FunctionParser : public Parser
{
public:
    bool Parse(CXCursor Cursor) override;
    bool CanParse(CXCursor Cursor) const override;

private:
    const FunctionDecl* Function = nullptr;
};
