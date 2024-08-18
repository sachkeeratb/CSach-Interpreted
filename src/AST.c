#include "include/AST.h"

// Initialize an AST node
AST_T* initAST(int type) {
  AST_T* ast = calloc(1, sizeof(struct AST_STRUCT)); // Allocate memory for the AST node
  ast->type = type; // Set the type of the AST node

  return ast;
}