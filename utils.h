#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "book.h"

typedef enum {
    FULL,
    PARTIAL
} String;

Node *createNode();
void insertNode(Node **firstNode, Node *node);
void deleteNode(Node **firstNode, int id);
void deleteAllNode(Node **firstNode);
bool verifyInputInt(char *string, int min, int max);
bool verifyInputStr(char *string);
void trimWhiteSpace(char *string);
int bookCount(Node *firstNode);
bool isNumberStr(const char *string);
int numberStrToInt(const char *string);
bool compareString(const char *string1, const char *string2, String type);
char charToLower(char character);
void printBook(Node *node);
void printPagination(Node *firstNode, int *minPagination, int *maxPagination, int currentPagination, int totalPagination);

// void deskripsiUrutan(int kolom, int arah);
// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
// void hurufKecil(char *stringAsli, char *stringSalinan);
// void hapusSpasi(char *stringAsli);

#endif