#include <stdio.h>
#include <string.h>
#include "include/visitor.h"

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

visitor_T* initVisitor() {
  visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
  visitor->varDefs = (void*) 0;
  visitor->varDefsSize = 0;

  return visitor;
}

AST_T* visit(visitor_T* visitor, AST_T* node) {
  switch (node->type) {
    case AST_VARIABLE_DEFINITION: return visitVarDef(visitor, node); break;
    case AST_VARIABLE: return visitVar(visitor, node); break;
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
  if (visitor->varDefs == (void*) 0) {
    visitor->varDefs = calloc(1, sizeof(struct AST_STRUCT*));
    visitor->varDefs[0] = node;
    visitor->varDefsSize += 1;
  }
  else {
    visitor->varDefsSize += 1;
    visitor->varDefs = realloc(
      visitor->varDefs, 
      visitor->varDefsSize * sizeof(struct AST_STRUCT*)
    );

    visitor->varDefs[visitor->varDefsSize - 1] = node;
  }

  return node;
}

AST_T* visitVar(visitor_T* visitor, AST_T* node) {
  for (int i = 0; i < visitor->varDefsSize; i++) {
    AST_T* varDef = visitor->varDefs[i];
    if (strcmp(varDef->varDefVarName, node->varName) == 0)
      return visit(visitor, varDef->varDefVal);
  }

  printf("Undefined variable `%s`\n", node->varName);
  return node;
}

AST_T* visitFuncCall(visitor_T* visitor, AST_T* node) {
  if(strcmp(node->funcCallName, "print") == 0)
    return builtinFuncPrint(visitor, node->funcCallArgs, node->funcCallArgsSize);
  
  printf("Undefined function call of `%s`\n", node->funcCallName);
  exit(1);
}

AST_T* visitString(visitor_T* visitor, AST_T* node) {
  return node;
}

AST_T* visitCompound(visitor_T* visitor, AST_T* node) {
  for (int i = 0; i < node->compoundSize; i++) 
    visit(visitor, node->compoundVal[i]);

  return initAST(AST_NOOP);
}