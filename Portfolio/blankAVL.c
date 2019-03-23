// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "blankAVL.h"

// An AVL tree node
typedef struct node{
	char title[200];
	char releaseYear[10];
	char runTime[500];
	char genre[200];
	Node *left;
	Node *right;
	int height;
}Node;

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
	return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
Node* newNode(char movie[], char release[], char rt[], char g[])
{
	Node* node = (Node*)malloc(sizeof(Node));

	strcpy(node->title, movie);
	strcpy(node->releaseYear, release);
	strcpy(node->runTime, rt);
	strcpy(node->genre, g);

	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially added at leaf
	return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	// Return new root
	return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

//takes an original string and creates a copy of that string but in all lowercase letters.
char *LOW(char *string){
	if(string == NULL){
		return NULL;
	}
	int i = 0;
	char *temp = malloc(200 * sizeof(char));
	for(i; i < strlen(string); i++){
		temp[i] = tolower(string[i]);
	}
	temp[i] = '\0';
	return temp;
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Node* insert(Node* node, char movie[], char release[], char rt[], char genre[]){
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(movie, release, rt, genre));

	char *tempMovie = malloc(200 * sizeof(char));
	char *tempNodeTitle = malloc(200*sizeof(char));
	tempMovie = LOW(movie);
	tempNodeTitle = LOW(node->title);


	if (strcmp(tempMovie,tempNodeTitle) < 0){
		node->left = insert(node->left, movie);
	}

	else if (strcmp(tempMovie,tempNodeTitle) >= 0){
		node->right = insert(node->right, movie);
	}
	/*else // Equal keys are not allowed in BST
		return node;*/

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
						height(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then
	// there are 4 cases
	char *nodeLeftTitle = malloc(200 * sizeof(char));
	nodeLeftTitle = LOW(node->left->title);

	// Left Left Case
	if ((balance > 1) && (strcmp(tempMovie,nodeLeftTitle))<0)
		return rightRotate(node);

	char *nodeRightTitle = malloc(200 * sizeof(char));
	nodeRightTitle = LOW(node->right->title);

	// Right Right Case
	if (balance < -1 && (strcmp(tempMovie,nodeRightTitle)>0))
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && (strcmp(tempMovie,nodeLeftTitle)>0))
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && (strcmp(tempMovie,nodeRightTitle)<0))
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(Node *root)
{
	if(root != NULL)
	{
		printf("%s, ", root->title);
		preOrder(root->left);
		preOrder(root->right);
	}
}
