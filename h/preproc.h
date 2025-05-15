#ifndef PREPROC_H
#define PREPROC_H

#include <table.h>

long fileSize(FILE *file);
int readFile(FILE* file, char** bufptr);

int write_words_to_file(const char* in_path, const char* out_path);
int write_unique_words(const char* in_path, const char* short_path, const char* long_path, int* n_short, int* n_long);

char* get_word_in_arr(char* words, int ind);

#endif // PREPROC_H