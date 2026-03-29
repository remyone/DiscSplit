#include "mergeFiles.h"

void getFilesSizes(FileArray *FS) {
    FILE *file;
    for (int i = 0; i < FS->size; ++i) {
        file = fopen(FS->files[i].FileName, "r");
        FS->files[i].FileSize = calculateFileSize(file);
        fclose(file);
    }
}

void getFilesName(char *user_input, FileArray *FS) {
    char *token = strtok(user_input, " ");

    while (token != NULL) {
        strcpy(FS->files[FS->size].FileName, token);
        if (FS->size > FS->capacity) {
            FS->files = realloc(FS->files, sizeof(File) * 5);
            FS->capacity += 5;
        }
        FS->size++;
        token = strtok(NULL, " ");
    }
}

FileArray *getFiles(char *user_input) {
    FileArray *FS = (FileArray *) malloc(sizeof(FileArray));
    FS->files = (File *) malloc(sizeof(File) * 5);
    FS->capacity = 5;
    FS->size = 0;

    getFilesName(user_input, FS);
    getFilesSizes(FS);

    for (int i = 0; i < FS->size; ++i)
        printf("%s : [%" PRIu32 "]\n", FS->files[i].FileName, FS->files[i].FileSize);

    return FS;
}

uint8_t checkFilesExtensionDifference(FileArray *FS) {
    char *FileExtension = getFileExtension(FS->files->FileName); // First File's Extension 
    for (int i = 1; i < FS->size; ++i) {
        if (strcmp(FileExtension, getFileExtension(FS->files[i].FileName)) != 0)
            return 1;
    }
    return 0;
}

uint8_t mergeFiles(char *user_input) {
    FileArray *FS = getFiles(user_input);
    char isFilesExtensionDifferent = checkFilesExtensionDifference(FS);

    if (!isFilesExtensionDifferent) {
        char **buffers = allocate_2dBuffer(FS);

        char merged_fileName[20];
        snprintf(merged_fileName, sizeof(merged_fileName), "file.%s", getFileExtension(FS->files->FileName));

        FILE *mergedFile = fopen(merged_fileName, "a");
        FILE *files_for_merging[FS->size];

        for (int i = 0; i < FS->size; ++i)
            files_for_merging[i] = fopen(FS->files[i].FileName, "r");

        for (int i = 0; i < FS[0].size; ++i) {
            if (fread(buffers[i], 1, FS->files[i].FileSize, files_for_merging[i]) < FS->files[i].FileSize) {
                perror("fread error");
                return -1;
            }

            if (fwrite(buffers[i], 1, FS->files[i].FileSize, mergedFile) < FS->files[i].FileSize) {
                perror("fwrite failed");
                return -1;
            }
        }

        for (int i = 0; i < FS->size; ++i)
            fclose(files_for_merging[i]);
        fclose(mergedFile);

        for (int i = 0; i < FS->size; ++i)
            free(buffers[i]);

        free(buffers);
    } else {
        printf(red"You entered files with different extensions -> Files merging cannot be completed\n"reset);
        return -1;
    }
    
    free(FS);
    return 1;
}