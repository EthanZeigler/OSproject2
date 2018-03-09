#include <stdio.h>
#ifndef PROJECT2_CSVPARSER_H
#define PROJECT2_CSVPARSER_H
#define MAX_LINE_SIZE 300
#define MAX_NUM_OF_CELLS 50

#endif //PROJECT2_CSVPARSER_H

typedef struct CSVCell {
    char* data;
    int isEmpty;
    int isNumeric;
    int isAlphanumeric;
};

typedef struct CSVLine {
    struct CSVCell* line;
    int len;
};

typedef struct CSVFile {
    struct CSVLine* lines;
    int len;
};

struct CSVFile *readFile(FILE *file);

struct CSVCell * getCell(char* token);

struct CSVLine * readLine(FILE* file);
