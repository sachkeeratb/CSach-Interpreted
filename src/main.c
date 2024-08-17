#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

void printHelp();

// Print a help message
void printHelp() {
  printf(
    "Local usage: ./csach.out <filePath>\nSystem-wide usage: csach <filePath>\n"
    );
  exit(1);
}

int main(int argc, char* argv[]) {
  // Check if the user has provided a file
  if (argc != 2) 
    printHelp();

  // Initialize the lexer
  lexer_T* lexer = initLexer(
    getFileContents(argv[1])
  );

  // Initialize the parser
	parser_T* parser = initParser(lexer);
  AST_T* root = parseStatements(parser, parser->scope);

  // Visit the AST
  visit(root);

  return 0;
}