#include <stdio.h>
#include <stdlib.h>

struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {

    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;
    
    // Insert code here
    printf("Value of head: %p\n", (void*)head);
    printf("Address of head: %p\n", (void*)&head);
    printf("Address of iValue: %p\n", (void*)&(head->iValue));
    printf("Address of fValue: %p\n", (void*)&(head->fValue));
    printf("Address of next: %p\n", (void*)&(head->next));
    
    return 0;
}