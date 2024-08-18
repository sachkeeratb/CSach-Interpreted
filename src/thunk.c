#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/scope.h"
#include "include/parser.h"

// Lazy evaluation using thunks

// Thunk structure to hold delayed expressions
typedef struct THUNK_STRUCT {
	bool isEvaluated;
	void* val;
	AST_T* expression;  // Store the expression to evaluate later
} thunk_T;

// Function to initialize a thunk for a variable
thunk_T* initThunk(AST_T* expression) {
	thunk_T* thunk = malloc(sizeof(thunk_T));
	thunk->isEvaluated = false;
	thunk->expression = expression;
	return thunk;
}