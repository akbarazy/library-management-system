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
    ADD = 1,
    SHOW,
    UPDATE,
    DELETE,
    SEARCH,
    SORT,
    QUIT
} Menu;

void menuDisplay(const char *notification)
{
    printf("===========================\n");
    printf(" LIBRARY MANAGEMENT SYSTEM \n");
    printf("===========================\n\n");

    printf("Total Of Books: 100\n\n");
    printf("1. Add Books\n");
    printf("2. Show Books\n");
    printf("3. Update Books\n");
    printf("4. Delete Books\n");
    printf("5. Search Books\n");
    printf("6. Sort Books\n");
    printf("7. Save & Quit\n\n");

    printf("Notification:\n%s\n\n", notification);
    printf("==============\n");
    printf("Select Menu: ");
}

int main()
{
    Node *firstNode = NULL;
    Menu selectedMenu = ADD;
    int fileStatus = loadData(&firstNode);
    char input, notification[256];
    bool isMenuChanged = false;

    strcpy(
        notification, 
        !fileStatus ? "Data Loaded Successfully" : "Data Load Failed"
    );

    while (selectedMenu != QUIT)
    {
        system("cls");
        printf("\n");

        menuDisplay(notification);
        input = getch();

        switch (input - '0')
        {
        case ADD:
            addBooks(&firstNode);
            break;
        // case SHOW:
        //     showBooks(firstNode);
        //     break;
        // case UPDATE:
        //     updateBook(&firstNode);
        //     break;
        // case DELETE:
        //     deleteBook(&firstNode);
        //     break;
        // case SEARCH:
        //     searchBook(firstNode);
        //     break;
        // case SORT:
        //     sortBooks(&firstNode);
        //     break;
        case QUIT:
            selectedMenu = QUIT;
            // saveData(&firstNode);
            printf("\n");
            break;
        default:
            strcpy(notification, "Invalid Menu Selection");
            break;
        }
    }

    return 0;
}