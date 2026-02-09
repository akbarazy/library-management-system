#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
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

void menuDisplay();

int main()
{
    Node *firstNode = NULL;
    Menu currentMenu, selectedMenu = TAMBAH;
    int fileStatus = loadData(&firstNode);
    char input, notification[256];
    bool isMenuChanged = false;

    printf("\n");
    menuDisplay();
    input = getch();

    return 0;
}

void menuDisplay()
{
    printf("===========================\n");
    printf(" LIBRARY MANAGEMENT SYSTEM \n");
    printf("===========================\n\n");

    printf("Total Books: 100\n\n");
    printf("1. Add Books\n");
    printf("2. Show Books\n");
    printf("3. Update Books\n");
    printf("4. Delete Books\n");
    printf("5. Search Books\n");
    printf("6. Sort Books\n");
    printf("7. Save & Quit\n\n");

    printf("==============\n");
    printf("Select Menu: ");
}