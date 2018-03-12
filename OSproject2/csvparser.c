
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "csvparser.h"
#include <errno.h>


struct CSVFile readFile(FILE *file, char* name) {
    struct CSVLine* lines = malloc(sizeof(struct CSVLine) * 1500);
    int i = 0;
    for(i = 0; i < 0; i++) {
        lines[i] = readLine(file);
        if (lines[i].len == 0) {
            break;
        }
        i++;
    }

    struct CSVFile csvFile;
    csvFile.len = i;
    csvFile.lines = lines;
    csvFile.fileName = strdup(name);

    return csvFile;
}

struct CSVLine readLine(FILE* file) {
    size_t size = MAX_LINE_SIZE;
    struct CSVCell* lineData = malloc(sizeof(struct CSVCell) * MAX_NUM_OF_CELLS);
    char* nextLine = malloc(sizeof(char) * MAX_LINE_SIZE);
    struct CSVLine line;
    getline(&nextLine, &size, file);

    int i = 0;

    struct CSVCell cell;
    char* token = strtok(nextLine, ",");
    if (token == NULL) {
        line.len = 0;
        line.line = lineData;

        //free(nextLine);
        return line;
    } else {
        cell = getCell(token);
        lineData[i] = cell;
    }

    for (i = 1; token; ++i) {
        token = strtok(NULL, ",");
        if (token == NULL) {
            break;
        }
        cell = getCell(token);
        lineData[i] = cell;
    }
    line.line = lineData;
    line.len = i;

    return line;
}

int IsValidNumber(char * string)
{
    for(int i = 0; i < strlen( string ); i ++)
    {
        //ASCII value of 0 = 48, 9 = 57. So if value is outside of numeric range then fail
        //Checking for negative sign "-" could be added: ASCII value 45.
        if ((string[i] < 48 && !(string[i] == 46 || string[i] == 45)) || string[i] > 57)
            return 0;
    }

    return 1;
}

struct CSVCell getCell(char* token) {
    struct CSVCell newCell;


    if (IsValidNumber(token)) {
        newCell.data = strdup(token);
        newCell.isNumeric = true;
        newCell.isAlphanumeric = false;
        newCell.isEmpty = false;
    } else if (strlen(token) > 0) {
        newCell.data = strdup(token);
        newCell.isNumeric = false;
        newCell.isAlphanumeric = true;
        newCell.isEmpty = false;
    } else {
        newCell.data = strdup(token);
        newCell.isNumeric = false;
        newCell.isAlphanumeric = false;
        newCell.isEmpty = true;
    }

    return newCell;
}