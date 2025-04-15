#ifndef PREPROC_H
#define PREPROC_H

#include <table.h>

int write_words(const char* in_path, const char* out_path);
int write_unique(const char* in_path, const char* out_path, int* n_unique);
int fill_tbl(Table* tbl, Node** long_lst, const char* in_path, int n_words, char** txt_buf, char** words);

int get_rand_index(int max_ind);
int test_tbl(Table* tbl, Node* long_lst, int n_tests, int n_words, char** words);

#endif // PREPROC_H