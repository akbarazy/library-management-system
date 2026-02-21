#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "book.h"
#include "utils.h"

Output addBooks(Node **firstNode) {
    Node *node = NULL;
    Output output = {0};
    static Book book = {0};
    char input[256] = "";

    printf("--- ADD BOOKS ---\n\n");
    printf("Book Id:\n%d\n\n", bookCount(*firstNode) + 1);
    book.id = bookCount(*firstNode) + 1;

    if (!book.title || book.title[0] == '\0') {
        printf("Book Title :\n");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            book = (Book) {0};
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
        printf("Book Title :\n%s\n\n", book.title);
    }

    if (!book.author || book.author[0] == '\0') {
        printf("Book Author :\n");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            book = (Book) {0};
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputStr(input)) {
            snprintf(book.author, sizeof(book.author), "%s", input);
            output.exitMenu = false;
            return output;
        } else {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Author Name");
            return output;
        }
    } else {
        printf("Book Author :\n%s\n\n", book.author);
    }

    if (!book.year) {
        printf("Book Year :\n");
    
        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            book = (Book) {0};
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputInt(input, 1000, 9999)) {
            book.year = numberStrToInt(input);
            output.exitMenu = false;
            return output;
        } else {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");
            return output;
        }
    } else {
        printf("Book Year :\n%d\n\n", book.year);
    }

    printf("Book Available :\n");
    printf("1. True\n2. False\n");
    printf("Select > ");

    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        book = (Book) {0};
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
        return output;
    }

    if (verifyInputInt(input, 1, 2)) {
        if (numberStrToInt(input) == 1) {
            book.available = true;
        } else if (numberStrToInt(input) == 2) {
            book.available = false;
        }
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Invalid Available Status");
        return output;
    }

    node = createNode();
    if (!node) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Failed To Create Node");
        return output;
    }

    node->book = book;
    insertNode(firstNode, node);
    book = (Book) {0};
    
    output.exitMenu = false;
    snprintf(output.notification, sizeof(output.notification), "Book Added Successfully");
    return output;
}

Output showBooks(Node *firstNode) {
    Output output = {0};
    Node *currentNode = NULL;
    char input[256] = "";
    static int currentPagination = 1;
    int minPagination = 0, maxPagination = 0;
    int totalPagination = (bookCount(firstNode) + 4) / 5;

    printf("--- SHOW BOOKS ---\n\n");
    printBook(firstNode, currentPagination);
    printPagination(currentPagination, totalPagination, &minPagination, &maxPagination);

    printf("Select > ");

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

    if (verifyInputInt(input, minPagination, maxPagination)) {
        currentPagination = numberStrToInt(input);
        output.exitMenu = false;
        return output;
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Pagination Not Found");
        return output;
    }
}