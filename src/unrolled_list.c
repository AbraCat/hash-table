#include <unrolled_list.h>

#include <stdlib.h>
#include <string.h>

UnrNode* unr_ctr(UnrNode* next, char* s)
{
    UnrNode* node = (UnrNode*)calloc(1, sizeof(UnrNode));
    if (node == NULL) return NULL;

    int len = strlen(s);
    node->s = (char*)aligned_alloc(align, round_up(maxlen * unroll_coeff, align));
    if (node->s == NULL)
    {
        free(node);
        return NULL;
    }

    strncpy(node->s, s, len);
    for (int i = len; i < maxlen; ++i)
        node->s[i] = '\0';

    node->next = next;
    node->ind = 1;
    return node;
}

void unr_dtr(UnrNode* node)
{
    if (node == NULL) return;
    unr_dtr(node->next);
    free(node->s);
    free(node);
}

UnrNode* unr_insert(UnrNode* node, char* s)
{
    if (unr_find(node, s)) return node;
    if (node == NULL || node->ind == unroll_coeff) return unr_ctr(node, s);

    int len = strlen(s);
    strncpy(node->s + node->ind * maxlen, s, len);
    for (int i = len; i < maxlen; ++i)
        node->s[node->ind * maxlen + i] = '\0';

    node->ind++;
    return node;
}

int __attribute__ ((noinline)) unr_find(UnrNode* node, char* s)
{
    while (node != NULL)
    {
        for (int i = 0; i < unroll_coeff; ++i)
            if (tbl_strcmp(node->s + i * maxlen, s) == 0) return 1;
        node = node->next;
    }
    return 0;
}

int unr_n_keys(UnrNode *node)
{
    int cnt = 0;
    while (node != NULL)
    {
        cnt += node->ind;
        node = node->next;
    }
    return cnt;
}

void unr_dump(UnrNode* node, FILE* file)
{
    fprintf(file, "Unrolled list dump\n");
    while (node != NULL)
    {
        for (int i = 0; i < node->ind; ++i)
            fprintf(file, "%s ", node->s + i * maxlen);
        for (int i = node->ind; i < unroll_coeff; ++i)
            fprintf(file, "(null) ");
        fputc('\n', file);
        node = node->next;
    }
}