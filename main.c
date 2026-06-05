#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 150

// Structure to hold customer information
typedef struct {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int loyaltyPoints;
    int customerId;
} Customer;

// Function to trim whitespace from string
void trimWhitespace(char* str) {
    if (str == NULL) return;
    
    // Trim leading whitespace
    char* start = str;
    while (isspace((unsigned char)*start)) start++;
    
    // Trim trailing whitespace
    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    
    // Write trimmed string
    size_t len = (end - start + 1);
    memmove(str, start, len);
    str[len] = '\0';
}

// Function to get string input with validation
int getStringInput(const char* prompt, char* buffer, size_t bufferSize) {
    printf("%s", prompt);
    if (fgets(buffer, bufferSize, stdin) == NULL) {
        return 0;
    }
    
    // Remove newline character
    buffer[strcspn(buffer, "\n")] = '\0';
    trimWhitespace(buffer);
    
    return strlen(buffer) > 0;
}

// Function to get integer input with validation
int getIntegerInput(const char* prompt, int* value) {
    char buffer[50];
    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    char* endptr;
    long result = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\n') {
        return 0; // Invalid input
    }
    
    *value = (int)result;
    return 1;
}

// Function to greet customer
void greetCustomer(const Customer* customer) {
    if (customer == NULL) {
        fprintf(stderr, "Customer cannot be NULL\n");
        return;
    }
    
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║     Welcome to Our Service!           ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("Hello, %s!\n", customer->name);
    printf("Customer ID: #%d\n", customer->customerId);
    printf("Loyalty Points: %d\n", customer->loyaltyPoints);
    if (strlen(customer->email) > 0) {
        printf("Email: %s\n", customer->email);
    }
    printf("\n");
}

// Function to display customer menu
void displayMenu() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║         Customer Service Menu         ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ 1. View Profile                       ║\n");
    printf("║ 2. Add Loyalty Points                 ║\n");
    printf("║ 3. Update Email                       ║\n");
    printf("║ 4. Display Summary                    ║\n");
    printf("║ 5. Exit                               ║\n");
    printf("╚════════════════════════════════════════╝\n");
}

// Function to add loyalty points
void addLoyaltyPoints(Customer* customer) {
    int points;
    if (getIntegerInput("Enter points to add: ", &points)) {
        if (points > 0) {
            customer->loyaltyPoints += points;
            printf("✓ Successfully added %d points!\n", points);
            printf("New balance: %d points\n", customer->loyaltyPoints);
        } else {
            printf("✗ Points must be positive!\n");
        }
    } else {
        printf("✗ Invalid input!\n");
    }
}

// Function to update email
void updateEmail(Customer* customer) {
    char newEmail[MAX_EMAIL_LENGTH];
    if (getStringInput("Enter new email address: ", newEmail, sizeof(newEmail))) {
        // Basic email validation
        if (strchr(newEmail, '@') != NULL && strchr(newEmail, '.') != NULL) {
            strncpy(customer->email, newEmail, MAX_EMAIL_LENGTH - 1);
            customer->email[MAX_EMAIL_LENGTH - 1] = '\0';
            printf("✓ Email updated successfully!\n");
        } else {
            printf("✗ Invalid email format!\n");
        }
    }
}

// Function to display customer summary
void displaySummary(const Customer* customer) {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║        Customer Summary Report        ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ Name: %-32s║\n", customer->name);
    printf("║ ID: #%-33d║\n", customer->customerId);
    printf("║ Email: %-31s║\n", 
           strlen(customer->email) > 0 ? customer->email : "Not provided");
    printf("║ Loyalty Points: %-22d║\n", customer->loyaltyPoints);
    
    // Calculate membership tier
    const char* tier;
    if (customer->loyaltyPoints >= 1000) {
        tier = "PLATINUM";
    } else if (customer->loyaltyPoints >= 500) {
        tier = "GOLD";
    } else if (customer->loyaltyPoints >= 100) {
        tier = "SILVER";
    } else {
        tier = "BRONZE";
    }
    printf("║ Membership Tier: %-20s║\n", tier);
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
}

// Initialize customer
void initializeCustomer(Customer* customer) {
    static int nextId = 1000;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║       Customer Registration           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    // Get name
    while (!getStringInput("Enter your name: ", customer->name, sizeof(customer->name))) {
        printf("✗ Name cannot be empty. Please try again.\n");
    }
    
    // Get email (optional)
    printf("Enter your email (or press Enter to skip): ");
    if (!getStringInput("", customer->email, sizeof(customer->email))) {
        customer->email[0] = '\0';
    }
    
    customer->customerId = nextId++;
    customer->loyaltyPoints = 0;
    
    printf("\n✓ Registration successful!\n");
}

int main() {
    Customer customer = {0};
    int choice;
    int running = 1;
    
    // Initialize customer
    initializeCustomer(&customer);
    
    // Greet customer
    greetCustomer(&customer);
    
    // Main menu loop
    while (running) {
        displayMenu();
        
        if (!getIntegerInput("Enter your choice (1-5): ", &choice)) {
            printf("✗ Invalid input! Please enter a number.\n");
            continue;
        }
        
        switch (choice) {
            case 1:
                greetCustomer(&customer);
                break;
            case 2:
                addLoyaltyPoints(&customer);
                break;
            case 3:
                updateEmail(&customer);
                break;
            case 4:
                displaySummary(&customer);
                break;
            case 5:
                printf("\n");
                printf("╔════════════════════════════════════════╗\n");
                printf("║   Thank you for using our service!    ║\n");
                printf("║         Have a great day, %-12s║\n", customer.name);
                printf("╚════════════════════════════════════════╝\n");
                running = 0;
                break;
            default:
                printf("✗ Invalid choice! Please select 1-5.\n");
        }
    }
    
    return 0;
}