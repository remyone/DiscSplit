#include "fileAnalysis.h"

uint32_t min(uint32_t a, uint32_t b) {
    if (a < b)
        return a;
    return b;
}

uint32_t calculateFileSize(FILE *file) {
    uint32_t size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    return size;
}

File *getSplitFileSizes(char filename[150]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("fopen failed");
        exit(-1);
    }

    uint32_t MainFileSize = calculateFileSize(file);
    printf("FileSize = %dMB\n", MainFileSize / (1024 * 1024));

    if (MainFileSize <= MaxFileSize) {
        printf(green"Your file is already ready to upload to discord!\n"reset);
        exit(0);
    }

    File *splitFS = (File *) calloc(2, sizeof(File));
    
    if (splitFS == NULL) {
        perror("FileSizes calloc failed");
        exit(-1);
    }

    splitFS[0].capacity = 2;

    uint32_t MinFileSize = 0;

    for (int i = 0; MainFileSize > 0; ++i) {
        MinFileSize = min(MaxFileSize, MainFileSize);

        if (splitFS[0].size == splitFS[0].capacity) {
            splitFS = realloc(splitFS, sizeof(File) * 2);
            
            if (splitFS == NULL) {
                perror("realloc failed");
                exit(-1);
            }

            splitFS[0].capacity += 2;
        }

        splitFS[i].FileSize = MinFileSize;
        MainFileSize -= MinFileSize;
        splitFS[0].size += 1;
    }

    fclose(file);
    return splitFS;
}

char *getFileExtension(char *filename) {
    int start_extension_index = -1; // -1 means no extension was found
    int fileLength = strlen(filename);

    for (int i = 0; i < fileLength; ++i)
        if (filename[i] == '.')
            start_extension_index = i+1;

    char *no_returned_extension = " ";

    if (start_extension_index == -1)
        return no_returned_extension; //no extension was found => it's likely an executable file

    char *fileExtension = (char *) calloc(fileLength - start_extension_index, sizeof(char));

    if (fileExtension == NULL) {
        perror("Memory Allocation Failed");
        exit(-1);
    }

    for (int i = start_extension_index, j = 0; i < fileLength; ++i, j++)
        fileExtension[j] = filename[i];

    return fileExtension;
}