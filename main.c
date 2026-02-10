#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "file_handler.h"
#include "book.h"
#include "algorithm.h"
#include "utils.h"

typedef enum {
    DEFAULT,
    ADD,
    SHOW,
    UPDATE,
    DELETE,
    SEARCH,
    SORT,
    QUIT
} Menu;

void menuDisplay() {
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
}

int main() {
    Output output = NULL;
    Node *firstNode = NULL;
    Menu selectedMenu = DEFAULT;
    char notification[256];
    int input;

    if (!loadData(&firstNode)) {
        strcpy(
            notification, 
            "Data Loaded Successfully"
        );
    } else {
        strcpy(
            notification, 
            "Data Load Failed"
        );
    }

    while (selectedMenu != QUIT) {
        system("cls");

        printf("\n");
        menuDisplay();

        if (strlen(notification) > 0) {
            printf("Notification:\n%s\n\n", notification);
            memset(notification, 0, sizeof(notification));
        }

        if (selectedMenu == DEFAULT) {
            printf("==============\n");
            printf("Select Menu: ");

            input = getch();
            if (!verifyInputInt(input, 1, 7)) continue;

            deleteLines(2);
        }

        switch (input) {
            case ADD:
                if (selectedMenu == ADD) {
                    output = addBooks(&firstNode);

                    strcpy(notification, output.notification);
                    if (output.completed) selectedMenu = DEFAULT;
                } else {
                    selectedMenu = ADD;
                }
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
                // saveData(&firstNode);
                selectedMenu = QUIT;
                printf("\n");
                break;
            default:
                strcpy(notification, "Invalid Menu Selection");
                break;
        }
    }

    return 0;
}