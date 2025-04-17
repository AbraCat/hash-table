#include <test.h>
#include <preproc.h>

#include <stdlib.h>
#include <string.h>

const int target_load_factor = 20;

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

int fill_tbl(Test* t, const char* short_path, const char* long_path)
{
    FILE *fshort = fopen(short_path, "r"), *flong = fopen(long_path, "r");
    if (fshort == NULL || flong == NULL) return 1;

    if (readFile(fshort, &t->short_buf) != 0) return 1;
    if (readFile(flong, &t->long_buf) != 0) return 1;

    t->long_words = calloc(sizeof(char*), t->n_long);
    divide_words(t->n_long, t->long_buf, t->long_words);

    t->tbl = tbl_ctr(t->n_short / target_load_factor);
    for (int i = 0; i < t->n_short; ++i)
        tbl_insert(t->tbl, get_word(t->short_buf, i));

    return 0;
}
int __attribute__ ((noinline)) get_rand_index(int max_ind) { return rand() % max_ind; }

char* __attribute__ ((noinline)) find_word(int n_words, char** words, char* word)
{
    for (int i = 0; i < n_words; ++i)
        if (strcmp(words[i], word) == 0) return words[i];
    return NULL;
}

int __attribute__ ((noinline)) test_tbl(int n_tests, Test t)
{
    int found_cnt = 0;
    while (n_tests--)
    {
        int ind = get_rand_index(t.n_short + t.n_long);
        char* word = NULL;
        if (ind < t.n_short)
        {
            word = get_word(t.short_buf, ind);
            if (tbl_find(t.tbl, word)) ++found_cnt;
        }
        else
        {
            word = t.long_words[ind - t.n_short];
            if (find_word(t.n_long, t.long_words, word) != NULL) ++found_cnt;
        }
    }
    return found_cnt;
}

void test_dtr(Test* t)
{
    tbl_dtr(t->tbl);
    free(t->short_buf);
    free(t->long_buf);
    free(t->long_words);
}