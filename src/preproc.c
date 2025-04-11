#include <preproc.h>
#include <table.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define buflen 256

int write_words(const char* in_path, const char* out_path)
{
    FILE *fin = fopen(in_path, "r"), *fout = fopen(out_path, "w");
    if (fin == NULL || fout == NULL) return 1;

    char buf[buflen] = "";
    while (fscanf(fin, "%s", buf) == 1)
    {
        int empty = 1;
        for (int c = 0; buf[c] != '\0'; ++c)
        {
            if (isalnum(buf[c]))
            {
                empty = 0;
                fputc(buf[c], fout);
            }
        }
        if (!empty) fputc('\n', fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

int write_unique(const char* in_path, const char* out_path, int* n_unique)
{
    FILE *fin = fopen(in_path, "r"), *fout = fopen(out_path, "w");
    if (fin == NULL || fout == NULL) return 1;

    Table* tbl = tbl_ctr(10000);
    if (tbl == NULL) return 1;

    char buf[buflen] = "";
    while (fscanf(fin, "%s", buf) == 1)
        if (strlen(buf) < maxlen)
            tbl_insert(tbl, buf);

    tbl_write_keys(tbl, fout);
    *n_unique = tbl_n_keys(tbl);

    tbl_dtr(tbl);
    fclose(fin);
    fclose(fout);
    return 0;
}

int fill_tbl(Table* tbl, const char* in_path, int n_words, char** words)
{
    FILE *fin = fopen(in_path, "r");
    if (fin == NULL) return 1;

    char* _words = (char*)calloc(n_words * maxlen, sizeof(char));
    if (_words == NULL) return 1;

    char buf[buflen] = "";
    for (int i = 0; i < n_words; ++i)
    {
        fscanf(fin, "%s", buf);
        strncpy(_words + maxlen * i, buf, maxlen - 1);
        _words[maxlen * i + maxlen - 1] = '\0';

        tbl_insert(tbl, buf);
    }

    *words = _words;
    return 0;
}

int get_rand_index(int max_ind)
{
    return rand() % max_ind;
}

char* get_word(char* words, int ind)
{
    return words + ind * maxlen;
}

int test_tbl(Table* tbl, int n_tests, int n_words, char* words)
{
    int found_cnt = 0;
    while (n_tests--)
    {
        int ind = get_rand_index(n_words);
        char* word = get_word(words, ind);
        if (tbl_find(tbl, word)) ++found_cnt;
    }
    return found_cnt;
}