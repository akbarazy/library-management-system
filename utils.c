#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "utils.h"

Node *createNode()
{
    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;

    node->next = NULL;
    node->prev = NULL;

    return node;
}

void insertNode(Node **firstNode, Node *node)
{
    Node *currentNode;

    if (!*firstNode) {
        *firstNode = node;
        return;
    }

    currentNode = *firstNode;
    while (currentNode->next) 
        currentNode = currentNode->next;

    currentNode->next = node;
    node->prev = currentNode;
}

// void hapusBaris(int jumlahBaris)
// {
//     for (int i = 0; i < jumlahBaris; i++)
//         printf("\033[A\033[2K");
// }

// void deskripsiUrutan(int kolom, int arah)
// {
//     switch (kolom)
//     {
//     case 1:
//         arah % 2 ? 
//             strcpy(statusTabel[1], "Dari Id Terbesar.") : 
//             strcpy(statusTabel[1], "Dari Id Terkecil.");
//         break;
//     case 2:
//         arah % 2 ? 
//             strcpy(statusTabel[1], "Dari Nama Terbesar.") : 
//             strcpy(statusTabel[1], "Dari Nama Terkecil.");
//         break;
//     case 3:
//         arah % 2 ? 
//             strcpy(statusTabel[1], "Dari Stok Terbesar.") : 
//             strcpy(statusTabel[1], "Dari Stok Terkecil.");
//         break;
//     case 4:
//         arah % 2 ? 
//             strcpy(statusTabel[1], "Dari Harga Terbesar.") : 
//             strcpy(statusTabel[1], "Dari Harga Terkecil.");
//         break;
//     }
// }

// int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah)
// {
//     switch (kolom)
//     {
//     case 1:
//         return arah % 2 ? 
//             barang.id > pivot.id : barang.id < pivot.id;
//     case 2:
//         return arah % 2 ? 
//             strcmp(barang.nama, pivot.nama) > 0 : strcmp(barang.nama, pivot.nama) < 0;
//     case 3:
//         return arah % 2 ? 
//             barang.stok > pivot.stok : barang.stok < pivot.stok;
//     case 4:
//         return arah % 2 ? 
//             barang.harga > pivot.harga : barang.harga < pivot.harga;
//     }
// }

// void hurufKecil(char *stringAsli, char *stringSalinan)
// {
//     stringSalinan[0] = '\0';

//     for (int i = 0; i < 255; i++)
//     {
//         if (stringAsli[i] == '\0')
//         {
//             stringSalinan[i] = '\0';
//             break;
//         }
//         stringSalinan[i] = tolower(stringAsli[i]);
//     }
// }

// void hapusSpasi(char *stringAsli)
// {
//     int indexPertama = 0;
//     int indexTerakhir = strlen(stringAsli) - 1;

//     while (isspace((unsigned char)stringAsli[indexPertama])) {
//         indexPertama++;
//     }

//     while (indexTerakhir >= indexPertama && isspace((unsigned char)stringAsli[indexTerakhir])) {
//         indexTerakhir--;
//     }

//     int i = 0;
//     while (indexPertama <= indexTerakhir) {
//         stringAsli[i++] = stringAsli[indexPertama++];
//     }

//     stringAsli[i] = '\0';
// }