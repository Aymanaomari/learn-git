#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_ISBN_LENGTH 20
#define MAX_NAME_LENGTH 100
#define MAX_BORROWED_BOOKS 5

// Book structure
typedef struct {
    int bookId;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char isbn[MAX_ISBN_LENGTH];
    int year;
    int isAvailable;
    int borrowedByMemberId;
    time_t borrowDate;
    time_t dueDate;
} Book;

// Member structure
typedef struct {
    int memberId;
    char name[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    int borrowedCount;
    int borrowedBookIds[MAX_BORROWED_BOOKS];
} Member;

// Library structure
typedef struct {
    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    int bookCount;
    int memberCount;
} Library;

// Function prototypes
void initializeLibrary(Library* lib);
void displayMainMenu();
void displayBookMenu();
void displayMemberMenu();
void addBook(Library* lib);
void displayAllBooks(const Library* lib);
void searchBooks(const Library* lib);
void removeBook(Library* lib);
void addMember(Library* lib);
void displayAllMembers(const Library* lib);
void borrowBook(Library* lib);
void returnBook(Library* lib);
void displayBorrowedBooks(const Library* lib);
void displayMemberDetails(const Library* lib);
int getIntegerInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, size_t size);
void trimWhitespace(char* str);
void clearInputBuffer();
void pressEnterToContinue();

// Initialize library
void initializeLibrary(Library* lib) {
    lib->bookCount = 0;
    lib->memberCount = 0;
    
    // Add some sample books
    strcpy(lib->books[0].title, "The Great Gatsby");
    strcpy(lib->books[0].author, "F. Scott Fitzgerald");
    strcpy(lib->books[0].isbn, "978-0743273565");
    lib->books[0].year = 1925;
    lib->books[0].bookId = 1001;
    lib->books[0].isAvailable = 1;
    lib->books[0].borrowedByMemberId = -1;
    
    strcpy(lib->books[1].title, "To Kill a Mockingbird");
    strcpy(lib->books[1].author, "Harper Lee");
    strcpy(lib->books[1].isbn, "978-0061120084");
    lib->books[1].year = 1960;
    lib->books[1].bookId = 1002;
    lib->books[1].isAvailable = 1;
    lib->books[1].borrowedByMemberId = -1;
    
    strcpy(lib->books[2].title, "1984");
    strcpy(lib->books[2].author, "George Orwell");
    strcpy(lib->books[2].isbn, "978-0451524935");
    lib->books[2].year = 1949;
    lib->books[2].bookId = 1003;
    lib->books[2].isAvailable = 1;
    lib->books[2].borrowedByMemberId = -1;
    
    lib->bookCount = 3;
    
    // Add a sample member
    strcpy(lib->members[0].name, "John Smith");
    strcpy(lib->members[0].email, "john.smith@email.com");
    lib->members[0].memberId = 2001;
    lib->members[0].borrowedCount = 0;
    
    lib->memberCount = 1;
}

// Display main menu
void displayMainMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║       LIBRARY MANAGEMENT SYSTEM               ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1. Book Management                           ║\n");
    printf("║  2. Member Management                         ║\n");
    printf("║  3. Borrow Book                               ║\n");
    printf("║  4. Return Book                               ║\n");
    printf("║  5. Display All Borrowed Books                ║\n");
    printf("║  6. Exit                                      ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
}

// Display book menu
void displayBookMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║          BOOK MANAGEMENT MENU                 ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1. Add New Book                              ║\n");
    printf("║  2. Display All Books                         ║\n");
    printf("║  3. Search Books                              ║\n");
    printf("║  4. Remove Book                               ║\n");
    printf("║  5. Back to Main Menu                         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
}

// Display member menu
void displayMemberMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║         MEMBER MANAGEMENT MENU                ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1. Add New Member                            ║\n");
    printf("║  2. Display All Members                       ║\n");
    printf("║  3. Display Member Details                    ║\n");
    printf("║  4. Back to Main Menu                         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
}

// Trim whitespace from string
void trimWhitespace(char* str) {
    if (str == NULL) return;
    
    char* start = str;
    while (isspace((unsigned char)*start)) start++;
    
    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    
    size_t len = (end - start + 1);
    memmove(str, start, len);
    str[len] = '\0';
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Get integer input
int getIntegerInput(const char* prompt) {
    int value;
    char buffer[100];
    
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char* endptr;
            long result = strtol(buffer, &endptr, 10);
            
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                value = (int)result;
                return value;
            }
        }
        printf("✗ Invalid input! Please enter a valid number.\n");
    }
}

// Get string input
void getStringInput(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        trimWhitespace(buffer);
    }
}

// Press enter to continue
void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Add a new book
void addBook(Library* lib) {
    if (lib->bookCount >= MAX_BOOKS) {
        printf("✗ Library is full! Cannot add more books.\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║             ADD NEW BOOK                      ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    Book* book = &lib->books[lib->bookCount];
    
    getStringInput("Enter book title: ", book->title, MAX_TITLE_LENGTH);
    if (strlen(book->title) == 0) {
        printf("✗ Title cannot be empty!\n");
        return;
    }
    
    getStringInput("Enter author name: ", book->author, MAX_AUTHOR_LENGTH);
    if (strlen(book->author) == 0) {
        printf("✗ Author cannot be empty!\n");
        return;
    }
    
    getStringInput("Enter ISBN: ", book->isbn, MAX_ISBN_LENGTH);
    book->year = getIntegerInput("Enter publication year: ");
    
    book->bookId = 1001 + lib->bookCount;
    book->isAvailable = 1;
    book->borrowedByMemberId = -1;
    
    lib->bookCount++;
    
    printf("\n✓ Book added successfully!\n");
    printf("  Book ID: %d\n", book->bookId);
}

// Display all books
void displayAllBooks(const Library* lib) {
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              LIBRARY CATALOG                                  ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    
    if (lib->bookCount == 0) {
        printf("║  No books in the library.                                                     ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
        return;
    }
    
    for (int i = 0; i < lib->bookCount; i++) {
        const Book* book = &lib->books[i];
        printf("║ ID: %-4d │ %-30s │ %-20s │ %4d │ %-9s ║\n",
               book->bookId,
               book->title,
               book->author,
               book->year,
               book->isAvailable ? "Available" : "Borrowed");
    }
    
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total books: %d\n", lib->bookCount);
}

// Search books
void searchBooks(const Library* lib) {
    char searchTerm[100];
    int searchType;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║             SEARCH BOOKS                      ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1. Search by Title                           ║\n");
    printf("║  2. Search by Author                          ║\n");
    printf("║  3. Search by ISBN                            ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    searchType = getIntegerInput("Enter search type (1-3): ");
    
    if (searchType < 1 || searchType > 3) {
        printf("✗ Invalid search type!\n");
        return;
    }
    
    getStringInput("Enter search term: ", searchTerm, sizeof(searchTerm));
    
    if (strlen(searchTerm) == 0) {
        printf("✗ Search term cannot be empty!\n");
        return;
    }
    
    // Convert to lowercase for case-insensitive search
    for (int i = 0; searchTerm[i]; i++) {
        searchTerm[i] = tolower(searchTerm[i]);
    }
    
    printf("\nSearch Results:\n");
    printf("═══════════════════════════════════════════════════════════════════════════════════\n");
    
    int found = 0;
    for (int i = 0; i < lib->bookCount; i++) {
        const Book* book = &lib->books[i];
        char temp[MAX_TITLE_LENGTH];
        int match = 0;
        
        switch (searchType) {
            case 1: // Title
                strcpy(temp, book->title);
                for (int j = 0; temp[j]; j++) temp[j] = tolower(temp[j]);
                match = strstr(temp, searchTerm) != NULL;
                break;
            case 2: // Author
                strcpy(temp, book->author);
                for (int j = 0; temp[j]; j++) temp[j] = tolower(temp[j]);
                match = strstr(temp, searchTerm) != NULL;
                break;
            case 3: // ISBN
                match = strcmp(book->isbn, searchTerm) == 0;
                break;
        }
        
        if (match) {
            printf("ID: %d\n", book->bookId);
            printf("Title: %s\n", book->title);
            printf("Author: %s\n", book->author);
            printf("ISBN: %s\n", book->isbn);
            printf("Year: %d\n", book->year);
            printf("Status: %s\n", book->isAvailable ? "Available" : "Borrowed");
            printf("───────────────────────────────────────────────────────────────────────────────\n");
            found++;
        }
    }
    
    if (found == 0) {
        printf("No books found matching your search.\n");
    } else {
        printf("Found %d book(s).\n", found);
    }
}

// Remove book
void removeBook(Library* lib) {
    int bookId = getIntegerInput("\nEnter Book ID to remove: ");
    
    for (int i = 0; i < lib->bookCount; i++) {
        if (lib->books[i].bookId == bookId) {
            if (!lib->books[i].isAvailable) {
                printf("✗ Cannot remove book - it is currently borrowed!\n");
                return;
            }
            
            printf("Removing: %s by %s\n", lib->books[i].title, lib->books[i].author);
            
            // Shift remaining books
            for (int j = i; j < lib->bookCount - 1; j++) {
                lib->books[j] = lib->books[j + 1];
            }
            
            lib->bookCount--;
            printf("✓ Book removed successfully!\n");
            return;
        }
    }
    
    printf("✗ Book with ID %d not found!\n", bookId);
}

// Add a new member
void addMember(Library* lib) {
    if (lib->memberCount >= MAX_MEMBERS) {
        printf("✗ Maximum members reached!\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           ADD NEW MEMBER                      ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    Member* member = &lib->members[lib->memberCount];
    
    getStringInput("Enter member name: ", member->name, MAX_NAME_LENGTH);
    if (strlen(member->name) == 0) {
        printf("✗ Name cannot be empty!\n");
        return;
    }
    
    getStringInput("Enter email: ", member->email, MAX_NAME_LENGTH);
    
    member->memberId = 2001 + lib->memberCount;
    member->borrowedCount = 0;
    
    lib->memberCount++;
    
    printf("\n✓ Member added successfully!\n");
    printf("  Member ID: %d\n", member->memberId);
}

// Display all members
void displayAllMembers(const Library* lib) {
    printf("\n╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         LIBRARY MEMBERS                               ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════╣\n");
    
    if (lib->memberCount == 0) {
        printf("║  No members registered.                                               ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════╝\n");
        return;
    }
    
    for (int i = 0; i < lib->memberCount; i++) {
        const Member* member = &lib->members[i];
        printf("║ ID: %-4d │ %-30s │ Books Borrowed: %-2d           ║\n",
               member->memberId,
               member->name,
               member->borrowedCount);
    }
    
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total members: %d\n", lib->memberCount);
}

// Display member details
void displayMemberDetails(const Library* lib) {
    int memberId = getIntegerInput("\nEnter Member ID: ");
    
    for (int i = 0; i < lib->memberCount; i++) {
        if (lib->members[i].memberId == memberId) {
            const Member* member = &lib->members[i];
            
            printf("\n╔════════════════════════════════════════════════╗\n");
            printf("║          MEMBER DETAILS                       ║\n");
            printf("╠════════════════════════════════════════════════╣\n");
            printf("║ Member ID: %-35d║\n", member->memberId);
            printf("║ Name: %-40s║\n", member->name);
            printf("║ Email: %-39s║\n", member->email);
            printf("║ Books Borrowed: %-30d║\n", member->borrowedCount);
            printf("╚════════════════════════════════════════════════╝\n");
            
            if (member->borrowedCount > 0) {
                printf("\nBorrowed Books:\n");
                printf("───────────────────────────────────────────────────────────────\n");
                
                for (int j = 0; j < member->borrowedCount; j++) {
                    int bookId = member->borrowedBookIds[j];
                    
                    for (int k = 0; k < lib->bookCount; k++) {
                        if (lib->books[k].bookId == bookId) {
                            printf("%d. %s by %s (ID: %d)\n",
                                   j + 1,
                                   lib->books[k].title,
                                   lib->books[k].author,
                                   lib->books[k].bookId);
                            break;
                        }
                    }
                }
            }
            
            return;
        }
    }
    
    printf("✗ Member with ID %d not found!\n", memberId);
}

// Borrow a book
void borrowBook(Library* lib) {
    int memberId = getIntegerInput("\nEnter Member ID: ");
    int bookId = getIntegerInput("Enter Book ID: ");
    
    // Find member
    Member* member = NULL;
    for (int i = 0; i < lib->memberCount; i++) {
        if (lib->members[i].memberId == memberId) {
            member = &lib->members[i];
            break;
        }
    }
    
    if (member == NULL) {
        printf("✗ Member with ID %d not found!\n", memberId);
        return;
    }
    
    if (member->borrowedCount >= MAX_BORROWED_BOOKS) {
        printf("✗ Member has reached maximum borrowed books limit (%d)!\n", MAX_BORROWED_BOOKS);
        return;
    }
    
    // Find book
    Book* book = NULL;
    for (int i = 0; i < lib->bookCount; i++) {
        if (lib->books[i].bookId == bookId) {
            book = &lib->books[i];
            break;
        }
    }
    
    if (book == NULL) {
        printf("✗ Book with ID %d not found!\n", bookId);
        return;
    }
    
    if (!book->isAvailable) {
        printf("✗ Book is already borrowed!\n");
        return;
    }
    
    // Borrow the book
    book->isAvailable = 0;
    book->borrowedByMemberId = memberId;
    book->borrowDate = time(NULL);
    book->dueDate = book->borrowDate + (14 * 24 * 60 * 60); // 14 days
    
    member->borrowedBookIds[member->borrowedCount] = bookId;
    member->borrowedCount++;
    
    printf("\n✓ Book borrowed successfully!\n");
    printf("  Book: %s\n", book->title);
    printf("  Borrowed by: %s\n", member->name);
    
    char dueDateStr[26];
    struct tm* dueTm = localtime(&book->dueDate);
    strftime(dueDateStr, sizeof(dueDateStr), "%Y-%m-%d", dueTm);
    printf("  Due Date: %s\n", dueDateStr);
}

// Return a book
void returnBook(Library* lib) {
    int bookId = getIntegerInput("\nEnter Book ID to return: ");
    
    // Find book
    Book* book = NULL;
    for (int i = 0; i < lib->bookCount; i++) {
        if (lib->books[i].bookId == bookId) {
            book = &lib->books[i];
            break;
        }
    }
    
    if (book == NULL) {
        printf("✗ Book with ID %d not found!\n", bookId);
        return;
    }
    
    if (book->isAvailable) {
        printf("✗ Book is not currently borrowed!\n");
        return;
    }
    
    int memberId = book->borrowedByMemberId;
    
    // Find member and remove book from their list
    Member* member = NULL;
    for (int i = 0; i < lib->memberCount; i++) {
        if (lib->members[i].memberId == memberId) {
            member = &lib->members[i];
            
            // Remove book from member's borrowed list
            for (int j = 0; j < member->borrowedCount; j++) {
                if (member->borrowedBookIds[j] == bookId) {
                    for (int k = j; k < member->borrowedCount - 1; k++) {
                        member->borrowedBookIds[k] = member->borrowedBookIds[k + 1];
                    }
                    member->borrowedCount--;
                    break;
                }
            }
            break;
        }
    }
    
    // Check for late return
    time_t now = time(NULL);
    int daysLate = 0;
    if (now > book->dueDate) {
        daysLate = (int)((now - book->dueDate) / (24 * 60 * 60));
    }
    
    book->isAvailable = 1;
    book->borrowedByMemberId = -1;
    
    printf("\n✓ Book returned successfully!\n");
    printf("  Book: %s\n", book->title);
    if (member != NULL) {
        printf("  Returned by: %s\n", member->name);
    }
    
    if (daysLate > 0) {
        printf("\n⚠ LATE RETURN!\n");
        printf("  Days late: %d\n", daysLate);
        printf("  Fine: $%.2f (at $1.00 per day)\n", daysLate * 1.0);
    } else {
        printf("  ✓ Returned on time!\n");
    }
}

// Display all borrowed books
void displayBorrowedBooks(const Library* lib) {
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         CURRENTLY BORROWED BOOKS                              ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    
    int found = 0;
    for (int i = 0; i < lib->bookCount; i++) {
        if (!lib->books[i].isAvailable) {
            const Book* book = &lib->books[i];
            
            // Find member name
            const char* memberName = "Unknown";
            for (int j = 0; j < lib->memberCount; j++) {
                if (lib->members[j].memberId == book->borrowedByMemberId) {
                    memberName = lib->members[j].name;
                    break;
                }
            }
            
            char dueDateStr[26];
            struct tm* dueTm = localtime(&book->dueDate);
            strftime(dueDateStr, sizeof(dueDateStr), "%Y-%m-%d", dueTm);
            
            time_t now = time(NULL);
            const char* status = (now > book->dueDate) ? "OVERDUE" : "Active";
            
            printf("║ Book: %-35s │ ID: %-4d                         ║\n", book->title, book->bookId);
            printf("║ Borrowed by: %-30s │ Due: %-10s │ %-7s║\n", 
                   memberName, dueDateStr, status);
            printf("╟────────────────────────────────────────────────────────────────────────────────╢\n");
            found++;
        }
    }
    
    if (found == 0) {
        printf("║  No books currently borrowed.                                                  ║\n");
    }
    
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total borrowed books: %d\n", found);
}

// Main function
int main() {
    Library library;
    initializeLibrary(&library);
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║    Welcome to Library Management System!     ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    int running = 1;
    
    while (running) {
        displayMainMenu();
        int choice = getIntegerInput("Enter your choice (1-6): ");
        
        switch (choice) {
            case 1: { // Book Management
                int bookMenuRunning = 1;
                while (bookMenuRunning) {
                    displayBookMenu();
                    int bookChoice = getIntegerInput("Enter your choice (1-5): ");
                    
                    switch (bookChoice) {
                        case 1:
                            addBook(&library);
                            pressEnterToContinue();
                            break;
                        case 2:
                            displayAllBooks(&library);
                            pressEnterToContinue();
                            break;
                        case 3:
                            searchBooks(&library);
                            pressEnterToContinue();
                            break;
                        case 4:
                            removeBook(&library);
                            pressEnterToContinue();
                            break;
                        case 5:
                            bookMenuRunning = 0;
                            break;
                        default:
                            printf("✗ Invalid choice!\n");
                    }
                }
                break;
            }
            
            case 2: { // Member Management
                int memberMenuRunning = 1;
                while (memberMenuRunning) {
                    displayMemberMenu();
                    int memberChoice = getIntegerInput("Enter your choice (1-4): ");
                    
                    switch (memberChoice) {
                        case 1:
                            addMember(&library);
                            pressEnterToContinue();
                            break;
                        case 2:
                            displayAllMembers(&library);
                            pressEnterToContinue();
                            break;
                        case 3:
                            displayMemberDetails(&library);
                            pressEnterToContinue();
                            break;
                        case 4:
                            memberMenuRunning = 0;
                            break;
                        default:
                            printf("✗ Invalid choice!\n");
                    }
                }
                break;
            }
            
            case 3: // Borrow Book
                borrowBook(&library);
                pressEnterToContinue();
                break;
            
            case 4: // Return Book
                returnBook(&library);
                pressEnterToContinue();
                break;
            
            case 5: // Display Borrowed Books
                displayBorrowedBooks(&library);
                pressEnterToContinue();
                break;
            
            case 6: // Exit
                printf("\n╔════════════════════════════════════════════════╗\n");
                printf("║   Thank you for using our Library System!    ║\n");
                printf("║              Have a great day!                ║\n");
                printf("╚════════════════════════════════════════════════╝\n\n");
                running = 0;
                break;
            
            default:
                printf("✗ Invalid choice! Please select 1-6.\n");
        }
    }
    
    return 0;
}
