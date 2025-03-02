#include "Parser.h"

bool Parser::Parse(CXCursor Cursor)
{
    return false;
}

bool Parser::CanParse(CXCursor Cursor) const
{
    return false;
}

struct AttributeNameData
{
    std::string AttributeName;
};

string Parser::GetAttributeName(const CXCursor& Cursor)
{
    AttributeNameData Data;
    clang_visitChildren(Cursor, [](CXCursor Cursor, CXCursor, CXClientData ClientData)
    {
        AttributeNameData* Data = static_cast<AttributeNameData*>(ClientData);
        if (clang_isAttribute(clang_getCursorKind(Cursor)))
        {
            const CXString AttributeSpelling = clang_getCursorSpelling(Cursor);
            const char* AttributeName = clang_getCString(AttributeSpelling);
            Data->AttributeName = AttributeName;
        }

        return CXChildVisit_Continue;
    }, &Data);

    return Data.AttributeName;
}

const Stmt* Parser::GetCursorStmt(const CXCursor& Cursor)
{
    if (Cursor.kind == CXCursor_ObjCSuperClassRef ||
            Cursor.kind == CXCursor_ObjCProtocolRef ||
            Cursor.kind == CXCursor_ObjCClassRef)
        return nullptr;
    return static_cast<const Stmt *>(Cursor.data[1]);
}
