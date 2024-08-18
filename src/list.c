#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/list.h"
#include "include/token.h"

list_T* initList() {
	// Allocate memory for the list
	list_T* list = (list_T*) malloc(sizeof(list_T));
	// Set the head of the list to NULL
	list->head = (void*) 0;
	return list;
}

node_T* createNewNode(long val) {
	// Allocate memory for the new node
  node_T* newNode = (node_T*) malloc(sizeof(node_T));
	// Set the value of the new node and set the next node to NULL
  newNode->val = val;
  newNode->next = (void*) 0;
  return newNode;
}

void push(list_T** list, long val) {
	// Create a new node
	node_T* newNode = createNewNode(val);

	// If the list is empty, set the head to the new node
	if (!(*list)->head) {
		(*list)->head = newNode;
		return;
	}

	// Traverse the list to the end and add the new node
	node_T* temp = (*list)->head;
	while (temp->next)
		temp = temp->next;
	
	// Add the new node to the end of the list
	temp->next = newNode;
}

long pop(list_T** list) {
	// Check if the list is empty
	if (!(*list)->head) {
		printf("Error: Empty list/expression recieved a call to take out more input.\n");
		exit(1);
	}

	// If the list has only one element, remove the element and return the value
	if (!(*list)->head->next) {
		long val = (*list)->head->val;
		free((*list)->head);
		(*list)->head = (void*) 0;
		return val;
	}

	// Traverse the list to the second last element
	node_T* temp = (*list)->head;
	while (temp->next->next) 
		temp = temp->next;
	
	// Get the value of the last element to return
	long val = temp->next->val;

	// Free the memory of the last element and set the next of the second last element to NULL
	free(temp->next);
	temp->next = (void*) 0;

	return val;
}

int getSize(list_T** list) {
	// Traverse the list and count the number of elements
	int size = 0;
	for (node_T* current = (*list)->head; current; current = current->next)
		size++;

	// Return the size of the list
	return size;
}

void evalExponents(list_T** opList, list_T** numList) {
	// Store the current and previous number and operator nodes
  node_T* currentNum = (*numList)->head;
  node_T* currentOp = (*opList)->head;
	node_T* prevOp = (void*) 0;

	// Traverse the operator list while there are still operators
	while (currentOp) {
		// If the current operator is not an exponent, move to the next operator
		if (currentOp->val != TOKEN_POW) {
			currentNum = currentNum->next;
			prevOp = currentOp;
			currentOp = currentOp->next;
			continue;
		}

		// Calculate the result of the exponent
		long result;
		if (currentNum->next->val == 0)
			result = 1;
		else if (currentNum->next->val < 0) {
			printf("Error: Negative exponents are not supported for this number type.\n");
			exit(1);
		}
		else {
			result = currentNum->val;
			for (int i = 1; i < currentNum->next->val; i++)
				result *= currentNum->val;
		}

		// Update the linked list to replace operand nodes with the result
		currentNum->val = result;
		node_T* nextNum = currentNum->next;
		currentNum->next = currentNum->next->next;
		free(nextNum);

		// Remove the operator node
		if (!prevOp)
			(*opList)->head = currentOp->next;
		else
			prevOp->next = currentOp->next;
			
		// Free the memory of the operator node and move to the next operator
		node_T* tempOp = currentOp;
		currentOp = currentOp->next;
		free(tempOp);
	}
}

void evalMD(list_T** opList, list_T** numList) {
  // Store the current and previous number and operator nodes
  node_T* currentNum = (*numList)->head;
  node_T* currentOp = (*opList)->head;
	node_T* prevOp = (void*) 0;

	// Traverse the operator list while there are still operators
	while (currentOp) {
		// If the current operator is not multiplication, division, or modulo, move to the next operator
		if (!(currentOp->val == TOKEN_MULTIPLY) && !(currentOp->val == TOKEN_DIVIDE) && !(currentOp->val == TOKEN_MODULO)) {
			currentNum = currentNum->next;
			prevOp = currentOp;
			currentOp = currentOp->next;
			continue;
		}

		// Calculate the result of the operation
		long result;
		switch(currentOp->val) {
			case TOKEN_MULTIPLY:
				result = currentNum->val * currentNum->next->val;
				break;
			case TOKEN_DIVIDE:
				result = currentNum->val / currentNum->next->val;
				break;
			case TOKEN_MODULO:
				result = currentNum->val % currentNum->next->val;
				break;
		}

		// Update the linked list to replace operand nodes with the result
		currentNum->val = result;
		node_T* nextNum = currentNum->next;
		currentNum->next = currentNum->next->next;
		free(nextNum);

		// Remove the operator node
		if (!prevOp)
			(*opList)->head = currentOp->next;
		else
			prevOp->next = currentOp->next;
			
		// Free the memory of the operator node and move to the next operator
		node_T* tempOp = currentOp;
		currentOp = currentOp->next;
		free(tempOp);
	}
}

long evalAS(list_T** opList, list_T** numList) {
	// Store the current number and operator nodes
  node_T* currentNum = (*numList)->head;
  node_T* currentOp = (*opList)->head;

	// Store the result of the expression
	long result = currentNum->val;

	// Traverse the operator list while there are still operators
  while (currentOp) {
		// Move to the next number and operator nodes
		currentNum = currentNum->next;

		// If the current operator is addition, add the number to the result
		if (currentOp->val == TOKEN_PLUS) 
			result += currentNum->val;
		// Otherwise, subtract the number from the result
		else
			result -= currentNum->val;

		// Move to the next operator node
		currentOp = currentOp->next;
  }

  return result;
}

long eval(list_T** opList, list_T** numList) {
	// Evaluate the exponents
	evalExponents(opList, numList);

	// Evaluate the multiplication, division, and modulo
	evalMD(opList, numList);

	// Evaluate the addition and subtraction
	return evalAS(opList, numList);
}