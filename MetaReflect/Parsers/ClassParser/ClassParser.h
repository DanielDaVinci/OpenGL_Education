#pragma once
#include <clang-c/Index.h>
#include <string>
#include <vector>
#include <clang/AST/Decl.h>

#include "../Parser.h"

class FunctionParser;
class PropertyParser;
using namespace std;
using namespace clang;

class ClassParser : public Parser
{
public:
    bool Parse(CXCursor Cursor) override;
    bool CanParse(CXCursor Cursor) const override;
    
    static CXChildVisitResult VisitChildRecursive(CXCursor Cursor, CXCursor Parent, CXClientData ClientData);

private:
    vector<std::shared_ptr<PropertyParser>> Properties;
    vector<std::shared_ptr<FunctionParser>> Functions;
    
};
