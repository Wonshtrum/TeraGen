#ifndef __FILE_H__
#define __FILE_H__

#include "core.h"
#include "decompress.h"

const char* readFile(const char* name);

const char* readFile(const char* name, int* size);

void writeFile(const char* name, char* buffer, int size);

char* readImage(const char* name, unsigned int* width_, unsigned int* height_, unsigned int* channels_);


#endif