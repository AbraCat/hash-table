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

    char* buf = *bufptr = (char*)calloc(siz + 1, sizeof(char));
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
        tbl_insert(tbl, buf);

    *n_unique = tbl_n_keys(tbl);
    tbl_write_keys(tbl, fout);

    tbl_dtr(tbl);
    fclose(fin);
    fclose(fout);
    return 0;
}

void divide_words(int n_words, char* txt, char** words)
{
    int w = 0;
    words[0] = txt;
    for (int c = 0; w < n_words; ++c)
    {
        if (txt[c] == '\n')
        {
            txt[c] = '\0';
            ++w;
            if (w != n_words) words[w] = txt + c + 1;
        }
    }
}

int fill_tbl(Table* tbl, Node** long_lst, const char* in_path, int n_words, char** txt_buf, char** words)
{
    FILE *fin = fopen(in_path, "r");
    if (fin == NULL) return 1;

    if (readFile(fin, txt_buf) != 0) return 1;
    divide_words(n_words, *txt_buf, words);

    for (int i = 0; i < n_words; ++i)
    {
        if (strlen(words[i]) < maxlen) tbl_insert(tbl, words[i]);
        else *long_lst = lst_insert(*long_lst, words[i]);
    }

    return 0;
}

int get_rand_index(int max_ind)
{
    return rand() % max_ind;
}

int test_tbl(Table* tbl, Node* long_lst, int n_tests, int n_words, char** words)
{
    int found_cnt = 0;
    while (n_tests--)
    {
        char* word = words[get_rand_index(n_words)];
        if (strlen(word) < maxlen)
        {
            if (tbl_find(tbl, word)) ++found_cnt;
        }
        else
        {
            if (lst_find(long_lst, word) != NULL) ++found_cnt;
        }
    }
    return found_cnt;
}