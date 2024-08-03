#ifndef VISITOR_H
#define VISITOR_H
#include "AST.h"

/**
 * @brief A visitor is a design pattern that allows you to separate an algorithm from the objects it operates on.
 *        It enables you to add new operations to existing object structures without modifying those structures.
 *        The visitor pattern achieves this by defining a separate visitor class that contains the algorithm
 *        for each operation you want to perform on the objects.
 */

typedef struct VISITOR_STRUCT { } visitor_T;

visitor_T* initVisitor();

AST_T* visit(visitor_T* visitor, AST_T* node);

AST_T* visitVarDef(visitor_T* visitor, AST_T* node);

AST_T* visitVar(visitor_T* visitor, AST_T* node);

AST_T* visitFuncDef(visitor_T* visitor, AST_T* node);

AST_T* visitFuncCall(visitor_T* visitor, AST_T* node);

AST_T* visitCompound(visitor_T* visitor, AST_T* node);

#endif