#include "splitFileContent.h"

char **allocate_2dBuffer(File *splitFS) {
   char **buffer = (char **) calloc(splitFS[0].size, sizeof(char *));

    if (buffer == NULL) {
        perror("2d buffer calloc failed");
        exit(-1);
    }

    for (int i = 0; i < splitFS[0].size; ++i) {
        buffer[i] = (char *) calloc(1, sizeof(char) * splitFS[i].FileSize);
        if (buffer[i] == NULL) {
            perror("2d buffer calloc failed");
            exit(-1);
        }
    }
    return buffer;
}

void splitFileContent(FILE *files[], File *splitFS,char *splitFileName) {
    FILE *splitFile = fopen(splitFileName, "r");

    if (splitFile == NULL) {
        perror("fopen failed");
        exit(-1);
    }

    uint32_t splitFileSize = calculateFileSize(splitFile), bytes_read;
    char **buffer = allocate_2dBuffer(splitFS);

    for (int i = 0; i < splitFS[0].size; ++i) {
        bytes_read = fread(buffer[i], 1, splitFS[i].FileSize, splitFile);
        
        if (bytes_read < splitFS[i].FileSize) {
            perror("fread error");
            exit(-1);
        }

        if (fwrite(buffer[i], 1, bytes_read, files[i]) < bytes_read) {
            perror("fwrite failed");
            exit(-1);
        }

        fseek(splitFile, splitFS[i].FileSize, SEEK_SET);
    }

    for (int i = 0; i < splitFS[0].size; ++i)
        free(buffer[i]);

    fclose(splitFile);
}

void separateFile(char *filename) {
    File *splitFS = getSplitFileSizes(filename);

    for (int i = 0; i < splitFS[0].size; ++i) {
        printf("{%" PRIu32 "}\n", splitFS[i].FileSize);
    }

    FILE *splited_files[splitFS[0].size];

    char concated_filename[20];
    char *fileExtension = getFileExtension(filename);

    if (strcmp(fileExtension, " ") == 0) {
        for (int i = 0; i < splitFS[0].size; ++i) {
            snprintf(concated_filename, sizeof(concated_filename), "file%d", i, fileExtension);
            splited_files[i] = fopen(concated_filename, "w");
        }
    } else {
        for (int i = 0; i < splitFS[0].size; ++i) {
            snprintf(concated_filename, sizeof(concated_filename), "file%d.%s", i, fileExtension);
            splited_files[i] = fopen(concated_filename, "w");
        }

        free(fileExtension);
    }

    splitFileContent(splited_files, splitFS, filename);

    for (int i = 0; i < splitFS[0].size; ++i)
        fclose(splited_files[i]);

    free(splitFS);
}