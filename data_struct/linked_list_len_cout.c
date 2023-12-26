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

struct Node* createAndAppendNode(struct Node * start, int value){
    // creates a node, sets member value to value, and appends node to start
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if(node == NULL){
        printf("Not enough heap space for allocation");
        exit(-1);
    }
    node->value = value;
    start->next = node;
    return node; 
}

struct Node * get_nth_node(struct Node * head, size_t n){
    // Codewar Kata: Linked Lists - Get Nth Node
    // https://www.codewars.com/kata/55befc42bfe4d13ab1000007/train/c
    struct Node* tmp = head;
    while(n != 0){
        tmp = tmp->next;
        n--;
    }
    return tmp;
}


void free_list(struct Node* head){
    while(head != NULL){
        struct Node* next_ptr = head->next;
        free(head);
        head = next_ptr;
    }
}

void print_list(struct Node* head){
    struct Node* tmp = head;
    while(tmp!=NULL){
        printf("Address: %p, ", tmp);
        printf("Value: %i\n", tmp->value);
        tmp = tmp->next;
    }
}

int main(void){
    struct Node* head = (struct Node*) malloc(sizeof(struct Node));
    head->value = 0;

    struct Node* node1 = createAndAppendNode(head, 1);
    struct Node* node2 = createAndAppendNode(node1, 2);
    struct Node* node3 = createAndAppendNode(node2, 2);
    node3->next = NULL;

    print_list(head);

    printf("%p\n", get_nth_node(head, 0));
    
    printf("Length of List: %li\n", list_length(head));
    printf("Cout Occurrence: %li\n", list_count(head, 2));
    free_list(head);

}