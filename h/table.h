#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

#include <utils.h>
#include <list.h>
#include <unrolled_list.h>

typedef struct Table Table;

typedef struct Table
{
    TblNode** data;
    int n;
} Table;

int my_hash_fn(const char* s, int mod);
int hash_fn(const char* s, int mod);

Table* tbl_ctr(int n);
void tbl_dtr(Table* tbl);
void tbl_insert(Table* tbl, char* s);
int tbl_find(Table* tbl, char* s);

double hash_dispersion(Table* tbl);
void tbl_dump(Table* tbl, FILE* file);

#endif // TABLE_H