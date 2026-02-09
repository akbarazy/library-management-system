#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

typedef struct
{
    int id;
    char title[256];
    char author[256];
    int publicationYear;
    bool available;
} Book;

typedef struct Node
{
    Book book;
    struct Node *next;
    struct Node *prev;
} Node;

void addBooks();
void showBooks();
void updateBooks();
void deleteBooks();
void searchBooks();
void sortBooks();

#endif