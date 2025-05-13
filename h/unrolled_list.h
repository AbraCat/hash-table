#ifndef UNROLLED_LIST_H
#define UNROLLED_LIST_H

#include <stdio.h>

#include <utils.h>

typedef struct UnrNode UnrNode;

typedef struct UnrNode
{
    char* s;
    UnrNode* next;
    int ind;
} UnrNode;

UnrNode* unr_ctr(UnrNode* next, char* s);
void unr_dtr(UnrNode* node);
UnrNode* unr_insert(UnrNode* node, char* s);
int unr_find(UnrNode* node, char* s);

int unr_n_keys(UnrNode *node);
void unr_dump(UnrNode* node, FILE* file);

#endif // UNROLLED_LIST_H