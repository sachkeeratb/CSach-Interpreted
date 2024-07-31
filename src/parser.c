#include <string.h>
#include <stdio.h>
#include "include/parser.h"
#include "include/scope.h"

parser_T* initParser(lexer_T* lexer) {
  parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
  parser->lexer = lexer;
  parser->currentToken = lexerGetNextToken(lexer);
  parser->prevToken = parser->currentToken;
  parser->scope = initScope();

  return parser;
}

void parserEat(parser_T* parser, int tokenType) {
  if (parser->currentToken->type == tokenType) {
    parser->prevToken = parser->currentToken;
    parser->currentToken = lexerGetNextToken(parser->lexer);
  }
  else {
    printf(
      "Unexpected token `%s` with type %d\n", parser->currentToken->val, 
      parser->currentToken->type
    );
    exit(1);
  }
}

AST_T* parserParse(parser_T* parser, scope_T* scope) { 
  return parserParseStatements(parser, scope);
}

AST_T* parserParseStatement(parser_T* parser, scope_T* scope) {
  switch (parser->currentToken->type) {
    case TOKEN_ID: return parserParseID(parser, scope); break;
  }

  return initAST(AST_NOOP);
}

AST_T* parserParseStatements(parser_T* parser, scope_T* scope) {
  AST_T* compound = initAST(AST_COMPOUND);
  compound->compoundVal = calloc(1, sizeof(struct AST_STRUCT));
  
  AST_T* statement = parserParseStatement(parser, scope);
  statement->scope = scope;

  compound->compoundVal[0] = statement;
  compound->compoundSize += 1;
  compound->scope = scope;  

  while(parser->currentToken->type == TOKEN_SEMI) {
    parserEat(parser, TOKEN_SEMI);

    AST_T* statement = parserParseStatement(parser, scope);

    if (statement) {
      compound->compoundSize += 1;    
      compound->compoundVal = realloc(
        compound->compoundVal, 
        (compound->compoundSize + 1) * sizeof(struct AST_STRUCT)
      );

      compound->compoundVal[compound->compoundSize - 1] = statement;
    }
  }

  return compound;
}

AST_T* parserParseExpression(parser_T* parser, scope_T* scope) {
  switch (parser->currentToken->type) {
    case TOKEN_STRING: return parserParseString(parser, scope); break;
    case TOKEN_ID: return parserParseID(parser, scope); break;
  }

  return initAST(AST_NOOP);
}

AST_T* parserParseFactor(parser_T* parser, scope_T* scope) {

}

AST_T* parserParseTerm(parser_T* parser, scope_T* scope) {

}

AST_T* parserParseFuncCall(parser_T* parser, scope_T* scope) {
  AST_T* funcCall = initAST(AST_FUNCTION_CALL);
  funcCall->funcCallName = parser->prevToken->val;

  parserEat(parser, TOKEN_LPAREN);

  if (parser->currentToken->type != TOKEN_RPAREN) {
    funcCall->funcCallArgs = calloc(1, sizeof(struct AST_STRUCT));
    
    AST_T* expression = parserParseExpression(parser, scope);
    funcCall->funcCallArgs[0] = expression;
    funcCall->funcCallArgsSize += 1;

    while(parser->currentToken->type == TOKEN_COMMA) {
      parserEat(parser, TOKEN_COMMA);

      AST_T* expression = parserParseExpression(parser, scope);
      funcCall->funcCallArgsSize += 1;
      
      funcCall->funcCallArgs = realloc(
        funcCall->funcCallArgs, 
        (funcCall->funcCallArgsSize + 1) * sizeof(struct AST_STRUCT)
      );

      funcCall->funcCallArgs[funcCall->funcCallArgsSize - 1] = expression;
    }
  }

  parserEat(parser, TOKEN_RPAREN);

  funcCall->scope = scope;

  return funcCall;
}

AST_T* parserParseVarDef(parser_T* parser, scope_T* scope) {
  parserEat(parser, TOKEN_ID); // let
  char* varDefVarName = parser->currentToken->val;
  parserEat(parser, TOKEN_ID); // variable name
  parserEat(parser, TOKEN_EQUALS); // =
  AST_T* varDefVal = parserParseExpression(parser, scope); // value

  // Create the AST node with its values
  AST_T* varDef = initAST(AST_VARIABLE_DEFINITION);
  varDef->varDefVarName = varDefVarName;
  varDef->varDefVal = varDefVal;

  varDef->scope = scope;

  return varDef;
}

AST_T* parserParseFuncDef(parser_T* parser, scope_T* scope) {
  AST_T* funcDef = initAST(AST_FUNCTION_DEFINITION);

  parserEat(parser, TOKEN_ID); // func
  char* funcName = parser->currentToken->val;
  funcDef->funcDefName = calloc(
    strlen(funcName) + 1, 
    sizeof(char)
  );
  strcpy(funcDef->funcDefName, funcName);

  parserEat(parser, TOKEN_ID); // function name

  parserEat(parser, TOKEN_LPAREN); // (

  if (parser->currentToken->type != TOKEN_RPAREN) {
    // The arguments of the function
    funcDef->funcDefArgs = calloc(1, sizeof(struct AST_STRUCT*));
    AST_T* arg = parserParseVar(parser, scope);
    funcDef->funcDefArgsSize += 1;
    funcDef->funcDefArgs[funcDef->funcDefArgsSize - 1] = arg;

    while (parser->currentToken->type == TOKEN_COMMA) {
      parserEat(parser, TOKEN_COMMA); // ,
      funcDef->funcDefArgsSize += 1;

      funcDef->funcDefArgs = realloc(
        funcDef->funcDefArgs, 
        funcDef->funcDefArgsSize * sizeof(struct AST_STRUCT*)
      );

      AST_T* arg = parserParseVar(parser, scope);
      funcDef->funcDefArgs[funcDef->funcDefArgsSize - 1] = arg;
    }
  }

  parserEat(parser, TOKEN_RPAREN); // )
  parserEat(parser, TOKEN_LBRACE); // {  

  // The body of the function
  funcDef->funcDefBody = parserParseStatements(parser, scope);

  parserEat(parser, TOKEN_RBRACE); // }

  funcDef->scope = scope;

  return funcDef;
}

AST_T* parserParseVar(parser_T* parser, scope_T* scope) {
  char* tokenVal = parser->currentToken->val;
  parserEat(parser, TOKEN_ID); // variable name
  
  if (parser->currentToken->type == TOKEN_LPAREN) 
    return parserParseFuncCall(parser, scope);
  
  // Create the AST node with its values
  AST_T* var = initAST(AST_VARIABLE);
  var->varName = tokenVal;
  var->scope = scope;

  return var;
}

AST_T* parserParseString(parser_T* parser, scope_T* scope) {
  AST_T* string = initAST(AST_STRING);
  string->stringVal = parser->currentToken->val;
  
  parserEat(parser, TOKEN_STRING);

  string->scope = scope;

  return string;
}

AST_T* parserParseID(parser_T* parser, scope_T* scope) {
  if (strcmp(parser->currentToken->val, "let") == 0)
    return parserParseVarDef(parser, scope);
  
  if(strcmp(parser->currentToken->val, "func") == 0)
    return parserParseFuncDef(parser, scope);
  
  return parserParseVar(parser, scope);
}