#include "AsciiArtTool.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

RLEList asciiArtRead(FILE* in_stream) {
    RLEList newRLE = RLEListCreate();
    if (!newRLE) {
        fprintf(stderr, "memory allocation error");
        return NULL;
    }
    assert(newRLE);
    char buffer;
    do {
        buffer = fgetc(in_stream);
        RLEListResult  appendingResult = RLEListAppend(newRLE, buffer);
        if(appendingResult != RLE_LIST_SUCCESS) {
            printf("error in appending the char to a new list\n");
        }
        assert(appendingResult == RLE_LIST_SUCCESS);
    } while(buffer != EOF);
    return newRLE;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    RLEListResult result;
    for (int i = 0; i < listSize; i++) {
        char symbol = RLEListGet(list, i, &result);
        if (symbol == 0) {
            return result;
        }
        fprintf(out_stream, "%c", symbol);
    }
    return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char* encodedList = RLEListExportToString(list, &result);
    fprintf(out_stream, "%s", encodedList);
    free(encodedList);
    return result;
}