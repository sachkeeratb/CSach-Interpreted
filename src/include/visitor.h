#ifndef VISITOR_H
#define VISITOR_H
#include "AST.h"

/**
 * @brief A visitor is a design pattern that allows you to separate an algorithm from the objects it operates on.
 *        It enables you to add new operations to existing object structures without modifying those structures.
 *        The visitor pattern achieves this by defining a separate visitor class that contains the algorithm
 *        for each operation you want to perform on the objects.
 */

AST_T* builtinFuncPrint(AST_T** args, int argsSize);

AST_T* builtinFuncPrintln(AST_T** args, int argsSize);

AST_T* builtinFuncClear(int argsSize);

AST_T* builtinFuncExit(AST_T** args, int argsSize);

AST_T* visit(AST_T* node);

AST_T* visitVarDef(AST_T* node);

AST_T* visitVar(AST_T* node);

AST_T* visitFuncDef(AST_T* node);

AST_T* visitFuncCall(AST_T* node);

AST_T* visitCompound(AST_T* node);

#endif