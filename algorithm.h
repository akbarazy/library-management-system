#ifndef ALGORITHM_H
#define ALGORITHM_H

int linearSearchInteger(int kunciJawaban);
int linearSearchString(char kunciJawaban[255], int indexJawaban[255]);
int partition(int indexPertama, int indexTerakhir, int kolom, int arah);
void quickSort(int indexPertama, int indexTerakhir, int kolom, int arah);

#endif