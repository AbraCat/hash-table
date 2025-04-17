#ifndef PREPROC_H
#define PREPROC_H

#include <table.h>

long fileSize(FILE *file);
int readFile(FILE* file, char** bufptr);

int write_words(const char* in_path, const char* out_path);
int write_unique(const char* in_path, const char* short_path, const char* long_path, int* n_short, int* n_long);

char* get_word(char* words, int ind);

#endif // PREPROC_H