#pragma once
#include <clang-c/Index.h>
#include <string>
#include <clang/AST/Decl.h>

using namespace std;
using namespace clang;

class Parser
{
public:
    virtual bool Parse(CXCursor Cursor);
    virtual bool CanParse(CXCursor Cursor) const;
    
protected:
    static string GetAttributeName(const CXCursor& Cursor);
    
    template<typename DeclType>
    static const DeclType* GetCursorDecl(const CXCursor& Cursor)
    {
        return dyn_cast_or_null<const DeclType>(static_cast<const Decl*>(Cursor.data[0]));
    }
    
    static const Stmt* GetCursorStmt(const CXCursor& Cursor);
};
