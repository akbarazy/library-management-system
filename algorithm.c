#include "algorithm.h"
#include "book.h"

Node *linearSearchInt(Node *firstNode, int integer) {
    while (firstNode != NULL) {
        if (firstNode->book.id == integer) {
            return firstNode;
        }
        firstNode = firstNode->next;
    }
    return NULL;
}

// int linearSearchStr(char kunciJawaban[255], int indexJawaban[255])
// {
//     int jumlahJawaban = 0;
//     char kunciJawabanSalinan[255],
//         namaBarangSalinan[255];

//     hurufKecil(kunciJawaban, kunciJawabanSalinan);

//     for (int i = 0; i < jumlahSemuaBarang; i++)
//     {
//         hurufKecil(semuaBarang[i].nama, namaBarangSalinan);

//         if (strstr(namaBarangSalinan, kunciJawabanSalinan) != NULL)
//         {
//             indexJawaban[jumlahJawaban] = i;
//             jumlahJawaban++;
//         }
//     }
//     return jumlahJawaban;
// }

// int partition(int indexPertama, int indexTerakhir, int kolom, int arah)
// {
//     Barang pivot = semuaBarang[indexTerakhir];
//     int indexTukar = indexPertama - 1;

//     for (int i = indexPertama; i < indexTerakhir; i++)
//     {
//         if (kondisiUrutan(semuaBarang[i], pivot, kolom, arah))
//         {
//             indexTukar++;

//             Barang cadangan = semuaBarang[indexTukar];
//             semuaBarang[indexTukar] = semuaBarang[i];
//             semuaBarang[i] = cadangan;
//         }
//     }

//     Barang cadangan = semuaBarang[indexTukar + 1];
//     semuaBarang[indexTukar + 1] = semuaBarang[indexTerakhir];
//     semuaBarang[indexTerakhir] = cadangan;

//     return indexTukar + 1;
// }

// void quickSort(int indexPertama, int indexTerakhir, int kolom, int arah)
// {
//     if (indexPertama < indexTerakhir)
//     {
//         int indexPivot = partition(indexPertama, indexTerakhir, kolom, arah);

//         quickSort(indexPertama, indexPivot - 1, kolom, arah);
//         quickSort(indexPivot + 1, indexTerakhir, kolom, arah);
//     }
// }