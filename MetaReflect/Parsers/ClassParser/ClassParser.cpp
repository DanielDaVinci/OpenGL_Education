#include "ClassParser.h"
#include "metareflect.hxx"
#include <iostream>

#include "../PropertyParser/PropertyParser.h"

bool ClassParser::Parse(CXCursor Cursor)
{
    if (!CanParse(Cursor))
    {
        return false;
    }
    
    cout << "------- START PARSE CLASS -------" << endl;

    const CXString displayName = clang_getCursorDisplayName(Cursor);
    cout << "Class name: " << clang_getCString(displayName) << endl;
    clang_disposeString(displayName);

    clang_visitChildren(Cursor, VisitChildRecursive, this);

    cout << "------- END PARSE CLASS -------" << endl;
    return true;
}

bool ClassParser::CanParse(CXCursor Cursor) const
{
    return clang_getCursorKind(Cursor) == CXCursor_ClassDecl && GetAttributeName(Cursor) == ATTRIBUTE_CLASS_NAME;
}

CXChildVisitResult ClassParser::VisitChildRecursive(CXCursor Cursor, CXCursor Parent, CXClientData ClientData)
{
    ClassParser* Class = static_cast<ClassParser*>(ClientData);
    if (!Class)
    {
        return CXChildVisit_Continue;
    }
    
    const CXCursorKind CursorKind = clang_getCursorKind(Cursor);
    if (CursorKind == CXCursor_FieldDecl)
    {
        const auto Parser = make_shared<PropertyParser>();
        if (Parser->CanParse(Cursor))
        {
            Parser->Parse(Cursor);
            Class->Properties.push_back(Parser);
        }
    }

    
    return CXChildVisit_Continue;
}
