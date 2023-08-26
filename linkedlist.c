#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

//list input buffer max
#define MAX_LEN 100

//node struct
struct Node{
    int data;
    struct Node* next;
};

//list struct
struct List{
    struct Node* head;
};


struct List* list_create(){
    struct List* list = malloc(sizeof(struct List));
    list->head = NULL;

    return list;
}

void list_insert_end(struct List* list, int val){

    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL){
        return;
    }

    new_node->data = val;
    new_node->next = NULL;

    //if the list is empty, set the head of the list to the new_node
    if(list->head == NULL){
        list->head = new_node;
        return;
    }

    //traverse to the last node in the list
    struct Node* current = list->head;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = new_node;
}

void insert_list_front(struct List* list, int val){
    struct Node* new_node = malloc(sizeof(struct Node));

    new_node->data = val;
    new_node->next = list->head;

    list->head = new_node;
    
    return;
}

void print_list(struct List* list){
    struct Node* current = list->head;

    printf("List contents: ");

    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    return;
}

void list_free(struct List* list){
    struct Node* current;
    current = list->head;
    
    while(current != NULL){
        free(current);
        current = current->next;
    }

    free(list);

    return;
}

int io_err_check(int input){
    if(input > 4 || input < 1){
        return 1;
    }
    return 0;
}

void add_user_nodes(struct List* list){
    printf("Enter values separated by space: ");
    
    char input[MAX_LEN]; // input buffer
    fgets(input, sizeof(input), stdin);

    int length = strlen(input);

    // Remove newline character from the input
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    char* token = strtok(input, " ");
    while (token != NULL) {
        int val = atoi(token); // Convert token to integer
        list_insert_end(list, val); // Add the value to the linked list
        token = strtok(NULL, " ");
    }
}

int val_search(struct List* list, int val){
    //return 1 if value is in list, 0 if not
    struct Node* current = list->head;

    while(current != NULL){
        if(val == current->data){
            return 1;
        }
        current = current->next;
    }
    return 0; //value not in list
}

void list_remove(struct List* list) {
    if(list->head == NULL){
        system("cls");
        printf("No nodes to remove!");
        sleep(1);
        return;
    }
    else{
        int input;
        int flag = 0;

        while (1) {
            system("cls");
            fflush(stdin);
            print_list(list);
            printf("Enter value you want to remove: ");
            scanf("%d", &input);

            //search list (to check if input exists)
            if (val_search(list, input) == 1) {
                flag = 1;
                break;
            } else {
                char choice;
                fflush(stdin);
                printf("Value not in list! Try again? y/n: ");
                scanf(" %c", &choice); // Notice the space before %c
                if (choice == 'n' || choice == 'N') {
                    flag = 0; // Updated flag value here
                    break;
                }
            }
        }

        if (flag == 1) {
            struct Node* current = list->head;
            struct Node* previous_node = NULL;

            // Remove nodes at the beginning of the list with the target value
            while (current != NULL && input == current->data) {
                list->head = current->next;
                free(current);
                current = list->head;
            }

            // Traverse the rest of the list looking for the target value
            while (current != NULL) {
                if (input == current->data) {
                    previous_node->next = current->next;
                    struct Node* temp = current; // Store current in a temporary variable
                    current = current->next;     // Update current before freeing temp
                    free(temp);                  // Free the node
                } else {
                    previous_node = current;
                    current = current->next;
                }
            }
        }
    }
}

void user_ui(struct List* list){
    int input = 0;
    while(input != 4){
        printf("Linked list UI:\n");
        printf("1. Add node\n");
        printf("2. Pop node\n");
        printf("3. Display list\n");
        printf("4. Quit\n");

        printf("> ");
        scanf("%d", &input);
        
        if(io_err_check(input) == 1){
            printf("Invalid input, try again!\n");
            fflush(stdin);
            sleep(1);
            system("cls");
        }
        else{
            switch(input){
                case 1:
                    system("cls");
                    fflush(stdin);
                    add_user_nodes(list);
                    sleep(1);
                    system("cls");
                    break;
                case 2:
                    list_remove(list);
                    sleep(1);
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    fflush(stdin);
                    print_list(list);
                    sleep(2);
                    system("cls");
                    break;
                case 4:
                    system("cls");
                    list_free(list);
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    return;
            }
        }
    }
}

int main(){

    //create and allocate space for new list using list_create function
    struct List* list = list_create();

    //user menu to add/remove nodes to linked list
    user_ui(list);

    //free list memory
    list_free(list);

    //terminate program
    return 0; 
}