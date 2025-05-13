#include <utils.h>

#include <immintrin.h>

int round_up(int n, int alignment) { return n % alignment == 0 ? n : alignment * (n / alignment + 1); }

int strcmp_attributes mystrcmp(const char* lft, const char* rgt)
{
    __m256i xor_res = _mm256_xor_si256(_mm256_load_si256(lft), _mm256_load_si256(rgt));
    return !_mm256_testz_si256(xor_res, xor_res);
}

void dispersion(unsigned long long* a, int n, double* disp, double* expect)
{
    double sum = 0, sum_of_sq = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += a[i];
        sum_of_sq += a[i] * a[i];
    }
    double _expect = sum / n;
    if (expect != NULL) *expect = _expect;
    *disp = sum_of_sq / n - _expect * _expect;
}