#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "include/lexer.h"

// Initialize a new lexer with the contents of a file
lexer_T* initLexer(char* contents) {
  lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT)); // Allocate memory for the lexer
  lexer->contents = contents; // Set the contents of the lexer to the contents of the file
  lexer->c = contents[lexer->i]; // Set the current character to the first character in the file

  return lexer;
}

// Advance the lexer
void advance(lexer_T* lexer) {
  // If the current character isn't null and we aren't at the end of the file, advance
  if ((lexer->c != '\0') && (lexer->i < strlen(lexer->contents))) {
    lexer->i += 1;
    lexer->c = lexer->contents[lexer->i];
  }
}

void skipWhitespace(lexer_T* lexer) {
  // While there is either a space or a new line, we advance or "skip" it
  while (lexer->c == ' ' || lexer->c == '\n')
    advance(lexer);  
}

token_T* getNextToken(lexer_T* lexer) {
  // While the character isn't null and we aren't at the end of the line, get the next token
  while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
    // Whitespace
    if (lexer->c == ' ' || lexer->c == '\n')
      skipWhitespace(lexer);  

    // Numbers
    if (isdigit(lexer->c)) 
      return collectInt(lexer);

    // Identifiers
		if (isalpha(lexer->c)) 
			return collectID(lexer);

    // The beginning of a stirng
    if (lexer->c == '"') 
      return collectString(lexer);
    
    if (lexer->c == '\'') 
      return collectChar(lexer);
    
    switch (lexer->c) {
      case '=': return advanceWithToken(lexer, initToken(TOKEN_EQUALS, getCurrentCharAsString(lexer))); break;
      case ';': return advanceWithToken(lexer, initToken(TOKEN_SEMI, getCurrentCharAsString(lexer))); break;
      case '(': return advanceWithToken(lexer, initToken(TOKEN_LPAREN, getCurrentCharAsString(lexer))); break;
      case ')': return advanceWithToken(lexer, initToken(TOKEN_RPAREN, getCurrentCharAsString(lexer))); break;
      case '{': return advanceWithToken(lexer, initToken(TOKEN_LBRACE, getCurrentCharAsString(lexer))); break;
      case '}': return advanceWithToken(lexer, initToken(TOKEN_RBRACE, getCurrentCharAsString(lexer))); break;
      case '[': return advanceWithToken(lexer, initToken(TOKEN_LBRACKET, getCurrentCharAsString(lexer))); break;
      case ']': return advanceWithToken(lexer, initToken(TOKEN_RBRACKET, getCurrentCharAsString(lexer))); break;
      case ',': return advanceWithToken(lexer, initToken(TOKEN_COMMA, getCurrentCharAsString(lexer))); break;

      // Math
      case '+': return advanceWithToken(lexer, initToken(TOKEN_PLUS, getCurrentCharAsString(lexer))); break;
      case '-': return advanceWithToken(lexer, initToken(TOKEN_MINUS, getCurrentCharAsString(lexer))); break;
      case '*': return advanceWithToken(lexer, initToken(TOKEN_MULTIPLY, getCurrentCharAsString(lexer))); break;
      case '/': return advanceWithToken(lexer, initToken(TOKEN_DIVIDE, getCurrentCharAsString(lexer))); break;
      case '^': return advanceWithToken(lexer, initToken(TOKEN_POW, getCurrentCharAsString(lexer))); break;
      case '%': return advanceWithToken(lexer, initToken(TOKEN_MODULO, getCurrentCharAsString(lexer))); break;
    }
  }

  // Return the end of file token
	return initToken(TOKEN_EOF, "\0");
}

token_T* collectString(lexer_T* lexer) {
  // Move past the first "
  advance(lexer);

  char* value = calloc(1, sizeof(char)); // Allocate memory for the value
  value[0] = '\0'; // Set the first character to null

  // While we are not at the final 
  while(lexer->c != '"') {
    char* s = getCurrentCharAsString(lexer); // Get the current character as a string
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char)); // Reallocate memory for the value

    // Append 
    strlcat(value, s, strlen(value) + strlen(s) + 1);

		// Advance to the next character
		advance(lexer);
  }

  // Move past the final "
  advance(lexer);

	return initToken(TOKEN_STRING, value); // Return the token
}

token_T* collectChar(lexer_T* lexer) {
  // Move past the first '
  advance(lexer);

  if (lexer->c == '\'') 
    exit(1);
  

  char value = lexer->c; // Get the current character
  advance(lexer); // Move past the current character

  // Check if the next character is a closing single quote
  if (lexer->c != '\'') {
    printf("Error: Expected a closing single quote, not `%c`.\n", lexer->c);
    exit(1);
  }

  // Move past the final '
  advance(lexer);

	return initToken(TOKEN_CHAR, &value); // Return the token
}

token_T* collectID(lexer_T* lexer) {
  char* value = calloc(1, sizeof(char)); // Allocate memory for the value
  value[0] = '\0'; // Set the first character to null

  // While the current character is a letter
  while(isalpha(lexer->c)) { 
    char* s = getCurrentCharAsString(lexer); // Get the current character as a string
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char)); // Reallocate memory for the value

    // Append 
    strlcat(value, s, strlen(value) + strlen(s) + 1); // Append the current character to the value

		// CHARGE!!! ATTACK THE NEXT CHARACTER!
		// WE WILL NOT STOP UNTIL OUR KINGDOM IS VICTORIOUS!
		advance(lexer);
  }

	return initToken(TOKEN_ID, value); // Return the token
}

token_T* collectInt(lexer_T* lexer) {
  char* value = calloc(1, sizeof(char)); // Allocate memory for the value
  char* endptr; // Create a pointer to the end of the string
  value[0] = '\0'; // Set the first character to null

  // While the current character is a number
  while (isdigit(lexer->c)) {
    char* s = getCurrentCharAsString(lexer); // Get the current character as a string
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char)); // Reallocate memory for the value
    strcat(value, s); // Append 
		advance(lexer); // Advance to the next character
  }

  long valAsInt = strtol(value, &endptr, 10); // Convert the value to an integer

	return initToken(TOKEN_INT, (void*) valAsInt); // Return the token with the value as a void pointer casted from an integer
}

token_T* advanceWithToken(lexer_T* lexer, token_T* token) {
  advance(lexer); // Advance the lexer
  return token;
}

char* getCurrentCharAsString(lexer_T* lexer) {
	char* str = calloc(2, sizeof(char)); // Allocate memory for the string
	str[0] = lexer->c; // Set the first character to the current character
	str[1] = '\0'; // Set the second character to null
	return str;
}