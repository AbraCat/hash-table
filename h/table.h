#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

extern const int maxlen, align;

typedef struct Node Node;
typedef struct Table Table;

typedef struct Node
{
    char* s;
    Node* next;
} Node;

typedef struct Table
{
    Node** data;
    int n;
} Table;

int hash_fn(char* s, int mod);
int round_up(int n, int align);

Node* node_ctr(Node* next, char* s);
void node_dtr(Node* node);
Node* lst_insert(Node* node, char* s);
Node* lst_find(Node* node, char* s);

Table* tbl_ctr(int n);
void tbl_dtr(Table* tbl);
void tbl_insert(Table* tbl, char* s);
int tbl_find(Table* tbl, char* s);

int lst_n_keys(Node* node);
void lst_write_keys(Node* node, FILE* fout);
int tbl_n_keys(Table* tbl);
void tbl_write_keys(Table* tbl, FILE* fout);

void lst_dump(Node* node, FILE* file);
void tbl_dump(Table* tbl, FILE* file);

#endif // TABLE_H