#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_handler.h"
#include "book.h"
#include "algorithm.h"
#include "utils.h"

typedef enum
{
    TAMBAH = 1,
    TAMPILKAN,
    UBAH,
    HAPUS,
    CARI,
    URUTKAN,
    KELUAR
} Menu;

void tampilanJudul();
void tampilanMenu(int menuSaatIni);
void tampilanTabel();

int main()
{
    Node *firstNode = malloc(sizeof(*Node));
    Menu currentMenu;
    int fileStatus = memuatDariFile();
    char input, *notification;
    bool isMenuChanged = false;

    return 0;
}

void tampilanJudul()
{
    printf(" /$$$$$$ /$$   /$$ /$$    /$$ /$$$$$$$$ /$$   /$$ /$$$$$$$$ /$$$$$$  /$$$$$$$  /$$$$$$  /$$$$$$\n");
    printf("|_  $$_/| $$$ | $$| $$   | $$| $$_____/| $$$ | $$|__  $$__//$$__  $$| $$__  $$|_  $$_/ /$$__  $$\n");
    printf("  | $$  | $$$$| $$| $$   | $$| $$      | $$$$| $$   | $$  | $$  \\ $$| $$  \\ $$  | $$  | $$  \\__/\n");
    printf("  | $$  | $$ $$ $$|  $$ / $$/| $$$$$   | $$ $$ $$   | $$  | $$$$$$$$| $$$$$$$/  | $$  |  $$$$$$\n");
    printf("  | $$  | $$  $$$$ \\  $$ $$/ | $$__/   | $$  $$$$   | $$  | $$__  $$| $$__  $$  | $$   \\____  $$\n");
    printf("  | $$  | $$\\  $$$  \\  $$$/  | $$      | $$\\  $$$   | $$  | $$  | $$| $$  \\ $$  | $$   /$$  \\ $$\n");
    printf(" /$$$$$$| $$ \\  $$   \\  $/   | $$$$$$$$| $$ \\  $$   | $$  | $$  | $$| $$  | $$ /$$$$$$|  $$$$$$/\n");
    printf("|______/|__/  \\__/    \\_/    |________/|__/  \\__/   |__/  |__/  |__/|__/  |__/|______/ \\______/\n");
    printf("\n");
    printf(" /$$$$$$$   /$$$$$$  /$$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$\n");
    printf("| $$__  $$ /$$__  $$| $$__  $$ /$$__  $$| $$$ | $$ /$$__  $$\n");
    printf("| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$$$| $$| $$  \\__/\n");
    printf("| $$$$$$$ | $$$$$$$$| $$$$$$$/| $$$$$$$$| $$ $$ $$| $$ /$$$$\n");
    printf("| $$__  $$| $$__  $$| $$__  $$| $$__  $$| $$  $$$$| $$|_  $$\n");
    printf("| $$  \\ $$| $$  | $$| $$  \\ $$| $$  | $$| $$\\  $$$| $$  \\ $$\n");
    printf("| $$$$$$$/| $$  | $$| $$  | $$| $$  | $$| $$ \\  $$|  $$$$$$/\n");
    printf("|_______/ |__/  |__/|__/  |__/|__/  |__/|__/  \\__/ \\______/\n\n\n");
}

void tampilanTabel()
{
    char stringJumlahSemuaBarang[255];
    snprintf(stringJumlahSemuaBarang, 255, "Total %d Barang.", jumlahSemuaBarang);

    printf("======================================================================================\n");
    printf("|                             D A F T A R   B A R A N G                              |\n");
    printf("======================================================================================\n");
    printf("| %-23s | %-20s | %-33s |\n", stringJumlahSemuaBarang, statusTabel[0], statusTabel[1]);
    printf("--------------------------------------------------------------------------------------\n");
    printf("| Id   | Nama Barang                                        | Stok | Harga           |\n");
    printf("--------------------------------------------------------------------------------------\n");

    if (jumlahSemuaBarang > 0)
    {
        for (int i = indexPertama; i < indexTerakhir + 1; i++)
        {
            printf("| B%03d | %-50s | %-4d | Rp %-12.2f |\n",
                   semuaBarang[i].id,
                   semuaBarang[i].nama,
                   semuaBarang[i].stok,
                   semuaBarang[i].harga);
        }

        printf("--------------------------------------------------------------------------------------\n");
    }
    printf("\n");
}

void tampilanMenu(int menuSaatIni)
{
    switch (menuSaatIni)
    {
    case 1:
        printf("========================\n");
        printf("|      MENU UTAMA      |\n");
        printf("========================\n");
        printf("| 1. Tambah Barang     |\n");
        printf("| 2. Tampilkan Barang  |\n");
        printf("| 3. Ubah Barang       |\n");
        printf("| 4. Hapus Barang      |\n");
        printf("| 0. Simpan & Keluar   |\n");
        printf("------------------------\n\n");
        break;
    case 2:
        printf("========================   ==============================\n");
        printf("|      MENU UTAMA      |   |      TAMPILKAN BARANG      |\n");
        printf("========================   ==============================\n");
        printf("| 1. Tambah Barang     |   | 1. Ubah Paginasi           |\n");
        printf("| 2. Tampilkan Barang  |   | 2. Cari Barang             |\n");
        printf("| 3. Ubah Barang       |   | 3. Urutkan Barang          |\n");
        printf("| 4. Hapus Barang      |   | 0. Kembali Ke Menu Utama   |\n");
        printf("| 0. Simpan & Keluar   |   ------------------------------\n");
        printf("------------------------\n\n");
        break;
    case 3:
        printf("========================   ==============================\n");
        printf("|      MENU UTAMA      |   |        HAPUS BARANG        |\n");
        printf("========================   ==============================\n");
        printf("| 1. Tambah Barang     |   | 1. Hapus Semua             |\n");
        printf("| 2. Tampilkan Barang  |   | 2. Hapus Beberapa          |\n");
        printf("| 3. Ubah Barang       |   | 3. Hapus Barang            |\n");
        printf("| 4. Hapus Barang      |   | 0. Kembali Ke Menu Utama   |\n");
        printf("| 0. Simpan & Keluar   |   ------------------------------\n");
        printf("------------------------\n\n");
        break;
    }
}