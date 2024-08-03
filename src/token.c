#include <stdlib.h>
#include "include/token.h"

token_T* initToken(int type, void* val) {
  token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT)); // Allocate memory for the token
  token->type = type; // Set the type of the token
  token->val = val; // Set the value of the token
  
  return token;
}