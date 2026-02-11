#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "book.h"

Node *createNode();
void insertNode(Node **firstNode, Node *node);
bool verifyInputInt(int input, int min, int max);
bool verifyInputStr(const char *input);
void deleteLines(int lineCount);
void deleteWhiteSpace(char *input);
int countBooks(Node *firstNode);

// void deskripsiUrutan(int kolom, int arah);
// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
// void hurufKecil(char *stringAsli, char *stringSalinan);
// void hapusSpasi(char *stringAsli);

#endif