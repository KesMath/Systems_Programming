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
size_t list_length (const struct Node *list)
{
	while(list != NULL){
        printf("%i\n", list->value);
        list = list->next;
    }
    return 0;
}
// returns the number of occurences of search_val in list
size_t list_count (const struct Node *list, int search_val)
{
	return 0;
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

    node3->value = 3;
    node3->next = NULL;
    // FIXME: shouldn't head ptr be at the tail of the list?!
    printf("%li\n", list_length(head));
    //printf("%li\n", list_count(head, 8));

    free_list(head);

}