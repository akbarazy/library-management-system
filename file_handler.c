#include <stdio.h>
#include "book.h"
#include "utils.h"
#include "file_handler.h"

int loadData(Node **firstNode)
{
    FILE *pointerFile = fopen(DATASET, "r");
    Book book;
    Node *node;

    if (!pointerFile)
        return -1;

    while (fscanf(
        pointerFile, 
        "%d,%[^,],%[^,],%d,%d\n",
        &book.id,
        book.title,
        book.author,
        &book.publicationYear,
        &book.available
    ) == 5)
    {
        printf("ok");
        node = createNode(
            book.id, 
            book.title, 
            book.author, 
            book.publicationYear, 
            book.available
        );

        if (!node)
        {
            fclose(pointerFile);
            return -1;
        }

        *firstNode = insertNode(*firstNode, node);
    }
    fclose(pointerFile);

    return 0;
}

int saveData(Node **firstNode)
{
    FILE *pointerFile = fopen(DATASET, "w");

    if (!pointerFile)
        return -1;

    // quickSort(0, jumlahSemuaBarang - 1, 1, 2);

    // for (int i = 0; i < jumlahSemuaBarang; i++)
        // fprintf(pointerFile, "%d,%s,%d,%.2f\n",
        //         semuaBarang[i].id,
        //         semuaBarang[i].nama,
        //         semuaBarang[i].stok,
        //         semuaBarang[i].harga);
    fclose(pointerFile);

    return 0;
}