#pragma once
#include <clang/AST/Decl.h>
#include "../Parser.h"

using namespace clang;
using namespace std;

class PropertyParser : public Parser
{
public:
    bool Parse(CXCursor Cursor) override;
    bool CanParse(CXCursor Cursor) const override;

private:
    const FieldDecl* Field = nullptr;
};
