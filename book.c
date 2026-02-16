#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book.h"
#include "utils.h"

Output addBooks(Node **firstNode, Book *tempInput) {
    Node *node;
    Output output;
    char input[256];

    printf("--- ADD BOOKS ---\n");
    printf("Book Id: %d\n", bookCount(*firstNode) + 1);
    tempInput->id = bookCount(*firstNode) + 1;

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
        snprintf(tempInput->title, sizeof(tempInput->title), "%s", input);
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
        snprintf(tempInput->author, sizeof(tempInput->author), "%s", input);
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
        tempInput->publicationYear = numberStrToInt(input);
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
            tempInput->available = true;
        } else if (compareString(input, "false") == 0) {
            tempInput->available = false;
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

    node->book = *tempInput;
    insertNode(firstNode, node);
    
    output.exitMenu = false;
    snprintf(output.notification, sizeof(output.notification), "Book Added Successfully");
    return output;
}