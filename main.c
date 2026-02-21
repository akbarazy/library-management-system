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

void menuDisplay(int bookCount) {
    printf("===========================\n");
    printf(" LIBRARY MANAGEMENT SYSTEM \n");
    printf("===========================\n\n");

    printf("Total Of Books : %d\n\n", bookCount);
    printf("1. Add Books\n");
    printf("2. Show Books\n");
    printf("3. Update Books\n");
    printf("4. Delete Books\n");
    printf("5. Search Books\n");
    printf("6. Sort Books\n");
    printf("7. Save & Quit\n\n");
}

int main() {
    Output output = {0};
    Node *firstNode = NULL;
    Menu selectedMenu = DEFAULT;
    char input[256] = "", notification[256] = "";

    if (loadData(&firstNode)) {
        snprintf(notification, sizeof(notification), "Data Loaded Successfully");
    } else {
        snprintf(notification, sizeof(notification), "Data Load Failed");
    }

    while (selectedMenu != QUIT) {
        system("cls");

        printf("\n");
        menuDisplay(bookCount(firstNode));

        if (notification[0] != '\0') {
            printf("Notification :\n%s\n\n", notification);
            snprintf(notification, sizeof(notification), "");
        }

        if (selectedMenu == DEFAULT) {
            printf("==========\n");
            printf("Select > ");

            if (!fgets(input, sizeof(input), stdin)) {
                snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                continue;
            }

            input[strcspn(input, "\n")] = '\0';
            if (!verifyInputInt(input, ADD, QUIT))
                snprintf(input, sizeof(input), "0");
        }

        switch (numberStrToInt(input)) {
            case ADD:
                if (selectedMenu == ADD) {
                    output = addBooks(&firstNode);

                    if (output.notification[0] != '\0')
                        snprintf(notification, sizeof(notification), "%s", output.notification);
                    
                    if (output.exitMenu) selectedMenu = DEFAULT;
                } else {
                    selectedMenu = ADD;
                }
                break;

            case SHOW:
                if (selectedMenu == SHOW) {
                    output = showBooks(firstNode);

                    if (output.notification[0] != '\0')
                        snprintf(notification, sizeof(notification), "%s", output.notification);
                    
                    if (output.exitMenu) selectedMenu = DEFAULT;
                } else {
                    if (bookCount(firstNode) > 0) {
                        selectedMenu = SHOW;
                    } else {
                        snprintf(output.notification, sizeof(output.notification), "No Books Found");
                    }
                }
                break;
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
                snprintf(notification, sizeof(notification), "Invalid Menu Selection");
                break;
        }
    }

    return 0;
}