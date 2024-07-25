#include <stdlib.h>
#include "include/token.h"

token_T* initToken(int type, char* value) {
  token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
  token->type = type;
  token->value = value;
  
  return token;
}