#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"

int main(int argc, char* argv[]) {
  lexer_T* lexer = initLexer(
    "let name = \"Sachkeerat Brar\";\n"
    "print(name);\n"
  );

	parser_T* parser = initParser(lexer);
  AST_T* root = parserParse(parser);
  printf("%d\n", root->type);
  printf("%d\n", root->compoundSize);

  return 0;
}