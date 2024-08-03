#include <string.h>
#include "include/scope.h"

scope_T* initScope() {
  scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT)); // Allocate memory for the scope

  return scope;
}

AST_T* scopeAddVarDef(scope_T* scope, AST_T* varDef) {
  // Increase the size of the variable definitions
  scope->varDefsSize += 1;

  // If there are no variable definitions, allocate memory for the first one
  if (scope->varDefs == (void*) 0) {
    scope->varDefs = calloc(1, sizeof(struct AST_STRUCT*));
    scope->varDefs[0] = varDef;
  }

  // Otherwise, reallocate memory for the variable definitions
  else {
    scope->varDefs = realloc(
      scope->varDefs, 
      scope->varDefsSize * sizeof(struct AST_STRUCT*)
    );

    // Append the new variable definition to the end of the list
    scope->varDefs[scope->varDefsSize - 1] = varDef;
  }

  return varDef;
}

AST_T* scopeGetVarDef(scope_T* scope, const char* varDefName) {
  // Go through all the variable definitions in the scope
  for (int i = 0; i < scope->varDefsSize; i++) {
    AST_T* varDef = scope->varDefs[i];

    // If the name matches the name of a variable definition, return it
    if (strcmp(varDef->varDefVarName, varDefName) == 0)
      return varDef;
  }

  // Otherwise, return null
  return (void*) 0;
}

AST_T* scopeAddFuncDef(scope_T* scope, AST_T* funcDef) {
  // Increase the size of the function definitions
  scope->funcDefsSize += 1;

  // If there are no function definitions, allocate memory for the first one
  if (scope->funcDefs == (void*) 0) {
    scope->funcDefs = calloc(1, sizeof(struct AST_STRUCT*));
    scope->funcDefs[0] = funcDef;
  }
  // Otherwise, reallocate memory for the function definitions
  else {
    scope->funcDefs = realloc(
      scope->funcDefs,
      scope->funcDefsSize * sizeof(struct AST_STRUCT*)
    );

    // Append the new function definition to the end of the list
    scope->funcDefs[scope->funcDefsSize - 1] = funcDef;
  }

  // Return the function definition
  return funcDef;
}

AST_T* scopeGetFuncDef(scope_T* scope, const char* funcName) {
  // Go through all the function definitions in the scope
  for (int i = 0; i < scope->funcDefsSize; i++) {
    AST_T* funcDef = scope->funcDefs[i];

    // If the name matches the name of a function definition, return it
    if (strcmp(funcDef->funcDefName, funcName) == 0)
      return funcDef;
  }

  // Otherwise, return null
  return (void*) 0;
}