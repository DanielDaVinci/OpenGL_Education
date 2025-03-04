#include "ClassParser.h"
#include "metareflect.hxx"
#include <iostream>

#include "../FunctionParser/FunctionParser.h"
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
    const string AttributeName = GetAttributeName(Cursor);
    return clang_getCursorKind(Cursor) == CXCursor_ClassDecl && AttributeName.starts_with(ATTRIBUTE_CLASS_NAME);
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
    else if (CursorKind == CXCursor_CXXMethod)
    {
        const auto Parser = make_shared<FunctionParser>();
        if (Parser->CanParse(Cursor))
        {
            Parser->Parse(Cursor);
            Class->Functions.push_back(Parser);
        }
    }

    // const CXString displayName = clang_getCursorDisplayName(Cursor);
    // if (std::string(clang_getCString(displayName)) == "Hash()")
    // {
    //     cout << "Name: " << clang_getCString(displayName) << endl;
    //     cout << clang_getCString(clang_getCursorKindSpelling(CursorKind)) << endl;
    // }
    // clang_disposeString(displayName);

    
    return CXChildVisit_Continue;
}
