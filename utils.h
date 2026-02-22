#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "book.h"

Node *createNode();
void insertNode(Node **firstNode, Node *node);
bool verifyInputInt(char *string, int min, int max);
bool verifyInputStr(char *string);
void trimWhiteSpace(char *string);
int bookCount(Node *firstNode);
bool isNumberStr(const char *string);
int numberStrToInt(const char *string);
bool compareString(const char *string1, const char *string2);
char charToLower(char character);
void printBook(Node *firstNode, int currentPagination);
void printPagination(int currentPagination, int totalPagination, int *minPagination, int *maxPagination);

// void deskripsiUrutan(int kolom, int arah);
// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
// void hurufKecil(char *stringAsli, char *stringSalinan);
// void hapusSpasi(char *stringAsli);

#endif