#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT {
  AST_T** funcDefs;
  size_t funcDefsSize;
} scope_T;

scope_T* initScope();

AST_T* scopeAddFuncDef(scope_T* scope, AST_T* funcDef);

AST_T* scopeGetFuncDef(scope_T* scope, const char* funcName);

#endif