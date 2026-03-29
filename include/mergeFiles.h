#ifndef MERGE_FILES_H
#define MERGE_FILES_H

#include "splitFileContent.h"

extern void getFilesSizes(FileArray *FS);
extern void getFilesName(char *user_input, FileArray *FS);
extern FileArray *getFiles(char *user_input);
extern uint8_t checkFilesExtensionDifference(FileArray *FS);
extern uint8_t mergeFiles(char *user_input);

#endif