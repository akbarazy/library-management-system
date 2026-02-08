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

void headerDisplay();
void menuDisplay(Menu currentMenu);

int main()
{
    Node *firstNode;
    Menu currentMenu;
    Menu selectedMenu = TAMBAH;
    int fileStatus = loadData(&firstNode);
    char input, *notification;
    bool isMenuChanged = false;

    printf("ok");

    // if (firstNode->book.title)
    // {
    //     printf("lah kok ilang");
    // }

    // printf("%s", firstNode->book.title);

    return 0;
}

void headerDisplay() {}

void menuDisplay(Menu currentMenu)
{
    switch (currentMenu)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }
}