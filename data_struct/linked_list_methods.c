// Codewar Kata: Linked Lists - Length & Count
// https://www.codewars.com/kata/55beec7dd347078289000021/train/c
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
	struct Node *next;
	int value;
};

size_t list_length (struct Node *list);
size_t list_count (struct Node *list, int search_val);

struct Node* create_node(int value);
void append_node(struct Node* node1, struct Node* node2);

// FIXME (1) - add_to_head occurs only within stack frame but fails outside
void add_at_head(struct Node* head, size_t n);
void add_at_tail(struct Node* head, size_t n);
struct Node* get_nth_node(struct Node* head, size_t n);

// FIXME (2 & 3) - swap occurs only within stack frame but fails outside
void swap_pair(struct Node* node1, struct Node* node2);
struct Node* swap_node_pairs(struct Node *head);

// FIXME (4 & 5) - semi working
void remove_at_index(struct Node* head, size_t index);
void add_at_index(struct Node* head, size_t index, size_t n);

void free_list(struct Node* head);
void print_list(struct Node* head);


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

struct Node* create_node(int value){
    // creates a node, sets member value to value, and appends node to start
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if(node == NULL){
        printf("Not enough heap space for allocation");
        exit(-1);
    }
    node->value = value;
    node->next = NULL;
    return node; 
}

void append_node(struct Node* node1, struct Node* node2){
    node1->next = node2;
}

struct Node* get_nth_node(struct Node* head, size_t n){
    // Codewar Kata: Linked Lists - Get Nth Node
    // https://www.codewars.com/kata/55befc42bfe4d13ab1000007/train/c
    struct Node* tmp = head;
    while(n != 0){
        tmp = tmp->next;
        n--;
    }
    return tmp;
}

void swap_pair(struct Node* node1, struct Node* node2){
    // printf("%p\n", node1);
    // printf("%p\n", node2);
    struct Node* tmp = node1;
    node1 = node2;
    node2 = tmp;
    // printf("%p\n", node1);
    // printf("%p\n", node2);
    //print_list(node1);
    //printf("%s\n", "next node");
    //print_list(node2);
}

struct Node* swap_node_pairs(struct Node *head){
    // Codewar Kata: Swap Node Pairs In Linked List
    // https://www.codewars.com/kata/59c6f43c2963ecf6bf002252/train/c
    struct Node* ptr = head;
    bool isEven = false;

    size_t len = list_length(head);
    if (len % 2 == 0){
        isEven = true;
    }
    if (isEven){
        while(ptr != NULL){
            swap_pair(ptr, ptr->next);
            ptr = ptr->next->next;
        }
    }
    else{
        while(ptr != NULL){
            swap_pair(ptr, ptr->next);
            ptr = ptr->next->next;
            // eager check in order to prevent swapping with NULL ptr
            // recall that if len is odd, we only swap the first even pairs (up to and excluding the odd one) 
            if(ptr->next == NULL){
                break; 
            }
        }
    }
    return head;
}

void remove_at_index(struct Node* head, size_t index){
    //FIXME: Use-after-free when index == 0?!
    struct Node* tmp = head;
    if (index == 0){
        head = head->next;
    }
    else{
        struct Node* previous = NULL;
        // traverse to designated index in list
        while(index > 0 && tmp != NULL){
            previous = tmp;
            tmp = tmp->next;
            index--;
        }
        
        // would be best to have come capacity global to prevent NULL reads
        if (tmp != NULL){
            previous->next = tmp->next;
        }
    }
    // free orphaned node!!
    free(tmp);
    printf("%p\n", head);
}

void add_at_index(struct Node* head, size_t index, size_t n){
    if(index == 0){
        add_at_head(head, n);
    }
    else{
        struct Node* tmp = head;
        struct Node* previous = NULL;

        // traverse into target ptr in order to do incision
        while(index > 1){
            previous = tmp;
            tmp = tmp->next;
            index--;
        }
        struct Node* node = create_node(n);
        previous->next = node;
        node->next = tmp;
    }
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
    while(tmp != NULL){
        printf("Address: %p, ", tmp);
        printf("Value: %i\n", tmp->value);
        tmp = tmp->next;
    }
}

void add_at_tail(struct Node* head, size_t n){
    struct Node* tmp = head;
    size_t len = list_length(head);
    while(len > 1){
        tmp = tmp->next;
        len--;
    }
    struct Node* node = create_node(n);
    append_node(tmp, node);
}

void add_at_head(struct Node* head, size_t n){
    struct Node* node = create_node(n);
    node->next = head;
    head = node;
    printf("%s\n", "new node set");
    // FIXME: not sure why head is not updated when exiting the stack frame
    print_list(head);
}

int main(void){
    struct Node* head = create_node(0);

    int i = 1;
    struct Node* tmp = head;
    while(i <= 20){
        struct Node* node = create_node(i);
        append_node(tmp, node);
        tmp = node;
        i++;
    }

    // deleting an arbitrary node
    //print_list(head);
    // remove_at_index(head, 20);
    // print_list(head);

    // swap node
    //swap_pair(head, head->next);
    //print_list(head);


    //add at tail
    // print_list(head);
    // add_at_tail(head, 4);
    // add_at_tail(head, 5);
    // add_at_tail(head, 6);
    // print_list(head);

    //add at head
    print_list(head);
    add_at_head(head, 4);
    print_list(head);

    // other misc stats
    // printf("%p\n", get_nth_node(head, 0));
    // printf("Length of List: %li\n", list_length(head));
    // printf("Count Occurrence: %li\n", list_count(head, 2));
    free_list(head);

}