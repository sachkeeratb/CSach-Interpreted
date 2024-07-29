#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

void printHelp() {
  printf(
    "Local usage: ./csach.out <filePath>\nSystem-wide usage: csach <filePath>\n"
    );
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc < 2) 
    printHelp();

  lexer_T* lexer = initLexer(
    getFileContents(argv[1])
  );

	parser_T* parser = initParser(lexer);
  AST_T* root = parserParse(parser);
  visitor_T* visitor = initVisitor();

  visit(visitor, root);

  return 0;
}