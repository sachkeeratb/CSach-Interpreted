#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/list.h"
#include "include/token.h"

list_T* initList() {
	list_T* list = calloc(1, sizeof(list_T));
	return list;
}

void push(list_T** list, long val) {
	node_T* newNode = malloc(sizeof(node_T));
	newNode->val = val;
	newNode->next = (void*) 0;

	if (!(*list)->head) {
		(*list)->head = newNode;
		return;
	}

	node_T* temp = (*list)->head;
	while (temp->next)
		temp = temp->next;
	
	temp->next = newNode;
}

long pop(list_T** list) {
	if (!(*list)->head) 
		return -1;

	if (!(*list)->head->next) {
		long val = (*list)->head->val;
		free((*list)->head);
		(*list)->head = (void*) 0;
		return val;
	}

	node_T* temp = (*list)->head;
	while (temp->next->next) 
		temp = temp->next;
	
	long val = temp->next->val;

	free(temp->next);
	temp->next = (void*) 0;

	return val;
}

int getSize(list_T** list) {
	if (!(*list)->head) 
		return 0;

	if (!(*list)->head->next) 
		return 1;

	int size = 0;
	for (node_T* current = (*list)->head; current; current = current->next)
		size++;

	return size;
}

void evalExponents(list_T** opList, list_T** numList) {
	node_T* currentNum = (*numList)->head;
	node_T* currentOp = (*opList)->head;
	node_T* prevNum = (void*) 0;

	while (currentOp) {			
		if (currentOp->val != TOKEN_POW) {
			prevNum = currentNum;
			currentNum = currentNum->next;
			currentOp = currentOp->next;
			continue;
		}
		node_T* nextNum = currentNum->next;

		long result = currentNum->val;
		for (long i = 1; i < nextNum->val; i++)
			result *= currentNum->val;
		
		currentNum->val = result;  // Store the result in the current number node
		currentNum->next = nextNum->next;  // Remove the next number node

		// Free the next number node
		free(nextNum);

		// Remove the operator node
		node_T* tempOp = currentOp;
		if (!prevNum) 
			(*opList)->head = currentOp->next;  // Update head if we remove the first operator
		else 
			prevNum->next = currentNum;  // Skip the removed node
			
		currentOp = currentOp->next;
		free(tempOp);
	}
}

void evalMD(list_T** opList, list_T** numList) {
	node_T* currentNum = (*numList)->head;
	node_T* currentOp = (*opList)->head;
	node_T* prevNum = (void*) 0;

	while (currentOp) {
		if (currentOp->val != TOKEN_MULTIPLY && currentOp->val != TOKEN_DIVIDE && currentOp->val != TOKEN_MODULO) {
			prevNum = currentNum;
			currentNum = currentNum->next;
			currentOp = currentOp->next;
			if (!currentOp) 
				break;
			continue;
		}

		node_T* nextNum = currentNum->next;
		long result;
		switch (currentOp->val) {
			case TOKEN_MULTIPLY: result = currentNum->val * nextNum->val; break;
			case TOKEN_DIVIDE: result = currentNum->val / nextNum->val; break;
			case TOKEN_MODULO: result = currentNum->val % nextNum->val; break;
		}
			
		currentNum->val = result;  // Store the result in the current number node
		currentNum->next = nextNum->next;  // Remove the next number node

		// Free the next number node
		free(nextNum);

		// Remove the operator node
		node_T* tempOp = currentOp;
		if (!prevNum) 
			(*opList)->head = currentOp->next;  // Update head if we remove the first operator
		else 
			prevNum->next = currentNum;  // Skip the removed node
			
		currentOp = currentOp->next;
		free(tempOp);
	}
}

void evalAS(list_T** opList, list_T** numList) {
	node_T* currentNum = (*numList)->head;
	node_T* currentOp = (*opList)->head;
	node_T* prevNum = (void*) 0;

	while (currentOp) {
		if (!(currentOp->val == TOKEN_PLUS) && !(currentOp->val == TOKEN_MINUS)) {
			prevNum = currentNum;
			currentNum = currentNum->next;
			currentOp = currentOp->next;
			if (!currentOp) 
				break;
			continue;
		}

		node_T* nextNum = currentNum->next;
		long result = currentOp->val == TOKEN_PLUS ? currentNum->val + nextNum->val : currentNum->val - nextNum->val;
			
		currentNum->val = result;  // Store the result in the current number node
		currentNum->next = nextNum->next;  // Remove the next number node

		// Free the next number node
		free(nextNum);

		// Remove the operator node
		node_T* tempOp = currentOp;
		if (!prevNum) 
			(*opList)->head = currentOp->next;  // Update head if we remove the first operator
		else 
			prevNum->next = currentNum;  // Skip the removed node

		currentOp = currentOp->next;
		free(tempOp);
	}
}

long eval(list_T** opList, list_T** numList) {
	evalExponents(opList, numList);
	evalMD(opList, numList);
	evalAS(opList, numList);
  return (*numList)->head->val;
}