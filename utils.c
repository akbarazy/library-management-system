#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "book.h"
#include "utils.h"

Node *createNode() {
    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;

    node->next = NULL;
    node->prev = NULL;

    return node;
}

void insertNode(Node **firstNode, Node *node) {
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

Node *getLastNode(Node *firstNode) {
    if (!firstNode) return NULL;

    while (firstNode->next != NULL) 
        firstNode = firstNode->next;
        
    return firstNode;
}

bool verifyInputInt(char *input, int min, int max) {
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
            (unsigned char)input[index] > 126 ||
            input[index] == '\\')
            return false;
        index++;
    }

    return index > 0;
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

int bookCount(Node *firstNode) {
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

bool compareString(const char *input, const char *string) {
    while (*input && *string) {
        if (charToLower(*input) != charToLower(*string)) 
            return false;
            
        input++; 
        string++;
    }

    return *input == '\0' && *string == '\0';
}

char charToLower(char character) {
    if (character >= 'A' && character <= 'Z') {
        return character - 'A' + 'a';
    }
    return character;
}

void printBook(Node *firstNode, int currentPagination) {
    Node *currentNode = firstNode;
    int startIndex = (currentPagination - 1) * 5,
        endIndex = startIndex + 4,
        index = 0;

    while (currentNode) {
        if (index >= startIndex && index <= endIndex) {
            printf("%d. %s\n", currentNode->book.id, currentNode->book.title);
            printf("Author    : %s\n", currentNode->book.author);
            printf("Year      : %d\n", currentNode->book.year);
            printf("Available : %s\n\n", currentNode->book.available ? "True" : "False");
        }

        currentNode = currentNode->next;
        index++;
    }
}

void printPagination(int currentPagination, int totalPagination, int *minPagination, int *maxPagination) {
    if (totalPagination <= 5) {
        *minPagination = 1;
        *maxPagination = totalPagination;
    } else {
        *minPagination = currentPagination - 2;
        *maxPagination = currentPagination + 2;

        if (*minPagination < 1) {
            *minPagination = 1;
            *maxPagination = 5;
        }

        if (*maxPagination > totalPagination) {
            *maxPagination = totalPagination;
            *minPagination = totalPagination - 4;
        }
    }

    if (*minPagination > 1) printf("<< ");

    for (int i = *minPagination; i <= *maxPagination; i++) {
        if (i == currentPagination)
            printf("[%d] ", i);
        else
            printf("%d ", i);
    }

    if (*maxPagination < totalPagination) printf(">> ");
    printf("\n");
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