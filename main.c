/* DSA MINI PROJECT- LIBRARY MANAGEMENT SYSTEM USING SINGLY LINKED LISTS
ANSHUL B A- 1RF22CS019*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define title_length 100
#define author_length 100
#define PASSWORD_LENGTH 100


struct Library
{
    int bookID;
    char title[title_length];
    char author[author_length];
    struct Library *link;
};

typedef struct Library library;

library *start = NULL; // Global variable for the head of the linked list

struct User
{
    int userID;
    char bookTitle[title_length];
    int borrowedBookID;
    struct User *link;
};

typedef struct User user;
user *head = NULL;

bool checkEmpty();
library *addBook();
void displayLibrary(char choice[10]);
void searchBook();
library *removeBook(int bookIDToBeRemoved);
void noBooks();
library *borrowBook();
library *returnBook();
void displayBorrowedList();
void adminMenu();

char adminPassword[PASSWORD_LENGTH] = "a";
library *addBook()
{
    /*
    library *book;
    book = (library *)malloc(sizeof(struct Library));
    if (book == NULL)
    {
        printf("\nWe have run out of memory!\n");
        exit(1);
    }
    printf("\nEnter Book ID:\t");
    scanf("%d", &book->bookID);
    printf("\nEnter the title of the book:\t");
    scanf(" %[^\n]s", book->title);
    printf("\nEnter the author name:\t");
    scanf(" %[^\n]s", book->author);
    book->link = NULL;

    // Update the linked list
    if (start == NULL)
    {
        // If the linked list is empty, set the start to the new book
        start = book;
    }
    else
    {
        // If the linked list is not empty, add the new book to the beginning
        book->link = start;
        start = book;
    }

    printf("\nBook successfully added to the library!\n");
    return book;
    */


    library *book, *temp;
    book = (library *)malloc(sizeof(struct Library));

    if (book == NULL)
    {
        printf("\nWe have run out of memory!\n");
        return NULL;
    }

    printf("\nEnter Book ID:\t");
    scanf("%d", &book->bookID);
    printf("\nEnter the title of the book:\t");
    scanf(" %[^\n]s", book->title);
    printf("\nEnter the author name:\t");
    scanf(" %[^\n]s", book->author);
    book->link = NULL;

    // Update the linked list
    if (start == NULL)
    {
        // If the linked list is empty, set the start to the new book
        start = book;
    }
    else
    {
        // Traverse to the end and add the new book
        temp = start;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = book;
    }

    printf("\nBook successfully added to the library!\n");
    return start;
}

void displayLibrary(char choice[10])
{
    library *book = start;
    int count = 0;

    if (checkEmpty() == true)
    {
        noBooks();
        return;
    }

    printf("\nThe books present in the library right now are:\n");
    while (book != NULL)
    {
        printf("\nBook ID: |%d|\t Book title: |%s|\t Author name: |%s|", book->bookID, book->title, book->author);
        book = book->link;
        count++;
    }

    if (strcmp(choice, "yes") == 0 || strcmp(choice, "y") == 0)
        printf("\nThe number of books in the library is: %d\n", count);

    return;
}

void searchBook()
{
    library *book = start;
    int requiredBookID;
    if (checkEmpty() == true)
    {
        noBooks();
        return;
    }
    printf("\nEnter the ID of the book to be searched and displayed:\t");
    scanf("%d", &requiredBookID);

    while (book != NULL && book->bookID != requiredBookID)
    {
        book = book->link;
    }

    if (book != NULL && book->bookID == requiredBookID)
    {
        printf("\nThe book is present in the library!");
        printf("\nBook ID: |%d|\t Book title: |%s|\t Author name: |%s|", book->bookID, book->title, book->author);
    }
    else
    {
        printf("\nBook is not present in library!\n");
    }
}

library *removeBook(int bookIDToBeRemoved)
{


    if (checkEmpty() == true)
    {
        noBooks();
        return start;
    }
    library *currentBook = start;
    library *previousBook = NULL;


    while (currentBook != NULL && currentBook->bookID != bookIDToBeRemoved)  // traversing the library to find the required book
    {
        previousBook = currentBook;
        currentBook = currentBook->link;

    }

    if (currentBook != NULL && currentBook->bookID == bookIDToBeRemoved)
    {
        if (previousBook == NULL)
        {
            start = currentBook->link;                                    // first book
        }
        else
        {
            // If the book to be removed is not the first node
            previousBook->link = currentBook->link;
        }

        free(currentBook);
        printf("\nBook with ID %d removed successfully!\n", bookIDToBeRemoved);
    }
    else
    {
        printf("\nBook with ID %d not found or borrowed.\n", bookIDToBeRemoved);
    }

    return start;


}


void noBooks()
{
    printf("\nNo books in the library!\n");
}

bool checkEmpty()
{
    return (start == NULL);
}

library *borrowBook()
{
    int bookIDToBeBorrowed;
    user *borrowedBook;
    if (checkEmpty() == true)
    {
        noBooks();
        return start;
    }

    printf("\nEnter the ID of the book to be borrowed: ");
    scanf("%d", &bookIDToBeBorrowed);

    // Search for the book in the library
    library *bookToBeBorrowed = start;
    while (bookToBeBorrowed != NULL && bookToBeBorrowed->bookID != bookIDToBeBorrowed)
    {
        bookToBeBorrowed = bookToBeBorrowed->link;
    }

    if (bookToBeBorrowed != NULL && bookToBeBorrowed->bookID == bookIDToBeBorrowed)
    {
        // Book found, create a record in the user's borrowed book list
        borrowedBook = (user *)malloc(sizeof(struct User));

        printf("Enter your user ID:\t");
        scanf("%d",&borrowedBook->userID);
        strcpy(borrowedBook->bookTitle, bookToBeBorrowed->title);
        borrowedBook->borrowedBookID= bookToBeBorrowed->bookID;

        borrowedBook->link = head;
        head = borrowedBook;

        // Remove the borrowed book from the library
        start = removeBook(bookToBeBorrowed->bookID);
        printf("\nBook with ID %d borrowed successfully!\n", bookToBeBorrowed->bookID);
    }
    else
    {
        printf("\nBook with ID %d not found in the library.\n", bookIDToBeBorrowed);
    }

    return start;
}


/*library *returnBook()
{
    int bookIDToBeReturned;
    user *returnedBook;
    if (start == NULL)
    {
        noBooks();
        return start;
    }

    printf("\nEnter the ID of the book to be returned: ");
    scanf("%d", &bookIDToBeReturned);

    // Search for the book in the user's borrowed book list
    returnedBook = head;
    user *previousBook = NULL;
    while (returnedBook != NULL && returnedBook->borrowedBookID != bookIDToBeReturned)
    {
        previousBook = returnedBook;
        returnedBook = returnedBook->link;
    }

    if (returnedBook != NULL && returnedBook->bookTitle == bookIDToBeReturned)
    {
        // Book found, createing a record in the library
        library *returnedLibraryBook = (library *)malloc(sizeof(struct Library));
        returnedLibraryBook->bookID = returnedBook->borrowedBookID;
        strcpy(returnedLibraryBook->title, returnedBook->bookTitle);
        returnedLibraryBook->link = NULL;
        //start = returnedLibraryBook;
        if (start == NULL)
    {
        // If the linked list is empty, set the start to the new book
        start = returnedLibraryBook;
    }
    else
    {
        // Traverse to the end and add the new book
        library *temp = start;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = returnedLibraryBook;
    }



        // Remove the returned book from the user's borrowed book list
        if (previousBook == NULL)
        {
            // If the book to be returned is the first node
            head = returnedBook->link;
        }
        else
        {
            // If the book to be returned is not the first node
            previousBook->link = returnedBook->link;
        }

        free(returnedBook);
        printf("\nBook with ID %d returned successfully!\n", bookIDToBeReturned);
    }
    else
    {
        printf("\nBook with ID %d not found in the user's borrowed list.\n", bookIDToBeReturned);
    }

    return start;

}*/

library *returnBook()
{
    int bookIDToBeReturned;
    user *returnedBook;
    if (head == NULL)
    {
        noBooks();
        return start;
    }

    printf("\nEnter the ID of the book to be returned: ");
    scanf("%d", &bookIDToBeReturned);

    // Search for the book in the user's borrowed book list
    returnedBook = head;
    user *previousBook = NULL;
    while (returnedBook != NULL && returnedBook->borrowedBookID != bookIDToBeReturned)
    {
        previousBook = returnedBook;
        returnedBook = returnedBook->link;
    }

    if (returnedBook != NULL && returnedBook->borrowedBookID == bookIDToBeReturned)
    {
        // Book found, creating record in library SLL
        library *returnedLibraryBook = (library *)malloc(sizeof(struct Library));
        returnedLibraryBook->bookID = returnedBook->borrowedBookID;
        strcpy(returnedLibraryBook->title, returnedBook->bookTitle);
        returnedLibraryBook->link = NULL;

        // Add the returned book to the library
        if (start == NULL)
        {
            // If the linked list is empty, set the start to the new book
            start = returnedLibraryBook;
        }
        else
        {
            // Traverse to the end and add the new book
            library *temp = start;
            while (temp->link != NULL)
            {
                temp = temp->link;
            }
            temp->link = returnedLibraryBook;
        }

        // Remove the returned book from the user's borrowed book list
        if (previousBook == NULL)
        {
            // If the book to be returned is the first node
            head = returnedBook->link;
        }
        else
        {
            // If the book to be returned is not the first node
            previousBook->link = returnedBook->link;
        }

        free(returnedBook);
        printf("\nBook with ID %d returned successfully!\n", returnedBook->borrowedBookID);
    }
    else
    {
        printf("\nBook with ID %d not found in the user's borrowed list.\n", bookIDToBeReturned);
    }

    return start;
}
void displayBorrowedList()
{
    user *borrowedBook = head;
    int count = 0;

    if (borrowedBook == NULL)
    {
        printf("\nNo books borrowed by users!\n");
        return;
    }

    printf("\nThe books borrowed by users are:\n");
    while (borrowedBook != NULL)
    {
        printf("\nUser ID: |%d|\t Book Borrowed: |%s|\t Book ID: |%d|", borrowedBook->userID, borrowedBook->bookTitle, borrowedBook->borrowedBookID);
        borrowedBook = borrowedBook->link;
        count++;
    }

    printf("\nThe number of books borrowed by users is: %d\n", count);
}
void adminMenu()
{
    char enteredPassword[PASSWORD_LENGTH];
    printf("\nEnter the administrator password: ");
    scanf("%s",enteredPassword);

    if (strcmp(enteredPassword, adminPassword) != 0)
    {
        printf("\nIncorrect password. Access denied.\n");
        return;
    }

    int choice;
    do
    {
        printf("\nAdministrator Menu\n");
        printf("1. Add book\n");
        printf("2. Delete book\n");
        printf("3. Display library\n");
        printf("4. Display the borrowed book list \n");
        printf("5. Search for a single book \n");
        printf("6. Back to login page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            printf("\nEnter the Book ID to be deleted: ");
            int bookIDToDelete;
            scanf("%d", &bookIDToDelete);
            start = removeBook(bookIDToDelete);
            break;
        case 3:
            displayLibrary("yes");
            break;
        case 4:
            displayBorrowedList();
            break;
        case 5: searchBook();
            break;
        case 6:
            printf("\nLogging out from Admin section.\n");
            break;
        default:
            printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);
}


int main()
{

    int choice;
    do
    {
        printf("\nLogin Page\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Administrator section
            adminMenu();
            break;

        case 2:
            // User section
            do
            {
                printf("\nUser Menu\n");
                printf("1. Display library\n");
                printf("2. Borrow book\n");
                printf("3. Return book\n");
                printf("4. Search for a single book \n");
                printf("5. Back to login page\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    displayLibrary("no");
                    break;
                case 2:
                    borrowBook();
                    break;
                case 3:
                    returnBook();
                    break;
                case 4: searchBook();
                    break;
                case 5:
                    printf("\nLogging out from User section.\n");
                    break;
                default:
                    printf("\nInvalid choice. Please enter a valid option.\n");
                }
            } while (choice != 5);
            break;

        case 3:
            printf("\nThank you for using our library!\n");
            break;

        default:
            printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;

}
