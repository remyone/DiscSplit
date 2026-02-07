#ifndef MERGE_FILES_H
#define MERGE_FILES_H

#include "splitFileContent.h"

extern void getFilesSizes(File *FS);
extern void getFilesName(char *user_input, File *FS);
extern File *getFiles(char *user_input);
extern uint8_t checkFilesExtensionDifference(File *FS);
extern uint8_t mergeFiles(char *user_input);

#endif