#ifndef AST_H
#define AST_H
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief An AST, or Abstract Syntax Tree, is a data structure commonly used in programming language compilers and interpreters.
 *        It represents the structure of the source code in a hierarchical manner, capturing the structure and relationships between different elements of the code.
 */

typedef struct AST_STRUCT {
  enum {
    AST_VARIABLE_DEFINITION, // let var = val;
    AST_VARIABLE, // var
    AST_FUNCTION_DEFINITION, // func name(args) { body };
    AST_FUNCTION_CALL, // name(args);
    STRING, // "val"
    VOID, // void
    BOOL, // true/false
    ANY, // Any type
    CHAR, // 'a'
    INT, // 1234
    FLOAT, // 12.34
    AST_COMPOUND, // { statements }
    AST_BINOP, // Binary Operator
    AST_STATEMENT_RETURN, // ret val;
    AST_NOOP // No operation
  } type;

  struct SCOPE_STRUCT* scope;

  // For variable definitions
  char* varDefVarName;
  struct AST_STRUCT* varDefVal;

  // For variable references
  char* varName;
  struct AST_STRUCT* varVal;
  bool isInitialized;

  // For function definitions
  char* funcDefName;
  struct AST_STRUCT** funcDefArgs;
  size_t funcDefArgsSize;
  struct AST_STRUCT* funcDefBody;

  // For function calls
  char* funcCallName;
  struct AST_STRUCT** funcCallArgs;
  size_t funcCallArgsSize;
  
  // For strings
  char* stringVal;

  // For characters
  char charVal;

  // For bools
  bool boolVal;

  // For ints
  long intVal;

  // For compound statements
  struct AST_STRUCT** compoundVal;
  size_t compoundSize;
} AST_T;

AST_T* initAST(int type);

#endif