#ifndef FILE_HEADER_H
#define FILE_HEADER_H

#include "book.h"

#define DATASET "dataset.csv"

int loadData(Node **firstNode);
int saveData(Node **firstNode);

#endif