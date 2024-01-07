#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Inspired from https://leetcode.com/problems/implement-stack-using-queues/
// Stack Implementation using Doubly Linked List

struct Node {
	struct Node *next;
    struct Node *previous;
	int value;
};

struct Node* create_stack();
void push(int x);
struct Node* pop();
int top();
bool empty();
void free_stack();

struct Node* create_stack(){

}

void push(int x){

}

struct Node* pop(){

}

int top(){

}

bool empty(){

}

void free_stack(){

}
int main(void){
    return 0;
}