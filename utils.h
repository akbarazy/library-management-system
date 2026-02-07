#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "book.h"

Node *createNode(
    int id, 
    const char *title, 
    const char *author, 
    int publicationYear, 
    bool available
);
Node *insertNode(Node *firstNode, Node *node);

// void hapusBaris(int jumlahBaris);
// void deskripsiUrutan(int kolom, int arah);
// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
// void hurufKecil(char *stringAsli, char *stringSalinan);
// void hapusSpasi(char *stringAsli);

#endif