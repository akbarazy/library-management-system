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
    Node *currentNode = *firstNode;

    if (!*firstNode) {
        *firstNode = node;
        return;
    }

    while (currentNode->next) 
        currentNode = currentNode->next;

    currentNode->next = node;
    node->prev = currentNode;
}

void deleteNode(Node **firstNode, int id) {
    Node *currentNode = *firstNode;

    while (currentNode != NULL && currentNode->book.id != id)
        currentNode = currentNode->next;

    if (currentNode == NULL) return;

    if (currentNode->prev == NULL) {
        *firstNode = currentNode->next;
        if (*firstNode != NULL) (*firstNode)->prev = NULL;
    } else {
        currentNode->prev->next = currentNode->next;

        if (currentNode->next != NULL)
            currentNode->next->prev = currentNode->prev;
    }

    free(currentNode);
}

void deleteAllNode(Node **firstNode) {
    Node *currentNode = *firstNode;
    Node *temp;

    while (currentNode != NULL) {
        temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }

    *firstNode = NULL;
}

bool verifyInputInt(char *string, int min, int max) {
    int number;

    if (!string || string[0] == '\0') return false;
    trimWhiteSpace(string);

    if (!isNumberStr(string)) return false;
    number = numberStrToInt(string);
    
    if (number < min || number > max)
        return false;
    return true;
}

bool verifyInputStr(char *string) {
    int index = 0;

    if (!string || string[0] == '\0') return false;
    trimWhiteSpace(string);

    while (string[index] != '\0') {
        if ((unsigned char)string[index] < 32 || 
            (unsigned char)string[index] > 126 ||
            string[index] == '\\')
            return false;
        index++;
    }

    return index > 0;
}

void trimWhiteSpace(char *string) {
    int read = 0, write = 0;
    int firstChar = -1, lastChar = -1;

    while (string[read] != '\0') {
        if (
            string[read] != '\t' &&
            string[read] != '\n' &&
            string[read] != '\r' &&
            string[read] != '\f' &&
            string[read] != '\v'
        ) {
            string[write++] = string[read];
        }
        read++;
    }
    string[write] = '\0';

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] != ' ') {
            if (firstChar == -1) firstChar = i;
            lastChar = i;
        }
    }

    if (firstChar == -1) {
        string[0] = '\0';
        return;
    }

    memmove(string, string + firstChar, lastChar - firstChar + 1);
    string[lastChar - firstChar + 1] = '\0';

    read = 0;
    write = 0;
    while (string[read] != '\0') {
        if (!(string[read] == ' ' && read > 0 && string[read - 1] == ' ')) {
            string[write++] = string[read];
        }
        read++;
    }
    string[write] = '\0';
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

bool isNumberStr(const char *string) {
    while (*string) {
        if (*string < '0' || *string > '9') return false;
        string++;
    }

    return true;
}

int numberStrToInt(const char *string) {
    int number = 0;

    while (*string) {
        number = number * 10 + (*string - '0');
        string++;
    }

    return number;
}

bool compareString(const char *string1, const char *string2) {
    while (*string1 && *string2) {
        if (charToLower(*string1) != charToLower(*string2)) 
            return false;
            
        string1++; 
        string2++;
    }

    return *string1 == '\0' && *string2 == '\0';
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