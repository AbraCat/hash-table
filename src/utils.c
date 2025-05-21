#include <utils.h>

#include <immintrin.h>

int round_up(int n, int alignment) { return n % alignment == 0 ? n : alignment * (n / alignment + 1); }

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

void relation_err(double x, double x_err, double y, double y_err, double* result, double* result_err)
{
    double x_rel = x_err / x, y_rel = y_err / y;
    double res = *result = x / y;
    double res_rel = x_rel + y_rel;
    *result_err = res * res_rel;
}