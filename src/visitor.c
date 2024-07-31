#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/visitor.h"
#include "include/scope.h"

static AST_T* builtinFuncPrint(visitor_T* visitor, AST_T** args, int argsSize) {
  for (int i = 0; i < argsSize; i++) {
    AST_T* visited = visit(visitor, args[i]);
    switch (visited->type) {
      case AST_STRING: printf("%s\n", visited->stringVal); break;
    
      default: printf("%p\n", visited); break;
    }
  }

  return initAST(AST_NOOP);
}

static AST_T* builtinFuncClear(visitor_T* visitor, AST_T** args, int argSize) {
  for (int i = 0; i < argSize; i++) {
    AST_T* visited = visit(visitor, args[i]);
    
    switch (visited->type) {
      case AST_NOOP: system("clear"); break;
      default: printf("%p\n", visited); break;
    }
  }

  return initAST(AST_NOOP);
}

// TODO: exit function

visitor_T* initVisitor() {
  visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));

  return visitor;
}

AST_T* visit(visitor_T* visitor, AST_T* node) {
  switch (node->type) {
    case AST_VARIABLE_DEFINITION: return visitVarDef(visitor, node); break;
    case AST_VARIABLE: return visitVar(visitor, node); break;
    case AST_FUNCTION_DEFINITION: return visitFuncDef(visitor, node); break;
    case AST_FUNCTION_CALL: return visitFuncCall(visitor, node); break;
    case AST_STRING: return visitString(visitor, node); break;
    case AST_COMPOUND: return visitCompound(visitor, node); break;
    case AST_NOOP: return node; break;
  }

  printf("Uncaught statement of `%d`\n", node->type);
  exit(1);

  return initAST(AST_NOOP);
}

AST_T* visitVarDef(visitor_T* visitor, AST_T* node) {
  scopeAddVarDef(node->scope, node);

  return node;
}

AST_T* visitVar(visitor_T* visitor, AST_T* node) {
  AST_T* varDef = scopeGetVarDef(node->scope, node->varName);

  if (varDef != (void*) 0)
    return visit(visitor, varDef->varDefVal);

  printf("Undefined variable `%s`\n", node->varName);
  exit(1);
}

AST_T* visitFuncDef(visitor_T* visitor, AST_T* node) {
  scopeAddFuncDef(node->scope, node);

  return node;
}

AST_T* visitFuncCall(visitor_T* visitor, AST_T* node) {
  // Built-in functions
  if(strcmp(node->funcCallName, "print") == 0)
    return builtinFuncPrint(visitor, node->funcCallArgs, node->funcCallArgsSize);

  if (strcmp(node->funcCallName, "clear") == 0)
    return builtinFuncClear(visitor, node->funcCallArgs, node->funcCallArgsSize);
  
  // Custom functions
  AST_T* funcDef = scopeGetFuncDef(node->scope, node->funcCallName);

  // Not found
  if (funcDef == (void*) 0) {
    printf("Undefined function call of `%s`\n", node->funcCallName);
    exit(1);
  }

  // Invalid amount of arguments called
  if (node->funcCallArgsSize != funcDef->funcDefArgsSize) {
    printf("Invalid amounmt of arguments passed into function `%s`\n", node->funcCallName);
    exit(1);
  }

  // Go through the arguments
  for (int i = 0; i < funcDef->funcDefArgsSize; i++) {
    // Get the variable and its value from the defined arguments
    AST_T* var = (AST_T*) funcDef->funcDefArgs[i];
    AST_T* val = (AST_T*) node->funcCallArgs[i];

    // Create a new variable definition with the value of the argument passed in the call
    AST_T* varDef = initAST(AST_VARIABLE_DEFINITION);

    // Give the variable its value
    varDef->varDefVal = val;

    // Copy the name of the defined argument into the new variable definition
    varDef->varDefVarName = calloc(strlen(var->varName) + 1, sizeof(char));
    strcpy(varDef->varDefVarName, var->varName);

    // Add it to the function's scope
    scopeAddVarDef(funcDef->funcDefBody->scope, varDef);
  }
    
  // Found
  return visit(visitor, funcDef->funcDefBody);
}

AST_T* visitString(visitor_T* visitor, AST_T* node) {
  return node;
}

AST_T* visitCompound(visitor_T* visitor, AST_T* node) {
  for (int i = 0; i < node->compoundSize; i++) 
    visit(visitor, node->compoundVal[i]);

  return initAST(AST_NOOP);
}