#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: parser <file>\n");

        exit(EXIT_FAILURE);
    }

    /* Open file */
    char* input_file = argv[1];
    FILE* inputfp = fopen(input_file, "r");

    /* Declare getline pointers */
    char* cur_line = NULL;
    size_t linecap = 0;
    ssize_t read;

    /* Helper flag to mark leading tokens */
    char is_leading_token = 1;

    /* Read lines from file stream */
    while ((read = getline(&cur_line, &linecap, inputfp)) != -1) {
        char* line = strdup(cur_line);

        char* token = NULL;
        while ((token = strsep(&line, " \t"))) {
            /* If the leading token is a comment, do not parse it */
            if (is_leading_token && !strcmp(token, "#")) {
                /* TODO: Detect empty lines */
                printf("Comment found\n");
                break;
            }

            /* Unset the leading token flag after getting the first token */
            is_leading_token = 0;

            /* Send this token to the parser */
            printf("%s", token); // TODO: Replace this with a parsing function
        }

        /* When finished with a line, reset the leading token flag */
        is_leading_token = 1;
    }

    /* Cleanup */
    fclose(inputfp);
    free(cur_line);

    exit(EXIT_SUCCESS);
}

