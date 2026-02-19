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

    printf("Book Title: ");

    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Add Book Cancelled");
        return output;
    }

    if (verifyInputStr(input)) {
        snprintf(book.title, sizeof(book.title), "%s", input);
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Invalid Title Name");
        return output;
    }

    printf("Book Author: ");

    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Add Book Cancelled");
        return output;
    }

    if (verifyInputStr(input)) {
        snprintf(book.author, sizeof(book.author), "%s", input);
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Invalid Author Name");
        return output;
    }

    printf("Book Publication Year: ");
    
    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Add Book Cancelled");
        return output;
    }

    if (verifyInputInt(input, 1000, 9999)) {
        book.publicationYear = numberStrToInt(input);
    } else {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");
        return output;
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
        snprintf(output.notification, sizeof(output.notification), "Add Book Cancelled");
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
    char input;
    int startIndex, endIndex;
    static int currentPagination = 1;
    int minPagination, maxPagination;
    int totalPagination = (bookCount(firstNode) + 4) / 5;

    printf("--- SHOW BOOKS ---\n");
    if (totalPagination <= 5) {
        minPagination = 1;
        maxPagination = totalPagination;
    } else {
        minPagination = currentPagination - 2;
        maxPagination = currentPagination + 2;

        if (minPagination < 1) {
            minPagination = 1;
            maxPagination = 5;
        }

        if (maxPagination > totalPagination) {
            maxPagination = totalPagination;
            minPagination = totalPagination - 4;
        }
    }

    currentNode = firstNode;
    startIndex = (currentPagination - 1) * 5;
    endIndex = startIndex + 4;
    for (size_t i = 0; i < endIndex + 1; i++) {
        if (i >= startIndex) {
            printf("Id              : %d\n", currentNode->book.id);
            printf("Title           : %s\n", currentNode->book.title);
            printf("Author          : %s\n", currentNode->book.author);
            printf("Publication Year: %d\n", currentNode->book.publicationYear);
            printf("Availability    : %s\n\n", currentNode->book.available ? "True" : "False");
        }
        currentNode = currentNode->next;
    }

    if (minPagination > 1) printf("<< ");

    for (size_t i = minPagination; i <= maxPagination; i++) {
        if (i == currentPagination) {
            printf("[%d] ", i);
        } else {
            printf("%d ", i);
        }
    }

    if (maxPagination < totalPagination) printf(">> ");
    printf("\n");

    printf("Select Pagination: ");
    input = getch();
    deleteLine(2);

    if (input == '/') {
        currentPagination = 1;
        output.exitMenu = true;
        snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
        return output;
    }

    // verifyInputInt hanya menerima string bukan char

    // if (verifyInputInt(input, minPagination, maxPagination) && input - '0' != currentPagination) {
    //     currentPagination = input - '0';
    //     output.exitMenu = false;
    //     return output;
    // } else {
    //     output.exitMenu = false;
    //     snprintf(output.notification, sizeof(output.notification), "Pagination Not Found");
    //     return output;
    // }
}