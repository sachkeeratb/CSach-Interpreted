#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT {
  enum {
    AST_VARIABLE_DEFINITION,
    AST_VARIABLE,
    AST_FUNCTION_CALL,
    AST_STRING,
    AST_COMPOUND
  } type;

  // For variable definition
  char* varDefVarName;
  struct AST_STRUCT* varDefVal;

  // For variable reference
  char* varName;
  struct AST_STRUCT* varVal;

  // For function call
  char* funcCallName;
  struct AST_STRUCT** funcCallArgs;
  size_t funcCallArgsSize;
  
  // For strings
  char* stringVal;

  // For compound statements
  struct AST_STRUCT** compoundVal;
  size_t compoundSize;
} AST_T;

AST_T* initAST(int type);

#endif