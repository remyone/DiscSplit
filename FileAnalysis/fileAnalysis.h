#ifndef FileAnalysis_H
#define  FileAnalysis_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MaxFileSize 0x989680 //10mb

#define reset "\x1b[0m"
#define red "\x1b[31m"
#define green "\x1b[32m"
#define blue "\x1b[94m"

typedef struct {
    char FileName[50];
    uint32_t FileSize;
    size_t capacity;
    size_t size;
} File;

extern uint32_t min(uint32_t a, uint32_t b);
extern uint32_t calculateFileSize(FILE *file);
extern File *getSplitFileSizes(char filename[150]);
extern char *getFileExtension(char *filename);

#endif