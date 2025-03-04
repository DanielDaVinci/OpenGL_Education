#include "FunctionParser.h"

#include <iostream>

#include "metareflect.hxx"

bool FunctionParser::Parse(CXCursor Cursor)
{
    if (!CanParse(Cursor))
    {
        return false;
    }

    Function = GetCursorDecl<FunctionDecl>(Cursor);
    if (!Function)
    {
        return false;
    }

    const CXString displayName = clang_getCursorDisplayName(Cursor);
    cout << "Function name: " << clang_getCString(displayName) << endl;
    clang_disposeString(displayName);

    return true;
}

bool FunctionParser::CanParse(CXCursor Cursor) const
{
    const string AttributeName = GetAttributeName(Cursor);
    return clang_getCursorKind(Cursor) == CXCursor_CXXMethod && AttributeName.starts_with(ATTRIBUTE_FUNCTION_NAME);
}
