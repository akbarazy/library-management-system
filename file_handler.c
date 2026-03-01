#include <stdio.h>
#include <stdbool.h>
#include "book.h"
#include "utils.h"
#include "file_handler.h"
#include "algorithm.h"

bool loadData(Node **firstNode) {
    FILE *file = fopen(DATASET, "r");
    Book book;
    Node *node;

    if (!file)
        return false;

    while (fscanf(
        file, 
        "%d,%255[^,],%255[^,],%d,%d",
        &book.id,
        book.title,
        book.author,
        &book.year,
        &book.available
    ) == 5) {
        
        node = createNode();
        if (!node)
        {
            fclose(file);
            return false;
        }

        node->book = book;
        insertNode(firstNode, node);
    }

    fclose(file);
    if (!*firstNode) return false;

    return true;
}

bool saveData(Node **firstNode) {
    FILE *file = fopen(DATASET, "w");
    Node *node;

    if (!file)
        return false;

    if (*firstNode && (*firstNode)->next) {
        mergeSort(firstNode, 1, 1);
    }

    node = *firstNode;
    while (node) {
        fprintf(file, node->next != NULL ? "%d,%s,%s,%d,%d\n" : "%d,%s,%s,%d,%d",
                node->book.id,
                node->book.title,
                node->book.author,
                node->book.year,
                node->book.available);

        node = node->next;
    }

    fclose(file);
    deleteAllNode(firstNode);

    return true;
}