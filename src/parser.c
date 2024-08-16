#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "include/parser.h"
#include "include/scope.h"

parser_T* initParser(lexer_T* lexer) {
  parser_T* parser = calloc(1, sizeof(parser_T)); // Allocate memory for the parser
  parser->lexer = lexer; // Set the lexer of the parser
  parser->currentToken = getNextToken(lexer); // Set the current token of the parser
  parser->prevToken = parser->currentToken; // Set the previous token of the parser
  parser->scope = initScope(); // Set the scope of the parser

  return parser;
}

void eat(parser_T* parser, int tokenType) {
  // Check if the current token is of the correct type
  if ((int) parser->currentToken->type != tokenType) {
    printf(
      "Unexpected token `%s` with type %d\n", (char*) parser->currentToken->val, 
      parser->currentToken->type
    );
    printf(
      "Expected token with type %d, which represents ", 
      tokenType
    );
    switch (tokenType) {
      case TOKEN_EQUALS: printf("=\n"); break;
		  case TOKEN_STRING: printf("a string.\n"); break;
		  case TOKEN_CHAR: printf("a character.\n"); break;
		  case TOKEN_INT: printf("an integer\n"); break;
		  case TOKEN_SEMI: printf(";\n"); break;
		  case TOKEN_LPAREN: printf("(\n"); break;
		  case TOKEN_RPAREN: printf(")\n"); break;
		  case TOKEN_LBRACE: printf("{\n"); break;
		  case TOKEN_RBRACE: printf("}\n"); break;
		  case TOKEN_LBRACKET: printf("[\n"); break;
      case TOKEN_RBRACKET: printf("]\n"); break;
		  case TOKEN_COMMA: printf(",\n"); break;
		  case TOKEN_PLUS: printf("+\n"); break;
		  case TOKEN_MINUS: printf("-\n"); break;
		  case TOKEN_MULTIPLY: printf("*\n"); break;
		  case TOKEN_DIVIDE: printf("/\n"); break;
		  case TOKEN_POW: printf("^\n"); break;
		  case TOKEN_MODULO: printf("%%\n"); break;
		  case TOKEN_EOF: printf("EOF\n"); break;
      default: printf("an unknown token.\n"); break;
    }
    exit(1);
  }

  // Set the previous token to the current token and advance the current token
  parser->prevToken = parser->currentToken;
  parser->currentToken = getNextToken(parser->lexer);
}

AST_T* parseStatement(parser_T* parser, scope_T* scope) {
  // Check the type of the current token and parse accordingly
  switch (parser->currentToken->type) {
    case TOKEN_STRING: return parseString(parser, scope); break;
    case TOKEN_ID: return parseID(parser, scope); break;
    case TOKEN_CHAR: return parseChar(parser, scope); break;
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_INT: return parseIntExpr(parser, scope); break;
    default: return initAST(AST_NOOP); break;
  }
}

AST_T* parseStatements(parser_T* parser, scope_T* scope) {
  // Create a compound AST node to hold the statements and allocate memory for the statements
  AST_T* compound = initAST(AST_COMPOUND);
  compound->compoundVal = calloc(1, sizeof(struct AST_STRUCT));
  
  // Parse the first statement
  AST_T* statement = parseStatement(parser, scope);
  statement->scope = scope;

  // Add the statement to the compound node
  compound->compoundVal[0] = statement;
  compound->compoundSize += 1;
  compound->scope = scope;  

  // Parse the rest of the statements, using a semicolon as the seperator
  while(parser->currentToken->type == TOKEN_SEMI) {
    eat(parser, TOKEN_SEMI);

    AST_T* statement = parseStatement(parser, scope);

    // If there is another statement, increase the size of the compound and reallocate memory for the compound's values
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

AST_T* parseFuncDef(parser_T* parser, scope_T* scope) {
  AST_T* funcDef = initAST(AST_FUNCTION_DEFINITION);

  eat(parser, TOKEN_ID); // func
  char* funcName = parser->currentToken->val;
  funcDef->funcDefName = calloc(
    strlen(funcName) + 1, 
    sizeof(char)
  );
  strcpy(funcDef->funcDefName, funcName);

  eat(parser, TOKEN_ID); // function name

  eat(parser, TOKEN_LPAREN); // (

  if (parser->currentToken->type != TOKEN_RPAREN) {
    // The arguments of the function
    funcDef->funcDefArgs = calloc(1, sizeof(struct AST_STRUCT*));
    AST_T* arg = parseVar(parser, scope);
    funcDef->funcDefArgsSize += 1;
    funcDef->funcDefArgs[funcDef->funcDefArgsSize - 1] = arg;

    while (parser->currentToken->type == TOKEN_COMMA) {
      eat(parser, TOKEN_COMMA); // ,
      funcDef->funcDefArgsSize += 1;

      funcDef->funcDefArgs = realloc(
        funcDef->funcDefArgs, 
        funcDef->funcDefArgsSize * sizeof(struct AST_STRUCT*)
      );

      AST_T* arg = parseVar(parser, scope);
      funcDef->funcDefArgs[funcDef->funcDefArgsSize - 1] = arg;
    }
  }

  eat(parser, TOKEN_RPAREN); // )
  eat(parser, TOKEN_LBRACE); // {  

  // The body of the function
  funcDef->funcDefBody = parseStatements(parser, scope);

  eat(parser, TOKEN_RBRACE); // }

  funcDef->scope = scope;

  return funcDef;
}

AST_T* parseFuncCall(parser_T* parser, scope_T* scope) {
  // Parse a function call and create an AST node with the function name and arguments as the value
  AST_T* funcCall = initAST(AST_FUNCTION_CALL);
  funcCall->funcCallName = parser->prevToken->val;

  eat(parser, TOKEN_LPAREN);

  // If there are arguments
  if (parser->currentToken->type != TOKEN_RPAREN) {
    funcCall->funcCallArgs = calloc(1, sizeof(struct AST_STRUCT));
    
    AST_T* statement = parseStatement(parser, scope);
    funcCall->funcCallArgs[0] = statement;
    funcCall->funcCallArgsSize += 1;

    // Go through the arguments of the function
    while(parser->currentToken->type == TOKEN_COMMA) {
      eat(parser, TOKEN_COMMA);

      AST_T* statement = parseStatement(parser, scope);
      funcCall->funcCallArgsSize += 1;
      
      funcCall->funcCallArgs = realloc(
        funcCall->funcCallArgs, 
        (funcCall->funcCallArgsSize + 1) * sizeof(struct AST_STRUCT)
      );

      funcCall->funcCallArgs[funcCall->funcCallArgsSize - 1] = statement;
    }
  }

  eat(parser, TOKEN_RPAREN);

  funcCall->scope = scope; // Add it to the scope

  return funcCall;
}

AST_T* parseVarDef(parser_T* parser, scope_T* scope) {
  eat(parser, TOKEN_ID); // let
  char* varDefVarName = parser->currentToken->val;
  eat(parser, TOKEN_ID); // variable name
  eat(parser, TOKEN_EQUALS); // =
  AST_T* varDefVal = parseStatement(parser, scope); // value

  // Create the AST node with its values
  AST_T* varDef = initAST(AST_VARIABLE_DEFINITION);
  varDef->varDefVarName = varDefVarName;
  varDef->varDefVal = varDefVal;

  varDef->scope = scope; // Add it to the scope

  return varDef;
}

AST_T* parseVar(parser_T* parser, scope_T* scope) {
  // Parse a variable and create an AST node with the variable name as the value
  char* tokenVal = parser->currentToken->val;
  eat(parser, TOKEN_ID); // variable name
  
  // Parse function arguments
  if (parser->currentToken->type == TOKEN_LPAREN) 
    return parseFuncCall(parser, scope);
  
  // Create the AST node with its values
  AST_T* var = initAST(AST_VARIABLE);
  var->varName = tokenVal;
  var->scope = scope; // Add it to the scope

  return var;
}

AST_T* parseString(parser_T* parser, scope_T* scope) {
  // Parse a string and create an AST node with the string as the value
  AST_T* string = initAST(AST_STRING);
  string->stringVal = parser->currentToken->val;
  
  eat(parser, TOKEN_STRING);

  while(parser->currentToken->type == TOKEN_PLUS) {
    eat(parser, TOKEN_PLUS);
    if (parser->currentToken->type != TOKEN_STRING) {
      printf("Concantinating non-string types with strings is currently unsupported.\n");
      exit(1);
    }
    string->stringVal = strcat(string->stringVal, (char*) parser->currentToken->val);
    eat(parser, TOKEN_STRING);
  }

  string->scope = scope;

  return string;
}

AST_T* parseChar(parser_T* parser, scope_T* scope) {
  // Parse a character and create an AST node with the character as the value
  AST_T* character = initAST(AST_CHAR);
  character->charVal = *(char*) parser->currentToken->val;
  
  // Move past the character
  eat(parser, TOKEN_CHAR);
  
  character->scope = scope;

  return character;
}


AST_T* parseIntExpr(parser_T* parser, scope_T* scope) {
  list_T* numList = initList();
  list_T* opList = initList();

  // Check if the first number is positive or negative and assign the value accordingly
  if (parser->currentToken->type == TOKEN_PLUS) {
    eat(parser, TOKEN_PLUS);
    push(&numList, (intptr_t) parser->currentToken->val);
  }
  else if (parser->currentToken->type == TOKEN_MINUS) {
    eat(parser, TOKEN_MINUS);
    push(&numList, -1 * (intptr_t) parser->currentToken->val);
  }
  else
    push(&numList, (intptr_t) parser->currentToken->val);
  
  eat(parser, TOKEN_INT);

  // Check if there are more operations to perform on the number
  int keepRepeat = 1;
  while (keepRepeat) {
    switch (parser->currentToken->type) {
      // If the token is a valid operation token, push it to the operation list and push the number to the number list
      case TOKEN_PLUS:
      case TOKEN_MINUS:
      case TOKEN_MULTIPLY:
      case TOKEN_DIVIDE:
      case TOKEN_POW:
      case TOKEN_MODULO:
        push(&opList, parser->currentToken->type);
        eat(parser, parser->currentToken->type);

        push(&numList, (intptr_t) parser->currentToken->val);
        eat(parser, TOKEN_INT);
        break;

      default:
        keepRepeat = 0;
        break;
    }    
  }

  // Initialize the AST node with the integer value
  AST_T* num = initAST(AST_INT);

  // Evaluate the expression and assign the value to the AST node
  num->intVal = eval(&opList, &numList);

  num->scope = scope;

  return num;
}

AST_T* parseID(parser_T* parser, scope_T* scope) {
  // Check the current identifier and parse accordingly
  if (strcmp(parser->currentToken->val, "let") == 0)
    return parseVarDef(parser, scope);
  
  if(strcmp(parser->currentToken->val, "func") == 0)
    return parseFuncDef(parser, scope);
  
  return parseVar(parser, scope);
}