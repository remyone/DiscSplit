#ifndef SPLITFILECONTENT_H
#define SPLITFILECONTENT_H

#include "fileAnalysis.h"
#include <inttypes.h>
#include <time.h>

extern char **allocate_2dBuffer(FileArray *splitFS);
extern void splitFileContent(FILE *files[], FileArray *splitFS,char *splitFileName);
extern void separateFile(char filename[]);

#endif