#include "include/AST.h"

AST_T* initAST(int type) {
  AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
  ast->type = type;

  // For variable definition
  ast->varDefVarName = (void*) 0;
  ast->varDefVal = (void*) 0;

  // For variable reference
  ast->varName = (void*) 0;
  ast->varVal = (void*) 0;

  // For function call
  ast->funcCallName = (void*) 0;
  ast->funcCallArgs = (void*) 0;
  ast->funcCallArgsSize = 0;
  
  // For strings
  ast->stringVal = (void*) 0;

  // For compound statements
  ast->compoundVal = (void*) 0;
  ast->compoundSize = 0;

  return ast;
}