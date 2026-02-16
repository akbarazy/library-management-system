#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

bool verifyInputInt(char *input, int min, int max)
{
    int number;

    if (!input || input[0] == '\0') return false;
    trimWhiteSpace(input);

    if (!isNumberStr(input)) return false;
    number = numberStrToInt(input);
    
    if (number < min || number > max)
        return false;
    return true;
}

bool verifyInputStr(char *input) {
    int index = 0;

    if (!input || input[0] == '\0') return false;
    trimWhiteSpace(input);

    while (input[index] != '\0') {
        if ((unsigned char)input[index] < 32 || 
            (unsigned char)input[index] > 126)
            return false;
        index++;
    }

    return index > 0;
}

void deleteLines(int lineCount)
{
    for (int i = 0; i < lineCount; i++)
        printf("\033[A\033[2K");
}

void trimWhiteSpace(char *input) {
    int firstChar = -1, lastChar = -1, index = 0;

    while (input[index] != '\0') {
        if (input[index] != ' ' && input[index] != '\t') {
            if (firstChar != -1) {
                lastChar = index;
            } else {
                firstChar = index;
                lastChar = index;
            }
        }
        index++;
    }

    if (firstChar == -1 && lastChar == -1) {
        input[0] = '\0';
    } else {
        memmove(input, input + firstChar, lastChar - firstChar + 1);
        input[lastChar - firstChar + 1] = '\0';
    }
}

int bookCount(Node *firstNode)
{
    int count = 0;
    Node *currentNode = firstNode;

    while (currentNode) {
        count++;
        currentNode = currentNode->next;
    }

    return count;
}

bool isNumberStr(const char *input) {
    while (*input) {
        if (*input < '0' || *input > '9') return false;
        input++;
    }

    return true;
}

int numberStrToInt(const char *input) {
    int number = 0;

    while (*input) {
        number = number * 10 + (*input - '0');
        input++;
    }

    return number;
}

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