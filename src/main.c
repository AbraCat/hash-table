#include <table.h>
#include <preproc.h>

#include <stdio.h>
#include <string.h>

const int n_words = 7, n_tests = 100;
const char text_path[] = "txt/text.txt", words_path[] = "txt/lines", unique_path[] = "txt/unique";

int main(int argc, const char** argv)
{
    if (argc > 1 && strcmp(argv[1], "-p") == 0)
    {
        if (write_words(text_path, words_path) != 0) return 1;

        int n_unique = 0;
        if (write_unique(words_path, unique_path, &n_unique) != 0) return 1;
        printf("Number of unique words: %d\n", n_unique);
        return 0;
    }

    Table* tbl = tbl_ctr(3);
    if (tbl == NULL) return 1;
    char* words = NULL;
    if (fill_tbl(tbl, unique_path, n_words, &words)) return 1;

    int found_cnt = test_tbl(tbl, n_tests, n_words, words);
    printf("Found %d / %d words\n", found_cnt, n_tests);

    return 0;
}