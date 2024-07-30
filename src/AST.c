#include "include/AST.h"

AST_T* initAST(int type) {
  AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
  ast->type = type;

  return ast;
}