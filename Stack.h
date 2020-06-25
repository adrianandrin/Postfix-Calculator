#ifndef STACKARRAY_H
#define STACKARRAY_H

typedef float stackItem;
typedef struct node *nodeptr;
struct node {
	stackItem item;
	nodeptr next;
};

typedef nodeptr Stack;
Stack newStack();
void push(Stack s,stackItem item);
void pop(Stack s);
void display(const Stack s);
bool isEmpty(const Stack s);
void clear(Stack s);
stackItem peek(const Stack s);
void destroy(Stack *s);


#endif

