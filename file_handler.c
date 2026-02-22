#include <stdio.h>
#include <stdbool.h>
#include "book.h"
#include "utils.h"
#include "file_handler.h"

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

    if (!file)
        return false;

    // quickSort(0, jumlahSemuaBarang - 1, 1, 2);

    // for (int i = 0; i < jumlahSemuaBarang; i++)
        // fprintf(file, "%d,%s,%d,%.2f\n",
        //         semuaBarang[i].id,
        //         semuaBarang[i].nama,
        //         semuaBarang[i].stok,
        //         semuaBarang[i].harga);
    fclose(file);

    return true;
}