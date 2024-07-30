#include <string.h>
#include "include/scope.h"

scope_T* initScope() {
  scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));

  return scope;
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