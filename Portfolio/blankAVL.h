#ifndef __BLANKAVL_INCLUDED__
#define __BLANKAVL_INCLUDED__
#include <stdio.h>

typedef struct node Node;

 int max(int a, int b);
 int height(Node *);
 Node *newNode(char [], char[], char[], char[]);
 Node *rightRotate(Node *);
 Node *leftRotate(Node *);
 int getBalance(Node *);
 char *LOW(char *);
 Node *insert(Node *, char [], char [], char[], char[]);
 void preOrder(Node *);
 void preOrderFile(Node *);
 void printNode(Node *);
 void printNodeFile(FILE *, Node *);
 int searchGeneral(Node *, char []);
 Node *searchSpecific(Node *, char[]);
 char *clipArticle(char []);
 Node *del(Node *, Node *);
 Node *deleteNode(Node*, Node *);

#endif
