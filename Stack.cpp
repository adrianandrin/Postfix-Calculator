#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

nodeptr createNode(stackItem item){
	nodeptr p;
	p = (nodeptr)malloc(sizeof(struct node));
	p->item = item;
	p->next = NULL;
	return p;
}
// Stack is a nodeptr
// creates the header node
Stack newStack() {
	Stack s;
	s = createNode(0); // 0 is meaningless
	return s;
}
// insert at the front
void push(Stack s,stackItem item){
	nodeptr p = createNode(item);
	p->next = s->next;
	s->next = p;  
}
void pop(Stack s){
	nodeptr temp;
	temp = s->next;
	s->next = temp->next;
	free(temp);
}
void display(const Stack s){
	nodeptr p = s->next;
	printf("[");
	while (p!=NULL){
		printf("%c ",p->item);
		p=p->next;
	}
	printf("]");
}
bool isEmpty(const Stack s) {
	return s->next == NULL;
}
// make it empty// not necessarily the best solution
void clear(Stack s){
	while (!isEmpty(s)) {
	pop(s);
	}
}// assumes not empty
stackItem peek(const Stack s){
	return s->next->item;
}
void destroy(Stack *s){
	clear(*s);
	free((*s)); // frees the header*s = NULL;
}
