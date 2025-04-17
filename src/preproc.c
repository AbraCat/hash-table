#include <preproc.h>
#include <table.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define buflen 256

long fileSize(FILE *file)
{
    if (fseek(file, 0L, SEEK_END)) return -1;

    long siz = ftell(file);
    if (siz == -1L) return -1;

    if (fseek(file, 0L, SEEK_SET)) return -1;

    return siz;
}

int readFile(FILE* file, char** bufptr)
{
    long siz = fileSize(file);
    if (siz == -1L) return 1;

    char* buf = *bufptr = (char*)aligned_alloc(align, round_up(siz + 1, align));
    // char* buf = *bufptr = (char*)malloc(siz + 1);
    if (buf == NULL) return 1;

    fread(buf, sizeof(char), siz, file);
    return 0;
}

int write_words(const char* in_path, const char* out_path)
{
    FILE *fin = fopen(in_path, "r"), *fout = fopen(out_path, "w");
    if (fin == NULL || fout == NULL) return 1;

    char buf[buflen] = "";
    while (fscanf(fin, "%s", buf) == 1)
    {
        int empty = 1;
        for (int i = 0; buf[i] != '\0'; ++i)
        {
            char c = buf[i];
            if (isalpha(c))
            {
                empty = 0;
                if ('A' <= c && c <= 'Z') c += 'a' - 'A';
                fputc(c, fout);
            }
        }
        if (!empty) fputc('\n', fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

int write_unique(const char* in_path, const char* short_path, const char* long_path, int* n_short, int* n_long)
{
    FILE *fin = fopen(in_path, "r"), *fshort = fopen(short_path, "w"), *flong = fopen(long_path, "w");
    if (fin == NULL || fshort == NULL || flong == NULL) return 1;

    Table* tbl = tbl_ctr(10000);
    if (tbl == NULL) return 1;

    char buf[buflen] = "";
    while (fscanf(fin, "%s", buf) == 1)
        tbl_insert(tbl, buf);

    *n_short = *n_long = 0;
    for (int i = 0; i < tbl->n; ++i)
    {
        Node* node = tbl->data[i];
        while (node != NULL)
        {
            int len = strlen(node->s);
            if (len < maxlen)
            {
                ++(*n_short);
                fputs(node->s, fshort);
                for (int j = len; j < maxlen; ++j)
                    fputc('\0', fshort);
            }
            else
            {
                ++(*n_long);
                fprintf(flong, "%s\n", node->s);
            }
            node = node->next;
        }
    }

    tbl_dtr(tbl);
    fclose(fin);
    fclose(fshort);
    fclose(flong);
    return 0;
}

char* __attribute__ ((noinline)) get_word(char* words, int ind) { return words + ind * maxlen; }