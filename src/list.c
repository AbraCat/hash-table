#include <list.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

Node* node_ctr(Node* next, char* s)
{
    Node* node = (Node*)calloc(sizeof(Node), 1);
    if (node == NULL) return NULL;

    int len = strlen(s);
    node->s = (char*)aligned_alloc(align, round_up(len > maxlen ? len : maxlen, align));
    if (node->s == NULL)
    {
        free(node);
        return NULL;
    }

    strncpy(node->s, s, len);
    for (int i = len; i < maxlen; ++i)
        node->s[i] = '\0';

    node->next = next;
    return node;
}

void node_dtr(Node* node)
{
    if (node == NULL) return;
    node_dtr(node->next);
    free(node->s);
    free(node);
}

Node* lst_insert(Node* node, char* s)
{
    if (lst_find(node, s)) return node;
    return node_ctr(node, s);
}

int __attribute__ ((noinline)) lst_find(Node* node, char* s)
{
    while (node != NULL)
    {
        // assert((strcmp(node->s, s) == 0) == (mystrcmp(node->s, s) == 0));
        if (tbl_strcmp(node->s, s) == 0) return 1;
        node = node->next;
    }
    return 0;
}

int lst_n_keys(Node *node)
{
    int cnt = 0;
    while (node != NULL)
    {
        ++cnt;
        node = node->next;
        // node ->= next;
    }
    return cnt;
}

void lst_dump(Node* node, FILE* file)
{
    while(node != NULL)
    {
        fprintf(file, "%s ", node->s);
        node = node->next;
    }
    fputc('\n', file);
}