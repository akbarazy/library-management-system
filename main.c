#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>

#define MAX_BARANG 255
#define FILE_CSV "dataset.csv"

typedef struct
{
    int id;
    char nama[255];
    int stok;
    float harga;
} Barang;

typedef enum
{
    MENU_UTAMA = 1,
    MENU_TAMPILKAN,
    MENU_HAPUS
} Menu;

Barang semuaBarang[MAX_BARANG];
int arah = 2,
    kolom = 1,
    jumlahBaris,
    indexPertama = 0,
    indexTerakhir = 0,
    jumlahSemuaBarang = 0;
bool muatUlang = false;
char statusTabel[2][255] = {
    "Paginasi Ke 1.", 
    "Dari Id Terkecil."
};

int memuatDariFile();
int menyimpanKeFile();

void tampilanJudul();
void tampilanTabel();
void tampilanMenu(int menuSaatIni);

void tambahBarang();
void ubahPaginasi();
void cariBarang();
void urutkanBarang();
void ubahBarang();
void hapusSemua();
void hapusBeberapa();
void hapusBarang();

int linearSearchId(int kunciJawaban);
int linearSearchNama(char kunciJawaban[255], int indexJawaban[255]);
int partition(int indexPertama, int indexTerakhir, int kolom, int arah);
void quickSort(int indexPertama, int indexTerakhir, int kolom, int arah);

void hapusBaris(int jumlahBaris);
void deskripsiUrutan(int kolom, int arah);
int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah);
void hurufKecil(char *stringAsli, char *stringSalinan);
void hapusSpasi(char *stringAsli);

int main()
{
    Menu menuSaatIni1 = MENU_UTAMA;
    int statusFile = memuatDariFile();
    char input[255],
        namaPengguna[255],
        kataSandi[255],
        pesanProgram[255] = "Pesan Program Disini.",
        menuSaatIni2[255] = "Menu Utama>";
    bool menuBerganti = false;

    system("cls");
    tampilanJudul();

    printf("=====================================\n");
    printf("|     P E M B E R I T A H U A N     |\n");
    printf("=====================================\n");
    printf("| + Console Wajib Full Selayar.     |\n");
    printf("| + Console Jangan Terlalu Ngezoom. |\n");
    printf("-------------------------------------\n\n");

    do
    {
        printf("--- %s ---\n", pesanProgram);
        strcpy(pesanProgram, "Pesan Program Disini.");

        while (1)
        {
            printf("Nama Pengguna : ");
            fgets(namaPengguna, 255, stdin);

            namaPengguna[strcspn(namaPengguna, "\n")] = '\0';

            hapusSpasi(namaPengguna);

            if (strlen(namaPengguna) == 0)
            {
                system("cls");
                return 0;
            }

            hapusBaris(1);

            if (strlen(namaPengguna) > 0 && strlen(namaPengguna) <= 50)
            {
                printf("Nama Pengguna : %s\n", namaPengguna);
                break;
            }
        }

        while (1)
        {
            printf("Kata Sandi : ");
            fgets(kataSandi, 255, stdin);

            kataSandi[strcspn(kataSandi, "\n")] = '\0';

            hapusSpasi(kataSandi);

            if (strlen(kataSandi) == 0)
            {
                system("cls");
                return 0;
            }

            hapusBaris(1);

            if (strlen(kataSandi) > 0 && strlen(kataSandi) <= 50)
            {
                printf("Nama Pengguna : %s\n", kataSandi);
                break;
            }
        }

        if (strcmp(namaPengguna, "Admin") != 0 || strcmp(kataSandi, "Admin123") != 0)
            strcpy(pesanProgram, "Gagal Untuk Login.");

        if (strcmp(namaPengguna, "Admin") == 0 && strcmp(kataSandi, "Admin123") == 0)
            strcpy(pesanProgram, "Berhasil Untuk Login.");
        
        hapusBaris(3);

    } while (strcmp(pesanProgram, "Gagal Untuk Login.") == 0);

    strcpy(pesanProgram, statusFile == 0 ? "Berhasil Memuat File." : "Gagal Memuat File.");

    if (jumlahSemuaBarang > 10)
        indexTerakhir = 9;

    do
    {
        hapusBaris(50);

        if (jumlahSemuaBarang <= 10)
            indexTerakhir = jumlahSemuaBarang - 1;
        tampilanTabel();

        menuBerganti = false;

        tampilanMenu(menuSaatIni1);

        printf("--- %s ---\n", pesanProgram);
        strcpy(pesanProgram, "Pesan Program Disini.");

        if (muatUlang)
            printf("%s Pilih Menu : %d\n", menuSaatIni2, atoi(input));
        
        if (!muatUlang)
        {
            printf("%s Pilih Menu : ", menuSaatIni2);
            fgets(input, 255, stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) == 0)
            {
                strcpy(pesanProgram, "Input Tidak Boleh Kosong.");

                strcpy(input, "-1");

                continue;
            }

            int angka = true;
            for (int i = 0; i < strlen(input); i++)
            {
                if (!isdigit(input[i]) && input[i] != '-')
                {
                    angka = false;
                    break;
                }
            }

            if (!angka)
            {
                strcpy(pesanProgram, "Input Harus Berupa Angka.");

                strcpy(input, "-1");

                continue;
            }
        }

        if (menuSaatIni1 == MENU_UTAMA && !menuBerganti)
        {
            switch (atoi(input))
            {
            case 1:
                if (jumlahSemuaBarang == 255)
                    strcpy(pesanProgram, "Daftar Barang Penuh.");

                if (jumlahSemuaBarang < 255)
                    tambahBarang();
                break;
            case 2:
                if (jumlahSemuaBarang == 0)
                    strcpy(pesanProgram, "Daftar Barang Kosong.");

                if (jumlahSemuaBarang > 0)
                    menuSaatIni1 = MENU_TAMPILKAN;
                    strcpy(menuSaatIni2, "Menu Utama> Tampilkan Barang>");

                    menuBerganti = true;
                break;
            case 3:
                if (jumlahSemuaBarang == 0)
                    strcpy(pesanProgram, "Daftar Barang Kosong.");

                if (jumlahSemuaBarang > 0)
                    ubahBarang();
                break;
            case 4:
                if (jumlahSemuaBarang == 0)
                    strcpy(pesanProgram, "Daftar Barang Kosong.");

                if (jumlahSemuaBarang > 0)
                {
                    menuSaatIni1 = 3;
                    strcpy(menuSaatIni2, "Menu Utama> Hapus Barang>");
                    menuBerganti = true;
                }
                break;
            case 0:
                menyimpanKeFile();
                break;
            default:
                strcpy(pesanProgram, "Opsi Tidak Tersedia.");
                break;
            }
        }

        if (menuSaatIni1 == MENU_TAMPILKAN && !menuBerganti)
        {
            switch (atoi(input))
            {
            case 1:
                if (jumlahSemuaBarang <= 10)
                    strcpy(pesanProgram, "Daftar Barang Kurang.");

                if (jumlahSemuaBarang > 10)
                    ubahPaginasi();
                break;
            case 2:
                if (jumlahSemuaBarang == 0)
                    strcpy(pesanProgram, "Daftar Barang Kosong.");

                if (jumlahSemuaBarang > 0)
                    cariBarang();
                break;
            case 3:
                if (jumlahSemuaBarang < 2)
                {
                    strcpy(pesanProgram, "Daftar Barang Kurang.");
                } else if (jumlahSemuaBarang > 1) {
                    urutkanBarang();
                }
                break;
            case 0:
                menuSaatIni1 = MENU_UTAMA;
                strcpy(menuSaatIni2, "Menu Utama>");
                menuBerganti = true;
                break;
            default:
                strcpy(pesanProgram, "Opsi Tidak Tersedia.");
                break;
            }
        }

        if (menuSaatIni1 == MENU_HAPUS && !menuBerganti)
        {
            switch (atoi(input))
            {
            case 1:
                if (jumlahSemuaBarang <= 10)
                {
                    strcpy(pesanProgram, "Daftar Barang Kurang.");
                } else if (jumlahSemuaBarang > 10) {
                    hapusSemua();
                }
                break;
            case 2:
                if (jumlahSemuaBarang < 2)
                {
                    strcpy(pesanProgram, "Daftar Barang Kurang.");
                } else if (jumlahSemuaBarang > 1) {
                    hapusBeberapa();
                }
                break;
            case 3:
                hapusBarang();
                break;
            case 0:
                menuSaatIni1 = MENU_UTAMA;
                strcpy(menuSaatIni2, "Menu Utama>");
                menuBerganti = true;
                break;
            default:
                strcpy(pesanProgram, "Opsi Tidak Tersedia.");
                break;
            }

            if (jumlahSemuaBarang == 0)
            {
                indexPertama = 0;
                indexTerakhir = 0;

                muatUlang = false;

                menuSaatIni1 = 1;
                strcpy(menuSaatIni2, "Menu Utama>");
                menuBerganti = true;

                strcpy(statusTabel[0], "Paginasi Ke 1.");
                strcpy(statusTabel[1], "Dari Id Terkecil.");
                kolom = 1;
                arah = 2;
            }

            if (jumlahSemuaBarang > 0)
            {
                if (indexPertama >= jumlahSemuaBarang && indexPertama > 0)
                {
                    int paginasiTerkanan = (jumlahSemuaBarang + 9) / 10;
                    snprintf(statusTabel[0], 255, "Paginasi Ke %d.", paginasiTerkanan);

                    indexPertama = paginasiTerkanan * 10 - 10;
                    indexTerakhir = (jumlahSemuaBarang - indexPertama < 10) ? jumlahSemuaBarang - indexPertama - 1 : 9;
                    indexTerakhir += indexPertama;
                }

                if (jumlahSemuaBarang - 1 >= indexPertama && jumlahSemuaBarang - 1 <= indexTerakhir)
                    indexTerakhir = jumlahSemuaBarang - 1;
            }
        }
    } while (atoi(input) != 0 || menuBerganti);

    system("cls");

    return 0;
}

int memuatDariFile()
{
    FILE *pointerFile = fopen(FILE_CSV, "r");

    if (!pointerFile)
        return -1;

    while (fscanf(pointerFile, "%d,%49[^,],%d,%f",
                  &semuaBarang[jumlahSemuaBarang].id,
                  semuaBarang[jumlahSemuaBarang].nama,
                  &semuaBarang[jumlahSemuaBarang].stok,
                  &semuaBarang[jumlahSemuaBarang].harga) == 4)
    {
        jumlahSemuaBarang++;
    }
    fclose(pointerFile);

    return 0;
}

int menyimpanKeFile()
{
    FILE *pointerFile = fopen(FILE_CSV, "w");

    if (!pointerFile)
        return -1;

    quickSort(0, jumlahSemuaBarang - 1, 1, 2);

    for (int i = 0; i < jumlahSemuaBarang; i++)
        fprintf(pointerFile, "%d,%s,%d,%.2f\n",
                semuaBarang[i].id,
                semuaBarang[i].nama,
                semuaBarang[i].stok,
                semuaBarang[i].harga);
    fclose(pointerFile);

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

void tambahBarang()
{
    char input[255];
    Barang barangBaru;

    printf("=== TAMBAH BARANG ===\n");
    printf("Id    : B%03d\n", jumlahSemuaBarang + 1);
    barangBaru.id = jumlahSemuaBarang + 1;

    while (1)
    {
        printf("Nama  : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';
        hapusSpasi(input);

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(3);
            return;
        }

        hapusBaris(1);

        if (strlen(input) > 0 && strlen(input) <= 50)
        {
            strcpy(barangBaru.nama, input);
            printf("Nama  : %s\n", barangBaru.nama);
            break;
        }
    }

    while (1)
    {
        printf("Stok  : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(4);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(1);
            continue;
        }

        bool angka = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        if (atoi(input) > 9999)
        {
            hapusBaris(1);
            continue;
        }

        hapusBaris(1);
        barangBaru.stok = atoi(input);
        printf("Stok  : %d\n", barangBaru.stok);
        break;
    }

    while (1)
    {
        printf("Harga : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(5);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(1);
            continue;
        }

        bool angka = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        if (atof(input) < 100 || atof(input) > 999999999999)
        {
            hapusBaris(1);
            continue;
        }

        hapusBaris(1);
        barangBaru.harga = atof(input);
        printf("Harga : %.2f\n", barangBaru.harga);
        break;
    }

    if (indexTerakhir - indexPertama + 1 < 10)
        indexTerakhir++;

    semuaBarang[jumlahSemuaBarang] = barangBaru;
    jumlahSemuaBarang++;

    quickSort(0, jumlahSemuaBarang - 1, kolom, arah);

    muatUlang = true;
    hapusBaris(5);
}

void ubahPaginasi()
{
    int paginasiSaatIni,
        totalPaginasi = (jumlahSemuaBarang + 9) / 10;
    char input[255];

    printf("=== UBAH PAGINASI ===\n");
    sscanf(statusTabel[0], "Paginasi Ke %d.", &paginasiSaatIni);

    for (int i = 0; i < totalPaginasi; i++)
    {
        if (i + 1 == paginasiSaatIni)
            printf("[%d] ", i + 1);

        if (i + 1 != paginasiSaatIni)
            printf("%d ", i + 1);
            
        if ((i + 1) % 10 == 0 && i + 1 < totalPaginasi)
            printf("\n");
    }
    printf("\n");

    while (1)
    {
        printf("Pilih Paginasi : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(3 + ((totalPaginasi - 1) / 10));
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(1);
            continue;
        }

        int angka = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        if (!(atoi(input) > 0 && atoi(input) <= totalPaginasi && atoi(input) != paginasiSaatIni))
        {
            hapusBaris(1);
            continue;
        }

        paginasiSaatIni = atoi(input);
        snprintf(statusTabel[0], 255, "Paginasi Ke %d.", paginasiSaatIni);

        indexPertama = paginasiSaatIni * 10 - 10;
        indexTerakhir = (jumlahSemuaBarang - indexPertama < 10) ? jumlahSemuaBarang - indexPertama - 1 : 9;
        indexTerakhir += indexPertama;
        break;
    }

    hapusBaris(3 + ((totalPaginasi - 1) / 10));
    muatUlang = true;
}

void cariBarang()
{
    int jumlahJawaban,
        barangSaatIni,
        indexJawaban[255],
        indexBarangSaatIni;
    char input[255];

    printf("=== CARI BARANG ===\n");

    while (1)
    {
        printf("Masukkan Nama : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';
        hapusSpasi(input);

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(2);
            return;
        }

        if (!(strlen(input) > 0 && strlen(input) <= 50))
        {
            hapusBaris(1);
            continue;
        }

        jumlahJawaban = linearSearchNama(input, indexJawaban);

        if (jumlahJawaban == 0)
        {
            hapusBaris(1);
            continue;
        }

        hapusBaris(1);
        break;
    }

    barangSaatIni = 1;
    indexBarangSaatIni = indexJawaban[barangSaatIni - 1];

    while (1)
    {
        printf("Id    : B%03d\n", semuaBarang[indexBarangSaatIni].id);
        printf("Nama  : %s\n", semuaBarang[indexBarangSaatIni].nama);
        printf("Stok  : %d\n", semuaBarang[indexBarangSaatIni].stok);
        printf("Harga : %.2f\n", semuaBarang[indexBarangSaatIni].harga);

        for (int i = 0; i < jumlahJawaban; i++)
        {
            if (i + 1 == barangSaatIni)
                printf("[%d] ", i + 1);

            if (i + 1 != barangSaatIni)
                printf("%d ", i + 1);
                
            if ((i + 1) % 10 == 0 && i + 1 < jumlahJawaban)
                printf("\n");
        }

        printf("\nPilih Barang : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(7 + ((jumlahJawaban - 1) / 10));
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(6 + ((jumlahJawaban - 1) / 10));
            continue;
        }

        int angka = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(6 + ((jumlahJawaban - 1) / 10));
            continue;
        }

        if (!(atoi(input) > 0 && atoi(input) <= jumlahJawaban && atoi(input) != barangSaatIni))
        {
            hapusBaris(6 + ((jumlahJawaban - 1) / 10));
            continue;
        }

        hapusBaris(6 + ((jumlahJawaban - 1) / 10));
        barangSaatIni = atoi(input);
        indexBarangSaatIni = indexJawaban[barangSaatIni - 1];
    }
}

void urutkanBarang()
{
    char input[255];

    printf("=== URUTKAN BARANG ===\n");

    while (1)
    {
        printf("Berdasarkan?\n");
        printf("1. Id\n2. Nama\n3. Stok\n4. Harga\n");
        printf("Pilih Kolom : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(7);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(6);
            continue;
        }

        int angka = true;
        for (int i = 1; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(6);
            continue;
        }

        if (!(atoi(input) > 0 && atoi(input) < 5))
        {
            hapusBaris(6);
            continue;
        }
        
        kolom = atoi(input);
        hapusBaris(6);
        break;
    }

    while (1)
    {
        printf("Berdasarkan?\n");
        printf("1. Menurun\n2. Menaik\n");
        printf("Pilih Arah : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(5);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(4);
            continue;
        }

        int angka = true;
        for (int i = 1; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(4);
            continue;
        }

        if (!(atoi(input) == 1 || atoi(input) == 2))
        {
            hapusBaris(4);
            continue;
        }
        
        arah = atoi(input);
        hapusBaris(4);
        break;
    }

    quickSort(0, jumlahSemuaBarang - 1, kolom, arah);
    deskripsiUrutan(kolom, arah);

    hapusBaris(1);
    muatUlang = true;
}

void ubahBarang()
{
    int indexJawaban;
    char input[255];
    Barang barangBaru;

    printf("=== UBAH BARANG ===\n");

    while (1)
    {
        printf("Masukkan Id : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(2);
            return;
        }

        if (strlen(input) < 4 || toupper(input[0]) != 'B')
        {
            hapusBaris(1);
            continue;
        }

        int angka = true;
        for (int i = 1; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        indexJawaban = linearSearchId(atoi(input + 1));

        if (indexJawaban == -1)
        {
            hapusBaris(1);
            continue;
        }

        hapusBaris(1);
        break;
    }

    barangBaru = semuaBarang[indexJawaban];

    while (1)
    {
        printf("Id    : B%03d\n", barangBaru.id);
        printf("Nama  : %s\n", barangBaru.nama);
        printf("Menjadi : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';
        hapusSpasi(input);

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(4);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(1);
            break;
        }

        if (strlen(input) > 0 && strlen(input) <= 50)
        {
            hapusBaris(2);
            strcpy(barangBaru.nama, input);
            printf("Nama  : %s\n", barangBaru.nama);
            break;
        }

        hapusBaris(3);
    }

    while (1)
    {
        printf("Stok  : %d\n", barangBaru.stok);
        printf("Menjadi : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(5);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(1);
            break;
        }

        bool angka = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(2);
            continue;
        }

        if (atoi(input) > 9999)
        {
            hapusBaris(2);
            continue;
        }

        hapusBaris(2);
        barangBaru.stok = atoi(input);
        printf("Stok  : %d\n", barangBaru.stok);
        break;
    }

    while (1)
    {
        printf("Harga : %.2f\n", barangBaru.harga);
        printf("Menjadi : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(6);
            return;
        }

        if (strlen(input) == 0)
        {
            hapusBaris(1);
            break;
        }

        bool angka = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(2);
            continue;
        }

        if (atof(input) < 100 || atof(input) > 999999999999)
        {
            hapusBaris(2);
            continue;
        }

        hapusBaris(2);
        barangBaru.harga = atof(input);
        printf("Harga : %.2f\n", barangBaru.harga);
        break;
    }

    semuaBarang[indexJawaban] = barangBaru;

    hapusBaris(5);
    muatUlang = true;
}

void hapusSemua()
{
    Barang kosong = {0};

    for (int i = 0; i < jumlahSemuaBarang; i++)
        semuaBarang[i] = kosong;

    jumlahSemuaBarang = 0;
}

void hapusBeberapa()
{
    int indexJawaban[2],
        jumlahBarangDihapus;
    char input[255];
    Barang kosong = {0};

    printf("=== HAPUS BEBERAPA ===\n");

    while (1)
    {
        printf("Dari Id : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(2);
            return;
        }

        if (strlen(input) < 4 || toupper(input[0]) != 'B')
        {
            hapusBaris(1);
            continue;
        }

        int angka = true;
        for (int i = 1; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        if (atoi(input + 1) < 1 || atoi(input + 1) > jumlahSemuaBarang)
        {
            hapusBaris(1);
            continue;
        }

        indexJawaban[0] = linearSearchId(atoi(input + 1));
        break;
    }

    while (1)
    {
        printf("Sampai Id : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(3);
            return;
        }

        if (strlen(input) < 4 || toupper(input[0]) != 'B')
        {
            hapusBaris(1);
            continue;
        }

        int angka = true;
        for (int i = 1; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        if (atoi(input + 1) == indexJawaban[0] + 1)
        {
            hapusBaris(1);
            continue;
        }

        if (atoi(input + 1) < 1 || atoi(input + 1) > jumlahSemuaBarang)
        {
            hapusBaris(1);
            continue;
        }

        indexJawaban[1] = linearSearchId(atoi(input + 1));
        hapusBaris(3);
        break;
    }

    if (indexJawaban[1] < indexJawaban[0])
    {
        int cadangan = indexJawaban[0];
        indexJawaban[0] = indexJawaban[1];
        indexJawaban[1] = cadangan;
    }
    jumlahBarangDihapus = indexJawaban[1] - indexJawaban[0] + 1;

    for (int i = indexJawaban[1] + 1; i < jumlahSemuaBarang; i++)
        semuaBarang[i - jumlahBarangDihapus] = semuaBarang[i];
    
    for (int i = jumlahSemuaBarang - jumlahBarangDihapus; i < jumlahSemuaBarang; i++)
        semuaBarang[i] = kosong;

    jumlahSemuaBarang -= jumlahBarangDihapus;
    muatUlang = true;
    
    if (kolom != 1 && arah != 2)
        quickSort(0, jumlahSemuaBarang - 1, 1, 2);

    for (int i = 0; i < jumlahSemuaBarang; i++)
        semuaBarang[i].id = i + 1;
    quickSort(0, jumlahSemuaBarang - 1, kolom, arah);
}

void hapusBarang()
{
    int indexJawaban;
    char input[255];
    Barang kosong = {0};   

    printf("=== HAPUS BARANG ===\n");

    while (1)
    {
        printf("Masukkan Id : ");
        fgets(input, 255, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/") == 0)
        {
            muatUlang = false;
            hapusBaris(2);
            return;
        }

        if (strlen(input) < 4 || toupper(input[0]) != 'B')
        {
            hapusBaris(1);
            continue;
        }

        int angka = true;
        for (int i = 1; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                angka = false;
                break;
            }
        }

        if (!angka)
        {
            hapusBaris(1);
            continue;
        }

        if (atoi(input + 1) < 1 || atoi(input + 1) > jumlahSemuaBarang)
        {
            hapusBaris(1);
            continue;
        }

        indexJawaban = linearSearchId(atoi(input + 1));
        hapusBaris(2);
        break;
    }

    for (int i = indexJawaban + 1; i < jumlahSemuaBarang; i++)
        semuaBarang[i - 1] = semuaBarang[i];
    
    semuaBarang[jumlahSemuaBarang - 1] = kosong;
    jumlahSemuaBarang--;

    if (kolom != 1 && arah != 2)
        quickSort(0, jumlahSemuaBarang - 1, 1, 2);

    for (int i = 0; i < jumlahSemuaBarang; i++)
        semuaBarang[i].id = i + 1;
    quickSort(0, jumlahSemuaBarang - 1, kolom, arah);

    muatUlang = true;
}

int linearSearchId(int kunciJawaban) {
    for (int i = 0; i < jumlahSemuaBarang; i++) {
        if (semuaBarang[i].id == kunciJawaban) {
            return i;
        }
    }
    return -1;
}

int linearSearchNama(char kunciJawaban[255], int indexJawaban[255])
{
    int jumlahJawaban = 0;
    char kunciJawabanSalinan[255],
        namaBarangSalinan[255];

    hurufKecil(kunciJawaban, kunciJawabanSalinan);

    for (int i = 0; i < jumlahSemuaBarang; i++)
    {
        hurufKecil(semuaBarang[i].nama, namaBarangSalinan);

        if (strstr(namaBarangSalinan, kunciJawabanSalinan) != NULL)
        {
            indexJawaban[jumlahJawaban] = i;
            jumlahJawaban++;
        }
    }
    return jumlahJawaban;
}

int partition(int indexPertama, int indexTerakhir, int kolom, int arah)
{
    Barang pivot = semuaBarang[indexTerakhir];
    int indexTukar = indexPertama - 1;

    for (int i = indexPertama; i < indexTerakhir; i++)
    {
        if (kondisiUrutan(semuaBarang[i], pivot, kolom, arah))
        {
            indexTukar++;

            Barang cadangan = semuaBarang[indexTukar];
            semuaBarang[indexTukar] = semuaBarang[i];
            semuaBarang[i] = cadangan;
        }
    }

    Barang cadangan = semuaBarang[indexTukar + 1];
    semuaBarang[indexTukar + 1] = semuaBarang[indexTerakhir];
    semuaBarang[indexTerakhir] = cadangan;

    return indexTukar + 1;
}

void quickSort(int indexPertama, int indexTerakhir, int kolom, int arah)
{
    if (indexPertama < indexTerakhir)
    {
        int indexPivot = partition(indexPertama, indexTerakhir, kolom, arah);

        quickSort(indexPertama, indexPivot - 1, kolom, arah);
        quickSort(indexPivot + 1, indexTerakhir, kolom, arah);
    }
}

void hapusBaris(int jumlahBaris)
{
    for (int i = 0; i < jumlahBaris; i++)
        printf("\033[A\033[2K");
}

void deskripsiUrutan(int kolom, int arah)
{
    switch (kolom)
    {
    case 1:
        arah % 2 ? 
            strcpy(statusTabel[1], "Dari Id Terbesar.") : 
            strcpy(statusTabel[1], "Dari Id Terkecil.");
        break;
    case 2:
        arah % 2 ? 
            strcpy(statusTabel[1], "Dari Nama Terbesar.") : 
            strcpy(statusTabel[1], "Dari Nama Terkecil.");
        break;
    case 3:
        arah % 2 ? 
            strcpy(statusTabel[1], "Dari Stok Terbesar.") : 
            strcpy(statusTabel[1], "Dari Stok Terkecil.");
        break;
    case 4:
        arah % 2 ? 
            strcpy(statusTabel[1], "Dari Harga Terbesar.") : 
            strcpy(statusTabel[1], "Dari Harga Terkecil.");
        break;
    }
}

int kondisiUrutan(Barang barang, Barang pivot, int kolom, int arah)
{
    switch (kolom)
    {
    case 1:
        return arah % 2 ? 
            barang.id > pivot.id : barang.id < pivot.id;
    case 2:
        return arah % 2 ? 
            strcmp(barang.nama, pivot.nama) > 0 : strcmp(barang.nama, pivot.nama) < 0;
    case 3:
        return arah % 2 ? 
            barang.stok > pivot.stok : barang.stok < pivot.stok;
    case 4:
        return arah % 2 ? 
            barang.harga > pivot.harga : barang.harga < pivot.harga;
    }
}

void hurufKecil(char *stringAsli, char *stringSalinan)
{
    stringSalinan[0] = '\0';

    for (int i = 0; i < 255; i++)
    {
        if (stringAsli[i] == '\0')
        {
            stringSalinan[i] = '\0';
            break;
        }
        stringSalinan[i] = tolower(stringAsli[i]);
    }
}

void hapusSpasi(char *stringAsli)
{
    int indexPertama = 0;
    int indexTerakhir = strlen(stringAsli) - 1;

    while (isspace((unsigned char)stringAsli[indexPertama])) {
        indexPertama++;
    }

    while (indexTerakhir >= indexPertama && isspace((unsigned char)stringAsli[indexTerakhir])) {
        indexTerakhir--;
    }

    int i = 0;
    while (indexPertama <= indexTerakhir) {
        stringAsli[i++] = stringAsli[indexPertama++];
    }

    stringAsli[i] = '\0';
}