#ifndef VISITOR_H
#define VISITOR_H
#include "AST.h"

AST_T* visit(AST_T* node);

AST_T* visitVarDef(AST_T* node);

AST_T* visitVar(AST_T* node);

AST_T* visitFuncCakk(AST_T* node);

AST_T* visitString(AST_T* node);

AST_T* visitCompound(AST_T* node);

#endif