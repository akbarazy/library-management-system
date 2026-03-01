#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "book.h"

Node *linearSearchInt(Node *firstNode, Field field, int integer);
Node *linearSearchStr(Node *firstNode, Field field, const char *string);
Node *linearSearchBool(Node *firstNode, Field field, bool boolean);
int sortOption(Node *a, Node *b, int sortOption1, int sortOption2);
void splitList(Node *source, Node **frontNode, Node **backNode);
Node *sortedMerge(Node *a, Node *b, int sortOption1, int sortOption2);
void mergeSort(Node **headRef, int sortOption1, int sortOption2);

#endif