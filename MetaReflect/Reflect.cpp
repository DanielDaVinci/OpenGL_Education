#include <clang-c/Index.h>
#include <clang/AST/Decl.h>
#include "clang/AST/DeclBase.h"
#include "clang/AST/Expr.h"
#include <iostream>
#include "Parsers/ClassParser/ClassParser.h"

using namespace clang;

// std::string getLocationString(CXSourceLocation Loc)
// {
//     CXFile File;
//     unsigned Line, Column;
//     clang_getFileLocation(Loc, &File, &Line, &Column, nullptr);
//     CXString FileName = clang_getFileName(File);
//     std::ostringstream ostr;
//     ostr << clang_getCString(FileName) << ":" << Line << ":" << Column;
//     clang_disposeString(FileName);
//     return ostr.str();
// }
//
// void printCursor(CXCursor cursor) {
//     CXType type = clang_getCursorType(cursor);
//     CXString typeName = clang_getTypeSpelling(type);
//     CXString displayName = clang_getCursorDisplayName(cursor);
//     std::cout << clang_getCString(typeName) << " " << clang_getCString(displayName) << "\n";
//     clang_disposeString(displayName);
//     clang_disposeString(typeName);
// }

const Decl *getCursorDecl(CXCursor Cursor) {
    return static_cast<const Decl *>(Cursor.data[0]);
}

const Stmt *getCursorStmt(CXCursor Cursor) {
    if (Cursor.kind == CXCursor_ObjCSuperClassRef ||
            Cursor.kind == CXCursor_ObjCProtocolRef ||
            Cursor.kind == CXCursor_ObjCClassRef)
        return nullptr;
    return static_cast<const Stmt *>(Cursor.data[1]);
}

const Expr *getCursorExpr(CXCursor Cursor) {
    return dyn_cast_or_null<Expr>(getCursorStmt(Cursor));
}

CXChildVisitResult VisitRecursive( CXCursor Cursor, CXCursor /* parent */, CXClientData /*clientData*/ )
{
    CXSourceLocation location = clang_getCursorLocation( Cursor );
    if( clang_Location_isFromMainFile( location ) == 0 )
    {
        return CXChildVisit_Continue;
    }
    
    CXCursorKind cursorKind = clang_getCursorKind( Cursor );
    if (cursorKind == CXCursor_ClassDecl)
    {
        ClassParser Parser;
        Parser.Parse(Cursor);
    }
    
    clang_visitChildren( Cursor, VisitRecursive, nullptr );
    return CXChildVisit_Continue;
}

int main (int argc, char** argv)
{
    CXIndex Index = clang_createIndex (
        false, // excludeDeclarationFromPCH
        true  // displayDiagnostics
        );
    
    CXTranslationUnit Unit = clang_parseTranslationUnit (
        Index, // CIdx
        0, // source_filename
        argv, // command_line_args
        argc, // num_command_line_args
        0, // unsave_files
        0, // num_unsaved_files
        CXTranslationUnit_None // options
        );
    
    if (!Unit)
    {
        std::cout << "Translation unit was not created\n";
        return -1;
    }
    
    CXCursor RootCursor = clang_getTranslationUnitCursor(Unit);
    clang_visitChildren(RootCursor, VisitRecursive, nullptr);
    
    clang_disposeTranslationUnit(Unit);
    clang_disposeIndex(Index);

    return 0;
}