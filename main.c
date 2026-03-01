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
                    
                    if (output.exitMenu) {
                        selectedMenu = DEFAULT;
                    }
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
                        snprintf(notification, sizeof(notification), "No Books Found");
                    }
                }
                break;

            case UPDATE:
                if (selectedMenu == UPDATE) {
                    output = updateBooks(firstNode);

                    if (output.notification[0] != '\0')
                        snprintf(notification, sizeof(notification), "%s", output.notification);
                    
                    if (output.exitMenu) selectedMenu = DEFAULT;
                } else {
                    if (bookCount(firstNode) > 0) {
                        selectedMenu = UPDATE;
                    } else {
                        snprintf(notification, sizeof(notification), "No Books Found");
                    }
                }
                break;

            case DELETE:
                if (selectedMenu == DELETE) {
                    output = deleteBooks(&firstNode);

                    if (output.notification[0] != '\0')
                        snprintf(notification, sizeof(notification), "%s", output.notification);
                    
                    if (output.exitMenu) selectedMenu = DEFAULT;
                } else {
                    if (bookCount(firstNode) > 0) {
                        selectedMenu = DELETE;
                    } else {
                        snprintf(notification, sizeof(notification), "No Books Found");
                    }
                }
                break;

            case SEARCH:
                if (selectedMenu == SEARCH) {
                    output = searchBooks(firstNode);

                    if (output.notification[0] != '\0')
                        snprintf(notification, sizeof(notification), "%s", output.notification);
                    
                    if (output.exitMenu) selectedMenu = DEFAULT;
                } else {
                    if (bookCount(firstNode) > 0) {
                        selectedMenu = SEARCH;
                    } else {
                        snprintf(notification, sizeof(notification), "No Books Found");
                    }
                }
                break;

            case SORT:
                if (selectedMenu == SORT) {
                    output = sortBooks(&firstNode);

                    if (output.notification[0] != '\0')
                        snprintf(notification, sizeof(notification), "%s", output.notification);
                    
                    if (output.exitMenu) selectedMenu = DEFAULT;
                } else {
                    if (bookCount(firstNode) > 0) {
                        selectedMenu = SORT;
                    } else {
                        snprintf(notification, sizeof(notification), "No Books Found");
                    }
                }
                break;

            case QUIT:
                saveData(&firstNode);
                selectedMenu = QUIT;
                break;

            default:
                snprintf(notification, sizeof(notification), "Invalid Menu Selection");
                break;
        }
    }

    return 0;
}