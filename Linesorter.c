#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define SHORT_LINE_THRESHOLD 20

void convertToUpperCase(char *line) {
    for(int i = 0; line[i]; i++) {
        line[i] = toupper(line[i]);
    }
}

void convertToLowerCase(char *line) {
    for(int i = 0; line[i]; i++) {
        line[i] = tolower(line[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source_file> <short_lines_file> <long_lines_file>\n", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    FILE *shortFile = fopen(argv[2], "w");
    FILE *longFile = fopen(argv[3], "w");

    if (!source || !shortFile || !longFile) {
        printf("Error opening files\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int shortLines = 0, longLines = 0;

    while (fgets(line, sizeof(line), source)) {
        // Remove newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
            len--;
        }

        if (len < SHORT_LINE_THRESHOLD) {
            convertToUpperCase(line);
            fprintf(shortFile, "%s\n", line);
            shortLines++;
        } else {
            convertToLowerCase(line);
            fprintf(longFile, "%s\n", line);
            longLines++;
        }
    }

    fclose(source);
    fclose(shortFile);
    fclose(longFile);

    printf("%d lines written to %s\n", shortLines, argv[2]);
    printf("%d lines written to %s\n", longLines, argv[3]);

    return 0;
}
