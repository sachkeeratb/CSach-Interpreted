#include <string.h>
#include "include/scope.h"

scope_T* initScope() {
  scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));

  return scope;
}

AST_T* scopeAddVarDef(scope_T* scope, AST_T* varDef) {
  scope->varDefsSize += 1;

  if (scope->varDefs == (void*) 0) {
    scope->varDefs = calloc(1, sizeof(struct AST_STRUCT*));
    scope->varDefs[0] = varDef;
  }
  else {
    scope->varDefs = realloc(
      scope->varDefs, 
      scope->varDefsSize * sizeof(struct AST_STRUCT*)
    );

    scope->varDefs[scope->varDefsSize - 1] = varDef;
  }

  return varDef;
}

AST_T* scopeGetVarDef(scope_T* scope, const char* varDefName) {
  for (int i = 0; i < scope->varDefsSize; i++) {
    AST_T* varDef = scope->varDefs[i];

    if (strcmp(varDef->varDefVarName, varDefName) == 0)
      return varDef;
  }

  return (void*) 0;
}

AST_T* scopeAddFuncDef(scope_T* scope, AST_T* funcDef) {
  scope->funcDefsSize += 1;

  if (scope->funcDefs == (void*) 0) {
    scope->funcDefs = calloc(1, sizeof(struct AST_STRUCT*));
    scope->funcDefs[0] = funcDef;
  }
  else {
    scope->funcDefs = realloc(
      scope->funcDefs,
      scope->funcDefsSize * sizeof(struct AST_STRUCT*)
    );

    scope->funcDefs[scope->funcDefsSize - 1] = funcDef;
  }

  return funcDef;
}

AST_T* scopeGetFuncDef(scope_T* scope, const char* funcName) {
  for (int i = 0; i < scope->funcDefsSize; i++) {
    AST_T* funcDef = scope->funcDefs[i];

    if (strcmp(funcDef->funcDefName, funcName) == 0)
      return funcDef;
  }

  return (void*) 0;
}