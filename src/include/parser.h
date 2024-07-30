#ifndef PARSER_H
#define PARSER_H
#include "AST.h"
#include "lexer.h"
#include "scope.h"

typedef struct PARSER_STRUCT {
  lexer_T* lexer;
  token_T* currentToken;
  token_T* prevToken;
  scope_T* scope;
} parser_T;

parser_T* initParser(lexer_T* lexer);

void parserEat(parser_T* parser, int tokenType);

AST_T* parserParse(parser_T* parser, scope_T* scope);

AST_T* parserParseStatement(parser_T* parser, scope_T* scope);

AST_T* parserParseStatements(parser_T* parser, scope_T* scope);

AST_T* parserParseExpression(parser_T* parser, scope_T* scope);

AST_T* parserParseFactor(parser_T* parser, scope_T* scope);

AST_T* parserParseTerm(parser_T* parser, scope_T* scope);

AST_T* parserParseFuncCall(parser_T* parser, scope_T* scope);

AST_T* parserParseVarDef(parser_T* parser, scope_T* scope);

AST_T* parserParseFuncDef(parser_T* parser, scope_T* scope);

AST_T* parserParseVar(parser_T* parser, scope_T* scope);

AST_T* parserParseString(parser_T* parser, scope_T* scope);

AST_T* parserParseID(parser_T* parser, scope_T* scope);

#endif