#include <stdio.h>
#include "book.h"
#include "utils.h"
#include "file_handler.h"

int loadData(Node **firstNode)
{
    FILE *file = fopen(DATASET, "r");
    Book book;
    Node *node;

    if (!file)
        return -1;

    while (fscanf(
        file, 
        "%d,%255[^,],%255[^,],%d,%d",
        &book.id,
        book.title,
        book.author,
        &book.publicationYear,
        &book.available
    ) == 5)
    {
        node = createNode();
        if (!node)
        {
            fclose(file);
            return -1;
        }

        node->book = book;
        insertNode(firstNode, node);
    }
    fclose(file);

    return 0;
}

int saveData(Node **firstNode)
{
    FILE *file = fopen(DATASET, "w");

    if (!file)
        return -1;

    // quickSort(0, jumlahSemuaBarang - 1, 1, 2);

    // for (int i = 0; i < jumlahSemuaBarang; i++)
        // fprintf(file, "%d,%s,%d,%.2f\n",
        //         semuaBarang[i].id,
        //         semuaBarang[i].nama,
        //         semuaBarang[i].stok,
        //         semuaBarang[i].harga);
    fclose(file);

    return 0;
}