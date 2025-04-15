#include <table.h>
#include <preproc.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int n_words = 258, n_tests = 1000, target_load_factor = 20;
const char text_path[] = "txt/text.txt", words_path[] = "txt/lines", unique_path[] = "txt/unique";

int main(int argc, const char** argv)
{
    srand(1);

    if (argc > 1 && strcmp(argv[1], "-p") == 0)
    {
        if (write_words(text_path, words_path) != 0) return 1;

        int n_unique = 0;
        if (write_unique(words_path, unique_path, &n_unique) != 0) return 1;
        printf("Wrote %d unique words\n", n_unique);
        return 0;
    }

    Table* tbl = tbl_ctr(n_words / target_load_factor);
    if (tbl == NULL) return 1;

    Node* long_lst = NULL;
    char* txt_buf = NULL;
    char** words = (char**)calloc(sizeof(char*), n_words);
    if (fill_tbl(tbl, &long_lst, unique_path, n_words, &txt_buf, words)) return 1;
    // tbl_dump(tbl, stdout);

    int found_cnt = test_tbl(tbl, long_lst, n_tests, n_words, words);
    printf("Found %d / %d words\n", found_cnt, n_tests);

    tbl_dtr(tbl);
    node_dtr(long_lst);
    free(words);
    free(txt_buf);
    return 0;
}