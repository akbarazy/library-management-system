#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "book.h"

Node *createNode();
void insertNode(Node **firstNode, Node *node);
bool verifyInputInt(char *input, int min, int max);
bool verifyInputStr(char *input);
void trimWhiteSpace(char *input);
int bookCount(Node *firstNode);
bool isNumberStr(const char *input);
int numberStrToInt(const char *input);
bool compareString(const char *input, const char *string);
char charToLower(char character);
void printBook(Node *firstNode, int currentPagination);
void printPagination(int currentPagination, int totalPagination, int *minPagination, int *maxPagination);

// void deskripsiUrutan(int kolom, int arah);
// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
// void hurufKecil(char *stringAsli, char *stringSalinan);
// void hapusSpasi(char *stringAsli);

#endif