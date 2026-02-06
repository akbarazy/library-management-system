#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

typedef struct
{
    int id;
    char *title;
    char *author;
    int publicationYear;
    bool available;
} Book;

typedef struct Node
{
    Book book;
    struct Node *next;
} Node;

void tambahBuku();
void tampilkanBuku();
void ubahBuku();
void hapusBuku();
void cariBuku();

#endif