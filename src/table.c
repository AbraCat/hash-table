#include <table.h>

#include <stdlib.h>
#include <string.h>

const int maxlen = 32, align = 32;

int __attribute__ ((noinline)) hash_fn(char* s, int mod)
{
    int h = 5381;
    for (; *s != '\0'; ++s)
        h = (h << 5) + h + *s;
    return (h % mod + mod) % mod;
}

int round_up(int n, int align) { return n % align == 0 ? n : align * (n / align + 1); }

Node* node_ctr(Node* next, char* s)
{
    Node* node = (Node*)calloc(sizeof(Node), 1);
    if (node == NULL) return NULL;

    int len = strlen(s);
    node->s = (char*)aligned_alloc(align, round_up(len > maxlen ? len : maxlen, align));
    // node->s = (char*)malloc(len > maxlen ? len : maxlen);
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
    if (lst_find(node, s) != NULL) return node;
    return node_ctr(node, s);
}

Node* __attribute__ ((noinline)) lst_find(Node* node, char* s)
{
    while (node != NULL)
    {
        if (strcmp(node->s, s) == 0) return node;
        node = node->next;
    }
    return NULL;
}

Table* tbl_ctr(int n)
{
    Table* tbl = (Table*)calloc(sizeof(Table), 1);
    tbl->n = n;
    tbl->data = (Node**)calloc(n, sizeof(Node*));

    return tbl;
}

void tbl_dtr(Table* tbl)
{
    for (int i = 0; i < tbl->n; ++i)
        node_dtr(tbl->data[i]);
    free(tbl->data);
    free(tbl);
}

void tbl_insert(Table* tbl, char* s)
{
    int h = hash_fn(s, tbl->n);
    tbl->data[h] = lst_insert(tbl->data[h], s);
}

int __attribute__ ((noinline)) tbl_find(Table* tbl, char* s)
{
    int h = hash_fn(s, tbl->n);
    return lst_find(tbl->data[h], s) != NULL;
}

int lst_n_keys(Node* node)
{
    int cnt = 0;
    while (node != NULL)
    {
        ++cnt;
        node = node->next;
    }
    return cnt;
}

void lst_write_keys(Node* node, FILE* fout)
{
    while (node != NULL)
    {
        fprintf(fout, "%s\n", node->s);
        node = node->next;
    }
}

int tbl_n_keys(Table* tbl)
{
    int cnt = 0;
    for (int i = 0; i < tbl->n; ++i)
        cnt += lst_n_keys(tbl->data[i]);
    return cnt;
}

void tbl_write_keys(Table* tbl, FILE* fout)
{
    for (int i = 0; i < tbl->n; ++i)
        lst_write_keys(tbl->data[i], fout);
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

void tbl_dump(Table* tbl, FILE* file)
{
    fprintf(file, "Hash table %p\nn: %d\n", tbl, tbl->n);
    for (int i = 0; i < tbl->n; ++i)
    {
        fprintf(file, "%d: ", i);
        lst_dump(tbl->data[i], file);
    }
}