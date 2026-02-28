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

Node *sortedMerge(Node *a, Node *b) {
    Node *result = NULL;

    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

void mergeSort(Node **firstNode) {
    Node* firstNodeTemp = *firstNode;
    if (!firstNodeTemp || !firstNodeTemp->next) return;

    Node* a;
    Node* b;

    splitList(firstNodeTemp, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *firstNode = sortedMerge(a, b);
}