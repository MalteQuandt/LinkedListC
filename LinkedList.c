#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int appendItem(char* label);
void printList();
struct list_item* findItem(int id);
void deleteItem(int id);
void deleteList();

typedef struct list_item{
    // The id for the list item.
    int id;
	
    // The label for the list item.
    char label[16];

    // The pointer to the next item in the single linked list.
    struct list_item *next;
} list_item;

int globalId = 1;
list_item *back = NULL;
list_item *front = NULL;

int appendItem(char *label) {
    list_item *temp = NULL;
    int id = globalId++;
    
    if(front == NULL) {
        front = (list_item *) malloc(sizeof(list_item));
        front->id = id;
        front->next = NULL;
        strcpy(front->label, label);
        back = front;
    } else {
        // Allocation and declaration of the list item at the temporary pointer temp.
        temp = (list_item *) malloc(sizeof(list_item));
        temp->id = id;
        temp->next = NULL;
        strcpy(temp->label, label);
        
        back->next = temp;
        back = temp;
        temp = NULL;
    }
    return id;
}

void printList() {
    int position = 0;
    list_item *itrVar = front;
    if(itrVar == NULL) {
        printf("The list is empty!\n");
    } else {
        while(itrVar != NULL)
        {
            printf("%d ", position++);
            printf("ID: %d\n", itrVar->id);
            printf("Label: %s\n", itrVar->label);
            itrVar = itrVar->next;
        } 
    }
    itrVar = NULL;
}

struct list_item* findItem(int id) {
    list_item *itrVar = front;
    while(itrVar != NULL) {
        if(itrVar->id == id) {
               return itrVar;
        } else {
            itrVar = itrVar->next;
        }
    }
    return NULL;
    
}
void deleteList() {
    // Initializing the variables used for the iteration and the deletion.
    list_item *itrVar = front;
    list_item *freeVar = NULL;
    
    while(itrVar != NULL){
        freeVar = itrVar; 
        itrVar = itrVar->next;
        free(freeVar);
    };
    // Sets the pointers front and back to point to nothing as the final step.
    back = NULL;
    front= NULL;
}

void deleteItem(int id) {
    list_item *temp = NULL, *itrVar = NULL;
    // If the id is not existing or 
    if(front == NULL || id > globalId || id < front->id) {
        // end the function.
        return;
    // If the id is in the front.
    } else if(front->id == id) {
        temp = front;
        front = front->next;
        free(temp);
        
    // If the id is in the back.
    } else if(back->id == id) {
        itrVar = front;
        while(itrVar->next != NULL) {
            temp = itrVar;
            itrVar = itrVar->next;
        }
        back = temp;
        temp->next = NULL;
        free(itrVar);
     // If the id is somewhere between front and back.  
    } else {
        itrVar = front;
        while(itrVar->id != id) {
            temp = itrVar;
            itrVar = itrVar->next;
        }
        temp->next = itrVar->next;
        free(itrVar);
    }
    temp = NULL;
    itrVar = NULL;
}
