#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <iostream>
#include "decompress.h"

const char* readFile(const char* name);

char* readImage(const char* name, unsigned int* width_, unsigned int* height_, unsigned int* channels_);


#endif