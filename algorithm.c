#include <stdio.h>
#include <string.h>
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
            
            return firstNodeTemp;
        } else if (field == YEAR && firstNode->book.year == integer) {
            Node *node = createNode();
            if (node == NULL) {
                deleteAllNode(&firstNodeTemp);
                return NULL;
            }
            
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
        if (field == TITLE && compareString(firstNode->book.title, string, PARTIAL)) {
            Node *node = createNode();
            if (node == NULL) {
                deleteAllNode(&firstNodeTemp);
                return NULL;
            }
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        } else if (field == AUTHOR && compareString(firstNode->book.author, string, PARTIAL)) {
            Node *node = createNode();
            if (node == NULL) {
                deleteAllNode(&firstNodeTemp);
                return NULL;
            }
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        }

        firstNode = firstNode->next;
    }

    return firstNodeTemp;
}

Node *linearSearchBool(Node *firstNode, Field field, bool boolean) {
    Node *firstNodeTemp = NULL;

    while (firstNode != NULL) {
        if (field == AVAILABLE && firstNode->book.available == boolean) {
            Node *node = createNode();
            if (node == NULL) {
                deleteAllNode(&firstNodeTemp);
                return NULL;
            }
            
            node->book = firstNode->book;
            insertNode(&firstNodeTemp, node);
        }

        firstNode = firstNode->next;
    }
    
    return firstNodeTemp;
}

int sortOption(Node *a, Node *b, int sortOption1, int sortOption2) {
    int asc = sortOption2 % 2;

    switch (sortOption1) {
        case 1:
            if (a->book.id == b->book.id) return 0;
            return asc ?
                (a->book.id < b->book.id ? -1 : 1) :
                (a->book.id > b->book.id ? -1 : 1);

        case 2:
            return asc ?
                strcmp(a->book.title, b->book.title) :
                strcmp(b->book.title, a->book.title);

        case 3:
            return asc ?
                strcmp(a->book.author, b->book.author) :
                strcmp(b->book.author, a->book.author);

        case 4:
            if (a->book.year == b->book.year) return 0;
            return asc ?
                (a->book.year < b->book.year ? -1 : 1) :
                (a->book.year > b->book.year ? -1 : 1);

        case 5:
            return asc ?
                (a->book.available - b->book.available) :
                (b->book.available - a->book.available);
    }

    return 0;
}

void splitList(Node *source, Node **frontNode, Node **backNode) {
    Node* slow = source;
    Node* fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontNode = source;
    *backNode = slow->next;
    slow->next = NULL;
}

Node *sortedMerge(Node *a, Node *b, int sortOption1, int sortOption2) {
    if (!a) return b;
    if (!b) return a;

    if (sortOption(a, b, sortOption1, sortOption2) <= 0) {
        a->next = sortedMerge(a->next, b, sortOption1, sortOption2);
        return a;
    } else {
        b->next = sortedMerge(a, b->next, sortOption1, sortOption2);
        return b;
    }
}

void mergeSort(Node **headRef, int sortOption1, int sortOption2) {
    if (!*headRef || !(*headRef)->next) return;

    Node *a;
    Node *b;

    splitList(*headRef, &a, &b);

    mergeSort(&a, sortOption1, sortOption2);
    mergeSort(&b, sortOption1, sortOption2);

    *headRef = sortedMerge(a, b, sortOption1, sortOption2);
}