#ifndef VISITOR_H
#define VISITOR_H
#include "AST.h"

typedef struct VISITOR_STRUCT {
  AST_T** varDefs;
  size_t varDefsSize;
} visitor_T;

visitor_T* initVisitor();

AST_T* visit(visitor_T* visitor, AST_T* node);

AST_T* visitVarDef(visitor_T* visitor, AST_T* node);

AST_T* visitVar(visitor_T* visitor, AST_T* node);

AST_T* visitFuncDef(visitor_T* visitor, AST_T* node);

AST_T* visitFuncCall(visitor_T* visitor, AST_T* node);

AST_T* visitString(visitor_T* visitor, AST_T* node);

AST_T* visitCompound(visitor_T* visitor, AST_T* node);

#endif