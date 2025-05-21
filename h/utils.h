#ifndef UTILS_H
#define UTILS_H

#include <immintrin.h>

#define maxlen 32
#define align 32
#define unroll_coeff 4

#define TBL_USE_UNR
#define OPT_STRCMP
#define OPT_HASH_FN
// #define OPT_LIST_FIND

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
void dispersion(unsigned long long* a, int n, double* disp, double* expect);
void relation_err(double x, double x_err, double y, double y_err, double* result, double* result_err);

inline int mystrcmp(const char* lft, const char* rgt)
{
    __m256i xor_res = _mm256_xor_si256(_mm256_load_si256((const __m256i*)lft), _mm256_load_si256((const __m256i*)rgt));
    return !_mm256_testz_si256(xor_res, xor_res);
}

#endif // UTILS_H