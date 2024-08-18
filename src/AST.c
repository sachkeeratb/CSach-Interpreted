#include "include/AST.h"

// Initialize an AST node
AST_T* initAST(int type) {
  AST_T* ast = calloc(1, sizeof(struct AST_STRUCT)); // Allocate memory for the AST node
  ast->type = type; // Set the type of the AST node

  return ast;
}

size_t varTypeToASTType(size_t varType) {
  switch (varType) {
    case INT: return AST_INT;
    case CHAR: return AST_CHAR;
    case BOOL: return AST_BOOL;
    case STRING: return AST_STRING;
    default: return AST_NOOP;
  }
}