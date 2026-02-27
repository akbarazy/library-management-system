#include <stdio.h>
#include "algorithm.h"
#include "book.h"
#include "utils.h"

Node *linearSearchInt(Node *firstNode, Field field, int integer) {
    Node *firstNodeTemp = NULL;

    while (firstNode != NULL) {
        if (field == ID && firstNode->book.id == integer) {
            Node *node = createNode();
            if (node == NULL) return NULL;
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        } else if (field == YEAR && firstNode->book.year == integer) {
            Node *node = createNode();
            if (node == NULL) return NULL;
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        }

        firstNode = firstNode->next;
    }
    
    return firstNodeTemp;
}

Node *linearSearchStr(Node *firstNode, Field field, const char *string) {
    Node *firstNodeTemp = NULL;

    while (firstNode) {
        if (field == TITLE && compareString(firstNode->book.title, string)) {
            Node *node = createNode();
            if (node == NULL) return NULL;
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        } else if (field == TITLE && compareString(firstNode->book.title, string)) {
            Node *node = createNode();
            if (node == NULL) return NULL;
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        }

        firstNode = firstNode->next;
    }

    return firstNodeTemp;
}

// int partition(int indexPertama, int indexTerakhir, int kolom, int arah)
// {
//     Barang pivot = semuaBarang[indexTerakhir];
//     int indexTukar = indexPertama - 1;

//     for (int i = indexPertama; i < indexTerakhir; i++)
//     {
//         if (kondisiUrutan(semuaBarang[i], pivot, kolom, arah))
//         {
//             indexTukar++;

//             Barang cadangan = semuaBarang[indexTukar];
//             semuaBarang[indexTukar] = semuaBarang[i];
//             semuaBarang[i] = cadangan;
//         }
//     }

//     Barang cadangan = semuaBarang[indexTukar + 1];
//     semuaBarang[indexTukar + 1] = semuaBarang[indexTerakhir];
//     semuaBarang[indexTerakhir] = cadangan;

//     return indexTukar + 1;
// }

// void quickSort(int indexPertama, int indexTerakhir, int kolom, int arah)
// {
//     if (indexPertama < indexTerakhir)
//     {
//         int indexPivot = partition(indexPertama, indexTerakhir, kolom, arah);

//         quickSort(indexPertama, indexPivot - 1, kolom, arah);
//         quickSort(indexPivot + 1, indexTerakhir, kolom, arah);
//     }
// }