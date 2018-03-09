#include <libnet.h>
#include <stdbool.h>
#include "csvparser.h"


struct CSVFile *readFile(FILE *file) {
    struct CSVLine* lines = malloc(sizeof(struct CSVLine) * 1500);
    int i = 0;
    while (1) {
        lines[i] = *readLine(file);
        if (lines[i].len == 0) {
            break;
        }
        i++;
    }

    struct CSVFile* csvFile = malloc(sizeof(struct CSVFile));
    csvFile->len = i;
    csvFile->lines = lines;

    return csvFile;
}

struct CSVLine* readLine(FILE* file) {
    size_t size = MAX_LINE_SIZE;
    struct CSVCell* lineData = malloc(sizeof(struct CSVCell) * MAX_NUM_OF_CELLS);
    char* nextLine = malloc(sizeof(char) * MAX_LINE_SIZE);
    struct CSVLine* line = malloc(sizeof(struct CSVLine));
    getline(&nextLine, &size, file);

    int i = 0;

    char* token = strtok(nextLine, ",");
    struct CSVCell* cell = getCell(token);
    if (!cell) {
        line->len = 0;
        line->line = lineData;

        free(nextLine);
        return line;
    } else {
        lineData[i] = *cell;
    }

    for (i = 1; token; ++i) {
        token = strtok(NULL, ",");
        cell = getCell(token);
        if (!cell) {
            break;
        }
        lineData[i] = *cell;
    }
    line->line = lineData;
    line->len = i;

    //free(nextLine);
    return line;
}

struct CSVCell* getCell(char* token) {
    struct CSVCell* newCell = malloc(sizeof(struct CSVCell));

    if (token == NULL) {
        return NULL;
    } else if (isnumber(token)) {
        newCell->data = strdup(token);
        newCell->isNumeric = true;
        newCell->isAlphanumeric = false;
        newCell->isEmpty = false;
    } else if (strlen(token) > 0) {
        newCell->data = strdup(token);
        newCell->isNumeric = false;
        newCell->isAlphanumeric = true;
        newCell->isEmpty = false;
    } else {
        newCell->data = strdup(token);
        newCell->isNumeric = false;
        newCell->isAlphanumeric = false;
        newCell->isEmpty = true;
    }

    return newCell;
}