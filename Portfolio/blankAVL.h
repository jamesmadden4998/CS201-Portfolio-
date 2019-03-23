#ifndef __BLANKAVL_INCLUDED__
#define __BLANKAVL_INCLUDED__
#include <stdio.h>

typedef struct node Node;

 int max(int a, int b);
 int height(Node *);
 Node *newNode(char []);
 Node *rightRotate(Node *);
 Node *leftRotate(Node *);
 int getBalance(Node *);
 char *LOW(char *);
 Node *insert(Node *, char []);
 void preOrder(Node *);

#endif