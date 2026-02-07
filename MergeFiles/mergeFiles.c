#include "mergeFiles.h"

void getFilesSizes(File *FS) {
    FILE *file;
    for (int i = 0; i < FS[0].size; ++i) {
        file = fopen(FS[i].FileName, "r");
        FS[i].FileSize = calculateFileSize(file);
        fclose(file);
    }
}

void getFilesName(char *user_input, File *FS) {
    char *token = strtok(user_input, " ");

    while (token != NULL) {
        strcpy(FS[FS[0].size].FileName, token);
        FS[0].size++;
        token = strtok(NULL, " ");
    }

    getFilesSizes(FS);
}

File *getFiles(char *user_input) {
    File *FS = (File *) calloc(5, sizeof(File));
    FS[0].capacity = 5;
    FS[0].size = 0;

    getFilesName(user_input, FS);

    getFilesSizes(FS);

    for (int i = 0; i < FS[0].size; ++i)
        printf("%s : [%" PRIu32 "]\n", FS[i].FileName, FS[i].FileSize);

    return FS;
}

uint8_t checkFilesExtensionDifference(File *FS) {
    char *FileExtension = getFileExtension(FS[0].FileName); // First File's Extension 
    for (int i = 1; i < FS[0].size; ++i) {
        if (strcmp(FileExtension, getFileExtension(FS[i].FileName)) != 0)
            return 1;
    }
    return 0;
}

uint8_t mergeFiles(char *user_input) {
    File *FS = getFiles(user_input);

    char isFilesExtensionDifferent = checkFilesExtensionDifference(FS);

    if (!isFilesExtensionDifferent) {
        char **buffers = allocate_2dBuffer(FS);

        char merged_fileName[20];
        snprintf(merged_fileName, sizeof(merged_fileName), "file.%s", getFileExtension(FS[0].FileName));

        FILE *mergedFile = fopen(merged_fileName, "a");
        FILE *files_for_merging[FS[0].size];

        for (int i = 0; i < FS[0].size; ++i)
            files_for_merging[i] = fopen(FS[i].FileName, "r");

        for (int i = 0; i < FS[0].size; ++i) {
            if (fread(buffers[i], 1, FS[i].FileSize, files_for_merging[i]) < FS[i].FileSize) {
                perror("fread error");
                return -1;
            }

            if (fwrite(buffers[i], 1, FS[i].FileSize, mergedFile) < FS[i].FileSize) {
                perror("fwrite failed");
                return -1;
            }
        }

        for (int i = 0; i < FS[0].size; ++i)
            fclose(files_for_merging[i]);
        fclose(mergedFile);

        for (int i = 0; i < FS[0].size; ++i)
            free(buffers[i]);

        free(buffers);
    } else {
        printf(red"You entered files with different extensions -> Files merging cannot be completed\n"reset);
        return -1;
    }
    
    free(FS);
    return 1;
}