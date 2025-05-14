#ifndef UTILS_H
#define UTILS_H

#define maxlen 32
#define align 32
#define unroll_coeff 4

#define TBL_USE_UNR
#define OPT_STRCMP
#define OPT_HASH_FN
#define OPT_LIST_FIND

#ifdef TBL_USE_UNR
    #define TblNode UnrNode
    #define list_dtr unr_dtr
    #define list_insert unr_insert
    #ifdef OPT_LIST_FIND
        #define list_find my_unr_find
    #else
        #define list_find unr_find
    #endif // OPT_LIST_FIND
    #define list_n_keys unr_n_keys
    #define list_dump unr_dump
#else
    #define TblNode Node
    #define list_dtr node_dtr
    #define list_insert lst_insert
    #ifdef OPT_LIST_FIND
        #define list_find my_lst_find
    #else
        #define list_find lst_find
    #endif // OPT_LIST_FIND
    #define list_n_keys lst_n_keys
    #define list_dump lst_dump
#endif // TBL_USE_UNR

#ifdef OPT_STRCMP
#define tbl_strcmp mystrcmp
#else
#define tbl_strcmp strcmp
#endif // OPT_STRCMP

#ifdef OPT_HASH_FN
#define tbl_hash_fn my_hash_fn
#else
#define tbl_hash_fn hash_fn
#endif // OPT_STRCMP

int round_up(int n, int alignment);
int mystrcmp(const char* lft, const char* rgt);
void dispersion(unsigned long long* a, int n, double* disp, double* expect);

#endif // UTILS_H