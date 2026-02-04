#include "file_handler.h"
#include <stdio.h>

int loadData()
{
    FILE *pointerFile = fopen(DATASET, "r");

    if (!pointerFile)
        return -1;

    // while (fscanf(pointerFile, "%d,%49[^,],%d,%f",
    //               &semuaBarang[jumlahSemuaBarang].id,
    //               semuaBarang[jumlahSemuaBarang].nama,
    //               &semuaBarang[jumlahSemuaBarang].stok,
    //               &semuaBarang[jumlahSemuaBarang].harga) == 4)
    // {
    //     jumlahSemuaBarang++;
    // }
    fclose(pointerFile);

    return 0;
}

int saveData()
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
