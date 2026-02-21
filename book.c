#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "book.h"
#include "utils.h"

Output addBooks(Node **firstNode) {
    Node *node;
    Output output;
    static Book book;
    char input[256];

    printf("--- ADD BOOKS ---\n");
    printf("Book Id: %d\n", bookCount(*firstNode) + 1);
    book.id = bookCount(*firstNode) + 1;

    if (!book.title || book.title[0] == '\0') {
        printf("Book Title: ");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputStr(input)) {
            snprintf(book.title, sizeof(book.title), "%s", input);
            output.exitMenu = false;
            return output;
        } else {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Title Name");
            return output;
        }
    } else {
        printf("Book Title: %s\n", book.title);
    }

    if (!book.author) {
        printf("Book Author: ");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputStr(input)) {
            snprintf(book.author, sizeof(book.author), "%s", input);
        } else {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Author Name");
            return output;
        }
    } else {
        printf("Book Author: %s\n", book.author);
    }

    if (!book.year) {
        printf("Book Publication Year: ");
    
        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputInt(input, 1000, 9999)) {
            book.year = numberStrToInt(input);
        } else {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");
            return output;
        }
    } else {
        printf("Book Publication Year: %d\n", book.year);
    }

    printf("Book Availability: ");

    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
        return output;
    }

    if (verifyInputStr(input))
        if (compareString(input, "true") == 0) {
            book.available = true;
        } else if (compareString(input, "false") == 0) {
            book.available = false;
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Invalid Availability Status");
        return output;
    }

    node = createNode();
    if (!node)
    {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Failed To Create Node");
        return output;
    }

    node->book = book;
    insertNode(firstNode, node);
    
    output.exitMenu = false;
    snprintf(output.notification, sizeof(output.notification), "Book Added Successfully");
    return output;
}

Output showBooks(Node *firstNode) {
    Output output;
    Node *currentNode;
    char input[256];
    static int currentPagination = 1;
    int minPagination, maxPagination;
    int totalPagination = (bookCount(firstNode) + 4) / 5;

    printf("--- SHOW BOOKS ---\n");
    printBook(firstNode, currentPagination);
    printPagination(currentPagination, totalPagination, &minPagination, &maxPagination);

    printf("Select Pagination: ");

    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        currentPagination = 1;
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
        return output;
    }

    if (verifyInputInt(input, minPagination, maxPagination) && numberStrToInt(input) != currentPagination) {
        currentPagination = numberStrToInt(input);
        output.exitMenu = false;
        return output;
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Pagination Not Found");
        return output;
    }
}