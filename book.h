#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

typedef struct {
    int id;
    char title[256];
    char author[256];
    int year;
    bool available;
} Book;

typedef struct Node {
    Book book;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    char notification[256];
    bool exitMenu;
} Output;

typedef enum {
    ID,
    TITLE,
    AUTHOR,
    YEAR,
    AVAILABLE
} Field;

Output addBooks(Node **firstNode);
Output showBooks(Node *firstNode);
Output updateBooks(Node *firstNode);
Output deleteBooks(Node **firstNode);
Output searchBooks(Node *firstNode);
Output sortBooks(Node **firstNode);

#endif