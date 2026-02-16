#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "book.h"

Node *createNode();
void insertNode(Node **firstNode, Node *node);
bool verifyInputInt(char *input, int min, int max);
bool verifyInputStr(char *input);
void deleteLines(int lineCount);
void trimWhiteSpace(char *input);
int bookCount(Node *firstNode);
bool isNumberStr(const char *input);
int numberStrToInt(const char *input);

// void deskripsiUrutan(int kolom, int arah);
// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
// void hurufKecil(char *stringAsli, char *stringSalinan);
// void hapusSpasi(char *stringAsli);

#endif