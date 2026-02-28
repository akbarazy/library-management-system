#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "book.h"

Node *linearSearchInt(Node *firstNode, Field field, int integer);
Node *linearSearchStr(Node *firstNode, Field field, const char *string);
Node *linearSearchBool(Node *firstNode, Field field, bool boolean)
// int partition(int indexPertama, int indexTerakhir, int kolom, int arah);
// void quickSort(int indexPertama, int indexTerakhir, int kolom, int arah);

#endif