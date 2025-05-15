#ifndef TEST_H
#define TEST_H

#include <table.h>

typedef struct Test
{
    Table* tbl;
    char *short_buf, *long_buf;
    char **long_words;
    int n_short, n_long;
} Test;

int get_rand_index(int max_ind);

void divide_words(int n_words, char* txt, char** words);
char* find_word_in_arr(int n_words, char** words, char* word);

int fill_tbl(Test* t, const char* short_path, const char* long_path);
unsigned long long test_tbl(int n_tests, const Test t, int* n_found);
int measure_tbl_time(int n_tests, const Test t);

void test_dtr(Test* t);

#endif // TEST_H