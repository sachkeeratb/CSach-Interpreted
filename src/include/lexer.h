#ifndef LEXER_H
#define LEXER_H
#include "token.h"

/**
 * @brief A lexer is a component of a compiler or interpreter that breaks down the source code into a sequence of tokens.
 *        It scans the input code character by character and groups them into meaningful units called tokens.
 *        These tokens are then used by the parser to build the abstract syntax tree (AST) of the program.
 *        The lexer plays a crucial role in the compilation process as it helps in identifying the structure and meaning of the code.
 */

typedef struct LEXER_STRUCT {
	char c; // Current character
	unsigned int i; // Current index
	char* contents; // File contents
} lexer_T;

lexer_T* initLexer(char* contents);

void advance(lexer_T* lexer);

void skipWhitespace(lexer_T* lexer);

token_T* getNextToken(lexer_T* lexer);

token_T* collectString(lexer_T* lexer);

token_T* collectChar(lexer_T* lexer);

token_T* collectID(lexer_T* lexer);

token_T* collectInt(lexer_T* lexer);

token_T* advanceWithToken(lexer_T* lexer, token_T* token);

char* getCurrentCharAsString(lexer_T* lexer);

#endif