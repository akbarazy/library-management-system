#ifndef FILE_HEADER_H
#define FILE_HEADER_H

#include <stdbool.h>
#include "book.h"

#define DATASET "dataset.csv"

bool loadData(Node **firstNode);
bool saveData(Node **firstNode);

#endif