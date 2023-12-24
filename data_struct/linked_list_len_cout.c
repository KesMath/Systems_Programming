// Codewar Kata: Linked Lists - Length & Count
// https://www.codewars.com/kata/55beec7dd347078289000021/train/c
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *next;
	int value;
};

// returns the length of the list
size_t list_length (struct Node *list){
    size_t cout = 0;
    struct Node *ptr = list; // creating copy of pointer to do computation within this stack frame so we do not actually mutate original pointer
	while(ptr != NULL){
        cout++;
        ptr = ptr->next;
    }
    return cout;
}


// returns the number of occurences of search_val in list
size_t list_count (struct Node *list, int search_val)
{
    size_t cout = 0;
    struct Node *ptr = list; // creating copy of pointer to do computation within this stack frame so we do not actually mutate original pointer
	while(ptr != NULL){
        if(ptr->value == search_val){
            cout++;
        }
        ptr = ptr->next;
    }
    return cout;
}

void free_list(struct Node* head){
    while(head != NULL){
        struct Node* next_ptr = head->next;
        free(head);
        head = next_ptr;
    }
}

int main(void){
    struct Node* head = (struct Node*) malloc(sizeof(struct Node));
    struct Node* node1 = (struct Node*) malloc(sizeof(struct Node));;
    struct Node* node2 = (struct Node*) malloc(sizeof(struct Node));;
    struct Node* node3 = (struct Node*) malloc(sizeof(struct Node));;
    
    head->value = 0;
    head->next = node1;

    node1->value = 1;
    node1->next = node2;

    node2->value = 2;
    node2->next = node3;

    node3->value = 2;
    node3->next = NULL;

    printf("Length of List: %li\n", list_length(head));
    printf("Cout Occurrence: %li\n", list_count(head, 2));
    free_list(head);

}