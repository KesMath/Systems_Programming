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

// ************* OBSERVATION *************
// If we want to mutate/write the pre-existing state of the linked list (i.e. adding, removing, swapping nodes) and have them persist after function calls, we need to pass a pointer to this linked list (i.e. double pointer)
// in cases, where we just want to read the state of a linked list (printing, freeing, counting), a normal pointer to the linked list will suffice!

// From this observation, we can see that a Double pointer are to pointers what pointers are to deferenced values!
// For if we want to modify the dereferenced values:
// Assume method signature of func(*p), we call it like func(p), where p is a pointer

// When we want to modify pointer state:
// Assume method signature of func(**p), we call it like func(&p), where p is a pointer to a pointer
// ***************************************

// REFERENCE
// https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Pointers.html


size_t list_length (struct Node *list);
bool is_empty(struct Node* head);
size_t list_count (struct Node *list, int search_val);

struct Node* create_node(int value);
void append_node(struct Node* node1, struct Node* node2);

void add_at_head(struct Node** head, size_t n);
void remove_at_head(struct Node** head); // aka pop() in Queue terms
void add_at_tail(struct Node* head, size_t n); // aka push() in Stack/Queue terms
void remove_at_tail(struct Node** head); // aka pop() in Stack terms
struct Node* get_nth_node(struct Node* head, size_t n);

// swapping values for simplicity, not pointers!
// refer to this article to read into swap pointers approach: https://www.prepbytes.com/blog/linked-list/swap-nodes-in-a-linked-list-without-swapping-data/
void swap_values(struct Node* node1, struct Node* node2);
void swap_adjacent_node_pairs(struct Node* head);


void remove_at_index(struct Node** head, size_t index);
void add_at_index(struct Node** head, size_t index, size_t n);

void free_list(struct Node* head);
void print_list(struct Node* head);


size_t list_length (struct Node *list){
    size_t cout = 0;
    struct Node *ptr = list; // creating copy of pointer to do computation within this stack frame so we do not actually mutate original pointer
	while(ptr != NULL){
        cout++;
        ptr = ptr->next;
    }
    return cout;
}

bool is_empty(struct Node* head){
    return list_length(head) == 0;
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

// swapping values for simplicity, not pointers!
void swap_values(struct Node* node1, struct Node* node2){
    int tmp = node1->value;
    node1->value = node2->value;
    node2->value = tmp;
}

void swap_adjacent_pair_values(struct Node* head){
    struct Node* ptr = head;
    bool isEven = false;

    size_t len = list_length(head);
    if (len == 0 || len == 1){
        return;
    }
    if (len % 2 == 0){
        isEven = true;
    }
    if (isEven){
        while(ptr != NULL){
            swap_values(ptr, ptr->next);
            ptr = ptr->next->next;
        }
    }
    else{
        while(ptr != NULL){
            swap_values(ptr, ptr->next);
            ptr = ptr->next->next;
            // eager check in order to prevent swapping with NULL ptr
            // recall that if len is odd, we only swap the first even pairs (up to and excluding the odd one) 
            if(ptr->next == NULL){
                break; 
            }
        }
    }
    //return head;
}

void remove_at_index(struct Node** head, size_t index){
    struct Node* tmp = *head;
    if (index == 0){
        *head = tmp->next;
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
}

void add_at_index(struct Node** head, size_t index, size_t n){
    if(index == 0){
        add_at_head(head, n);
    }
    else{
        struct Node* tmp = *head;
        struct Node* previous = NULL;
        struct Node* node = create_node(n);

        // traverse into target ptr in order to do incision
        while(index > 1 && tmp != NULL){
            previous = tmp;
            tmp = tmp->next;
            index--;
        }
        // when index exceeds linked list capacity, just add to tail
        // optionally, can just check if index > list_length(head), break 
        if (tmp == NULL){
            previous->next = node;
            return;
        }
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

void add_at_head(struct Node** head, size_t n){
    struct Node* node = create_node(n);
    node->next = *head;
    *head = node;
}

void remove_at_tail(struct Node** head){
    size_t len = list_length(*head);
    remove_at_index(head, len - 1);
}

void remove_at_head(struct Node** head){
    remove_at_index(head, 0);
}

int main(void){
    struct Node* head = create_node(0);

    int i = 1;
    struct Node* tmp = head;
    while(i <= 21){
        struct Node* node = create_node(i);
        append_node(tmp, node);
        tmp = node;
        ++i;
    }
    //deleting an arbitrary node
    printf("\n%s\n", "Deleting arbitrary nodes...");
    print_list(head);
    printf("%s\n", "***********");
    remove_at_index(&head, 0);
    remove_at_index(&head, 15);
    remove_at_index(&head, 0);
    print_list(head);

    // inserting an arbitrary node
    printf("\n%s\n", "Inserting arbitrary nodes...");
    print_list(head);
    printf("%s\n", "***********");
    add_at_index(&head, 0, 3200);
    add_at_index(&head, 10, 1600);
    add_at_index(&head, 10, 1600);
    print_list(head);

    // swap node
    printf("\n%s\n", "Swapping adjacent nodes...");
    print_list(head);
    printf("%s\n", "***********");
    swap_adjacent_pair_values(head);
    print_list(head);


    //add at tail
    printf("\n%s\n", "Adding nodes to tail...");
    print_list(head);
    printf("%s\n", "***********");
    add_at_tail(head, 4);
    add_at_tail(head, 5);
    add_at_tail(head, 6);
    print_list(head);

    //add at head
    printf("\n%s\n", "Adding nodes to head...");
    print_list(head);
    printf("%s\n", "***********");
    add_at_head(&head, 600);
    add_at_head(&head, 400);
    add_at_head(&head, 400);
    print_list(head);

    //remove at tail
    printf("\n%s\n", "Popping from tail...");
    print_list(head);
    printf("%s\n", "***********");
    remove_at_tail(&head);
    remove_at_tail(&head);
    print_list(head);

    //remove at head
    printf("\n%s\n", "Removing from head...");
    print_list(head);
    printf("%s\n", "***********");
    remove_at_head(&head);
    remove_at_head(&head);
    print_list(head);

    // other misc stats
    printf("Length of List: %li\n", list_length(head));
    printf("Count Occurrence of %i: %li\n", 1600, list_count(head, 1600));
    free_list(head);
    return 0;
}