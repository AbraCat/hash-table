#include <preproc.h>
#include <test.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <immintrin.h>

const int n_short = 9423, n_long = 0, n_tests = 1e6;
const char text_path[] = "txt/lord-of-rings.txt", words_path[] = "txt/lines", 
short_path[] = "txt/short", long_path[] = "txt/long";

int main(int argc, const char** argv)
{
    srand(1);

    if (argc > 1 && strcmp(argv[1], "-p") == 0)
    {
        if (write_words(text_path, words_path) != 0) return 1;

        int n_short = -1, n_long = -1;
        if (write_unique(words_path, short_path, long_path, &n_short, &n_long) != 0) return 1;
        printf("Wrote %d short words and %d long words\n", n_short, n_long);
        return 0;
    }

    Test t = {};
    t.n_short = n_short;
    t.n_long = n_long;
    if (fill_tbl(&t, short_path, long_path)) return 1;

    if (argc > 1 && strcmp(argv[1], "-h") == 0)
    {
        printf("Hash dispersion: %lf\n", hash_dispersion(t.tbl));
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "-m") == 0)
    {
        measure_tbl_time(n_tests, t);
        return 0;
    }

    unsigned long long start = _rdtsc();
    int n_found = 0;
    unsigned long long elapsed_time = test_tbl(n_tests, t, &n_found);
    printf("Found %d / %d words (%lld elapsed)\n", n_found, n_tests, elapsed_time);

    test_dtr(&t);
    return 0;
}