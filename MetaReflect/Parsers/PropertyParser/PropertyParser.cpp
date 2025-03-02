#include "PropertyParser.h"

#include <iostream>
#include <clang/AST/DeclTemplate.h>
#include <clang/Sema/CodeCompleteConsumer.h>

#include "metareflect.hxx"

bool PropertyParser::Parse(CXCursor Cursor)
{
    if (!CanParse(Cursor))
    {
        return false;
    }

    Field = GetCursorDecl<FieldDecl>(Cursor);
    if (!Field)
    {
        return false;
    }

    const CXString displayName = clang_getCursorDisplayName(Cursor);
    cout << "Property name: " << clang_getCString(displayName) << endl;
    clang_disposeString(displayName);

    return true;
}

bool PropertyParser::CanParse(CXCursor Cursor) const
{
    auto AttributeName = GetAttributeName(Cursor);
    return clang_getCursorKind(Cursor) == CXCursor_FieldDecl && AttributeName == ATTRIBUTE_PROPERTY_NAME;
}
