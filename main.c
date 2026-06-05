#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void greetCustomer(const char* name) {
    printf("Hello, Customer!\n");
    if (name == NULL) {
        fprintf(stderr, "Name cannot be NULL\n");
        return;
    }
    printf("Welcome, %s!\n", name);
}


int main(){
    
    printf("Please enter your name: ");
    char *customerName = malloc(100 * sizeof(char));
    if (customerName == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    scanf("%s", customerName);
    greetCustomer(customerName);

    free(customerName);
    return 0;
}