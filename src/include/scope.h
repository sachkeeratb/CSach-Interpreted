#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT {  
  AST_T** varDefs;
  size_t varDefsSize;

  AST_T** funcDefs;
  size_t funcDefsSize;
} scope_T;

scope_T* initScope();

AST_T* scopeAddVarDef(scope_T* scope, AST_T* varDef);

AST_T* scopeGetVarDef(scope_T* scope, const char* varDefName);

AST_T* scopeAddFuncDef(scope_T* scope, AST_T* funcDef);

AST_T* scopeGetFuncDef(scope_T* scope, const char* funcName);

#endif