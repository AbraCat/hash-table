#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include <utils.h>

typedef struct Node Node;

typedef struct Node
{
    char* s;
    Node* next;
} Node;

Node* node_ctr(Node* next, char* s);
void node_dtr(Node* node);
Node* lst_insert(Node* node, char* s);
int lst_find(Node* node, char* s);
int my_lst_find(Node* node, char* s); // asm

int lst_n_keys(Node *node);
void lst_dump(Node* node, FILE* file);

#endif // LIST_H