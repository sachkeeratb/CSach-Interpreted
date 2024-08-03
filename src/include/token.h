#ifndef TOKEN_H
#define TOKEN_H
/**
 * @brief A token represents a single unit of meaning in a program.
 * 				Tokens are the smallest individual elements of a program's source code.
 * 				They can be keywords, identifiers, literals, operators, or punctuation marks.
 * 				Tokens are used by the compiler or interpreter to understand and parse the code.
 * 				Each token has a specific role and meaning within the programming language.
 */

typedef struct TOKEN_STRUCT {
  enum {
    TOKEN_ID, // Identifier
    TOKEN_EQUALS, // =
		TOKEN_STRING, // ""
		TOKEN_INT, // 1234
		TOKEN_SEMI, // ;
		TOKEN_LPAREN, // (
		TOKEN_RPAREN, // )
		TOKEN_LBRACE, // {
		TOKEN_RBRACE, // }
		TOKEN_LBRACKET, // [
    TOKEN_RBRACKET, // ]
		TOKEN_COMMA, // ,
		TOKEN_PLUS, // +
		TOKEN_MINUS, // -
		TOKEN_MULTIPLY, // *
		TOKEN_DIVIDE, // /
		TOKEN_POW, // ^
		TOKEN_MODULO, // %
		TOKEN_EOF // The end of the file
  } type;

	void* val; // Value of the token
} token_T;

token_T* initToken(int tokType, void* val);

#endif