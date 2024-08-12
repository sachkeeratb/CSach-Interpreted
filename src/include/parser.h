#ifndef PARSER_H
#define PARSER_H
#include "AST.h"
#include "lexer.h"
#include "scope.h"
#include "list.h"

/**
 * @brief A parser is a software component that analyzes a sequence of characters or tokens to determine its structure and meaning.
 *        It is commonly used in programming languages, markup languages, and other applications that require the interpretation of structured data.
 *        The parser takes input in the form of a stream of characters or tokens and produces an output in the form of a parse tree or an abstract syntax tree.
 *        This parse tree represents the hierarchical structure of the input and can be used for further processing or interpretation.
 *        The parser plays a crucial role in the compilation process of programming languages, where it is responsible for transforming the source code into executable *        instructions.
 *        Additionally, parsers are also used in data processing tasks such as data validation, data extraction, and query parsing.
 */

typedef struct PARSER_STRUCT {
  lexer_T* lexer;
  token_T* currentToken;
  token_T* prevToken;
  scope_T* scope;
} parser_T;

parser_T* initParser(lexer_T* lexer);

void eat(parser_T* parser, int tokenType);

AST_T* parseStatement(parser_T* parser, scope_T* scope);

AST_T* parseStatements(parser_T* parser, scope_T* scope);

AST_T* parseFuncCall(parser_T* parser, scope_T* scope);

AST_T* parseVarDef(parser_T* parser, scope_T* scope);

AST_T* parseFuncDef(parser_T* parser, scope_T* scope);

AST_T* parseVar(parser_T* parser, scope_T* scope);

AST_T* parseString(parser_T* parser, scope_T* scope);

AST_T* parseIntExpr(parser_T* parser, scope_T* scope);

AST_T* parseID(parser_T* parser, scope_T* scope);

#endif