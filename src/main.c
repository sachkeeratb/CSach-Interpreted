#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"

int main(int argc, char* argv[]) {
  lexer_T* lexer = initLexer(
    "let name = \"Sachkeerat Singh Brar\";\n"
    "let othername = \"other name\";\n"
    "print(name, othername);\n"
  );

	parser_T* parser = initParser(lexer);
  AST_T* root = parserParse(parser);
  visitor_T* visitor = initVisitor();

  visit(visitor, root);

  return 0;
}