#ifndef LIST_H
#define LIST_H

typedef struct Node {
  long val;
  struct Node* next;
} node_T;

typedef struct List {
  node_T* head;
} list_T;

list_T* initList();

void push(list_T** list, long val);

long pop(list_T** list);

int getSize(list_T** list);

void evalExponents(list_T** opList, list_T** numList);

void evalMD(list_T** opList, list_T** numList);

void evalAS(list_T** opList, list_T** numList);

long eval(list_T** opList, list_T** numList);

#endif