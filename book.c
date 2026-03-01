#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "book.h"
#include "utils.h"
#include "algorithm.h"

Output addBooks(Node **firstNode) {
    Output output = {0};
    Node *node = NULL;
    static Book book = {0};
    char input[256] = "";

    printf("--- ADD BOOKS ---\n\n");
    printf("Book Id :\n%d\n\n", bookCount(*firstNode) + 1);
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
    char input[256] = "";
    static int currentPagination = 1;
    int minPagination = 0, maxPagination = 0;
    int totalPagination = (bookCount(firstNode) + 4) / 5;

    printf("--- SHOW BOOKS ---\n\n");
    printPagination(firstNode, &minPagination, &maxPagination, currentPagination, totalPagination);

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

Output updateBooks(Node *firstNode) {
    Output output = {0};
    static Node *node = NULL;
    static Book book = {0};
    static bool skip[4] = {false, false, false, false};
    char input[256] = "";

    printf("--- UPDATE BOOKS ---\n\n");
    if (!book.id) {
        printf("Book Id :\n");
    
        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            if (node != NULL) {
                free(node);
                node = NULL;
            }

            book = (Book) {0};
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputInt(input, 1, bookCount(firstNode))) {
            book.id = numberStrToInt(input);
            node = linearSearchInt(firstNode, ID, book.id);
            if (node == NULL)
                snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");

            book = node->book;
            output.exitMenu = false;
            return output;
        } else {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");
            return output;
        }
    } else {
        printf("Book Id :\n%d\n\n", book.id);
    }

    if (compareString(book.title, node->book.title, FULL) && !skip[0]) {
        printf("Book Title : %s\n", node->book.title);

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

        if (input[0] == '\0') {
            skip[0] = true;
            output.exitMenu = false;
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

    if (compareString(book.author, node->book.author, FULL) && !skip[1]) {
        printf("Book Author : %s\n", node->book.author);

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

        if (input[0] == '\0') {
            skip[1] = true;
            output.exitMenu = false;
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

    if (book.year == node->book.year && !skip[2]) {
        printf("Book Year : %d\n", node->book.year);
    
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

        if (input[0] == '\0') {
            skip[2] = true;
            output.exitMenu = false;
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

    if (input[0] == '\0') {
        skip[3] = true;

        memset(skip, false, sizeof(skip));
        book = (Book) {0};
        node = NULL;
        
        output.exitMenu = false;
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
    memset(skip, false, sizeof(skip));
    book = (Book) {0};
    node = NULL;
    
    output.exitMenu = false;
    snprintf(output.notification, sizeof(output.notification), "Book Updated Successfully");
    return output;
}

Output deleteBooks(Node **firstNode) {
    Output output = {0};
    static Node *node = NULL;
    char input[256] = "";
    static int option = 0;

    printf("--- DELETE BOOKS ---\n\n");

    if (option == 0) {
        printf("1. Delete By Id\n2. Delete All\n");
        printf("Select > ");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            if (node != NULL) {
                free(node);
                node = NULL;
            }

            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputInt(input, 1, 2)) {
            option = numberStrToInt(input);
            output.exitMenu = false;
            return output;
        } else {
            input[0] = '\0';
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Delete Option");
            return output;
        }
    }

    switch (option) {
        case 1:
            if (node == NULL) {
                printf("Book Id :\n");
        
                if (!fgets(input, sizeof(input), stdin)) {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                    return output;
                }

                input[strcspn(input, "\n")] = '\0';

                if (input[0] == '/' && input[1] == '\0') {
                    deleteAllNode(&node);
                    option = 0;

                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputInt(input, 1, bookCount(*firstNode))) {
                    node = linearSearchInt(*firstNode, ID, numberStrToInt(input));
                    if (node == NULL)
                        snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");

                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");
                    return output;
                }
            } else {
                printBook(node);
                printf("1. Delete\n2. Cancel\n");
                printf("Select > ");
        
                if (!fgets(input, sizeof(input), stdin)) {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                    return output;
                }

                input[strcspn(input, "\n")] = '\0';

                if (input[0] == '/' && input[1] == '\0') {
                    option = 0;
                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputInt(input, 1, 2)) {
                    if (numberStrToInt(input) == 1) {
                        deleteNode(firstNode, node->book.id);
                        snprintf(output.notification, sizeof(output.notification), "Book Deleted Successfully");
                    }
                    node = NULL;
                    
                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Execute Option");
                    return output;
                }
            }
            break;

        case 2:
            deleteAllNode(firstNode);
            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "All Books Deleted Succesfully");
            return output;
    }
}

Output searchBooks(Node *firstNode) {
    Output output = {0};
    static Node *node = NULL;
    char input[256] = "";
    static int option = 0;
    static int currentPagination = 1;
    int minPagination = 0, maxPagination = 0, totalPagination;

    printf("--- DELETE BOOKS ---\n\n");

    if (option == 0) {
        printf("1. Search By Id\n");
        printf("2. Search By Title\n");
        printf("3. Search By Author\n");
        printf("4. Search By Year\n");
        printf("5. Search By Available\n");
        printf("Select > ");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            if (node != NULL) deleteAllNode(&node);

            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputInt(input, 1, 5)) {
            option = numberStrToInt(input);
            output.exitMenu = false;
            return output;
        } else {
            input[0] = '\0';
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Search Option");
            return output;
        }
    }

    if (node == NULL) {
        switch (option) {
            case 1:
                printf("Book Id :\n");
        
                if (!fgets(input, sizeof(input), stdin)) {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                    return output;
                }

                input[strcspn(input, "\n")] = '\0';

                if (input[0] == '/' && input[1] == '\0') {
                    option = 0;
                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputInt(input, 1, bookCount(firstNode))) {
                    node = linearSearchInt(firstNode, ID, numberStrToInt(input));
                    if (node == NULL)
                        snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");

                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");
                    return output;
                }
                break;

            case 2:
                printf("Book Title :\n");
        
                if (!fgets(input, sizeof(input), stdin)) {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                    return output;
                }

                input[strcspn(input, "\n")] = '\0';

                if (input[0] == '/' && input[1] == '\0') {
                    option = 0;
                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputStr(input)) {
                    node = linearSearchStr(firstNode, TITLE, input);
                    if (node == NULL)
                        snprintf(output.notification, sizeof(output.notification), "Invalid Title Name");

                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Title Name");
                    return output;
                }
                break;

            case 3:
                printf("Book Author :\n");
        
                if (!fgets(input, sizeof(input), stdin)) {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                    return output;
                }

                input[strcspn(input, "\n")] = '\0';

                if (input[0] == '/' && input[1] == '\0') {
                    option = 0;
                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputStr(input)) {
                    node = linearSearchStr(firstNode, AUTHOR, input);
                    if (node == NULL)
                        snprintf(output.notification, sizeof(output.notification), "Invalid Author Name");

                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Author Name");
                    return output;
                }
                break;

            case 4:
                printf("Book Year :\n");
        
                if (!fgets(input, sizeof(input), stdin)) {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                    return output;
                }

                input[strcspn(input, "\n")] = '\0';

                if (input[0] == '/' && input[1] == '\0') {
                    option = 0;
                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputInt(input, 1000, 9999)) {
                    node = linearSearchInt(firstNode, YEAR, numberStrToInt(input));
                    if (node == NULL)
                        snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");

                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");
                    return output;
                }
                break;

            case 5:
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
                    option = 0;
                    output.exitMenu = false;
                    return output;
                }

                if (verifyInputInt(input, 1, 2)) {
                    if (numberStrToInt(input) == 1) {
                        node = linearSearchInt(firstNode, AVAILABLE, true);
                    } else if (numberStrToInt(input) == 2) {
                        node = linearSearchInt(firstNode, AVAILABLE, false);
                    }
                    
                    if (node == NULL)
                        snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");

                    output.exitMenu = false;
                    return output;
                } else {
                    output.exitMenu = false;
                    snprintf(output.notification, sizeof(output.notification), "Invalid Publication Year");
                    return output;
                }
                break;
        }
    } else {
        if (option == 1) {
            printBook(node);
            printf("Book Id :\n");
        
            if (!fgets(input, sizeof(input), stdin)) {
                output.exitMenu = false;
                snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                return output;
            }

            input[strcspn(input, "\n")] = '\0';

            if (input[0] == '/' && input[1] == '\0') {
                deleteAllNode(&node);
                option = 0;

                output.exitMenu = false;
                return output;
            }

            if (verifyInputInt(input, 1, bookCount(firstNode))) {
                node = linearSearchInt(firstNode, ID, numberStrToInt(input));
                if (node == NULL)
                    snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");

                output.exitMenu = false;
                return output;
            } else {
                output.exitMenu = false;
                snprintf(output.notification, sizeof(output.notification), "Invalid Id Number");
                return output;
            }
        } else {
            totalPagination = (bookCount(node) + 4) / 5;
            printPagination(node, &minPagination, &maxPagination, currentPagination, totalPagination);

            if (!fgets(input, sizeof(input), stdin)) {
                output.exitMenu = false;
                snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
                return output;
            }

            input[strcspn(input, "\n")] = '\0';

            if (input[0] == '/' && input[1] == '\0') {
                deleteAllNode(&node);
                currentPagination = 1;

                output.exitMenu = false;
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
    }
}

Output sortBooks(Node **firstNode) {
    Output output = {0};
    char input[256] = "";
    static int option[2] = {0, 0};

    printf("--- SORT BOOKS ---\n\n");

    if (option[0] == 0) {
        printf("1. Sort By Id\n");
        printf("2. Sort By Title\n");
        printf("3. Sort By Author\n");
        printf("4. Sort By Year\n");
        printf("5. Sort By Available\n");
        printf("Select > ");

        if (!fgets(input, sizeof(input), stdin)) {
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
            return output;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '/' && input[1] == '\0') {
            memset(option, 0, sizeof(option));

            output.exitMenu = true;
            snprintf(output.notification, sizeof(output.notification), "Back To Main Menu");
            return output;
        }

        if (verifyInputInt(input, 1, 5)) {
            option[0] = numberStrToInt(input);
            output.exitMenu = false;
            return output;
        } else {
            input[0] = '\0';
            output.exitMenu = false;
            snprintf(output.notification, sizeof(output.notification), "Invalid Sort Option");
            return output;
        }
    }

    if (option[0] != 5) {
        printf("1. Sort By Ascending\n");
        printf("2. Sort By Descending\n");
    } else {
        printf("1. Sort By Available\n");
        printf("2. Sort By Not Available\n");
    }
    printf("Select > ");

    if (!fgets(input, sizeof(input), stdin)) {
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Input Error Occured");
        return output;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '/' && input[1] == '\0') {
        option[0] = 0;

        output.exitMenu = false;
        return output;
    }

    if (verifyInputInt(input, 1, 2)) {
        option[1] = numberStrToInt(input);
        mergeSort(firstNode, option[0], option[1]);
    } else {
        input[0] = '\0';
        output.exitMenu = false;
        snprintf(output.notification, sizeof(output.notification), "Invalid Sort Option");
        return output;
    }

    memset(option, 0, sizeof(option));

    output.exitMenu = true;
    snprintf(output.notification, sizeof(output.notification), "Books Sorted Succesfully");
    return output;
}