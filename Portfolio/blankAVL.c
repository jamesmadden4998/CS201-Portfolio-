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
	char runTime[5];
	char genre[100];
	char digital[10];
	char dateAquired[12];
	Node *left;
	Node *right;
	int height;
}Node;

void setDig(Node *node, int choice){
	if(choice == 1){
		strcpy(node->digital, "BR");
	}
	else if(choice == 2){
		strcpy(node->digital, "DVD");
	}
	else if(choice == 3){
		strcpy(node->digital, "Digital");
	}
}

void setDate(Node *node, char date[]){
	strcpy(node->dateAquired, date);
}

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

// int min(int a, int b){
// 	return (a < b)? a:b;
// }

/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
Node* newNode(char movie[], char release[], char rt[], char g[])
{
	Node* node = (Node*)malloc(sizeof(Node));

	strcpy(node->title, movie);
	strcpy(node->releaseYear, release);
	strcpy(node->runTime, rt);
	strcpy(node->genre, g);
	strcpy(node->digital, "n/a");
	strcpy(node->dateAquired, "dd/mm/yyyy");



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

char *clipArticle(char title[]){
	int f = 4;
	int a = 2;
	char *tempString = malloc(200 * sizeof(char));

	// printf("%s\n", title);
    if(strncmp(title, "and", 3) == 0){
        for(f; f<strlen(title); f++){
			tempString[f-4] = title[f];
		}
		tempString[f-4] = '\0';
        return tempString;
	}
	else if(strncmp(title, "the", 3) == 0){
        for(f; f<strlen(title); f++){
			tempString[f-4] = title[f];
            // printf("%c\n", tempString[f-4]);
		}
		tempString[f-4] = '\0';
		// printf("%s\n", tempString);
        return tempString;
	}
	else if(strncmp(title, "a ", 2) == 0){
        for(a; a<strlen(title); a++){
			tempString[a-2] = title[a];
		}
		tempString[a-2] = '\0';
        return tempString;
	}
	else{
		return title;
	}
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Node* insert(Node* node, char movie[], char release[], char rt[], char genre[]){
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(movie, release, rt, genre));

	char tempMovie[200];
	char tempNodeTitle[200];
	if(LOW(node->title) != NULL){
		strcpy(tempNodeTitle,LOW(node->title));
		strcpy(tempNodeTitle,clipArticle(tempNodeTitle));
	}
	if(LOW(movie) != NULL){
		strcpy(tempMovie,LOW(movie));
		strcpy(tempMovie,clipArticle(tempMovie));
	}
	// printf("tempMovie--%s	tempNodeTitle--%s\n", tempMovie, tempNodeTitle);

	if (strcmp(tempMovie,tempNodeTitle) < 0){
		node->left = insert(node->left, movie, release, rt, genre);
	}

	else if (strcmp(tempMovie,tempNodeTitle) > 0){
		node->right = insert(node->right, movie, release, rt, genre);
	}
	/*else // Equal keys are not allowed in BST
		return node;*/

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),height(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);
	// If this node becomes unbalanced, then
	// there are 4 cases
	// printf("Here\n");
	// printf("Here22\n");
	char nodeLeftTitle[200];
	char nodeRightTitle[200];

	if(LOW(node->left->title) != NULL){
		strcpy(nodeLeftTitle,LOW(node->left->title));
		strcpy(nodeLeftTitle,clipArticle(nodeLeftTitle));
	}

	if(LOW(node->right->title) != NULL){
		strcpy(nodeRightTitle, LOW(node->right->title));
		strcpy(nodeRightTitle,clipArticle(nodeRightTitle));
	}

	// Left Left Case
	if (balance > 1 && (strcmp(tempMovie,nodeLeftTitle)<0)) {
		return rightRotate(node);
	}
	// Right Right Case
	if (balance < -1 && (strcmp(tempMovie,nodeRightTitle)>0)){
		return leftRotate(node);
	}

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

Node *minValueNode(Node* node){
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* node, Node *search){
    // STEP 1: PERFORM STANDARD BST DELETE

    if (node == NULL)
        return node;

	char tempSearch[200];
	char tempNodeTitle[200];
	if(LOW(node->title) != NULL){
		strcpy(tempNodeTitle,LOW(node->title));
		strcpy(tempNodeTitle,clipArticle(tempNodeTitle));
	}
	if(LOW(search->title) != NULL){
		strcpy(tempSearch,LOW(search->title));
		strcpy(tempSearch,clipArticle(tempSearch));
	}


    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (strcmp(tempSearch, tempNodeTitle) < 0)
        node->left = deleteNode(node->left, search);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if(strcmp(tempSearch, tempNodeTitle) > 0)
        node->right = deleteNode(node->right, search);

    // if key is same as root's key, then This is
    // the node to be deleted
    else{
        // node with only one child or no child
        if((node->left == NULL) || (node->right == NULL)){
			Node *temp = node->left ? node->left : node->right;
            if (temp == NULL){// No child case
                temp = node;
                node = NULL;
            }
            // One child case// Copy the contents of the non-empty child
			else{
				strcpy(node->title, temp->title);
			   	strcpy(node->releaseYear, temp->releaseYear);
			   	strcpy(node->runTime, temp->runTime);
			   	strcpy(node->genre, temp->genre);
				strcpy(node->dateAquired, temp->dateAquired);
				strcpy(node->digital, temp->digital);
				node->right = NULL;
				node->left = NULL;
				node->height = temp->height;
		 	}
        }
        else{
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);

            // Copy the inorder successor's data to this node
            strcpy(node->title, temp->title);
			strcpy(node->releaseYear, temp->releaseYear);
			strcpy(node->runTime, temp->runTime);
			strcpy(node->genre, temp->genre);
			strcpy(node->dateAquired, temp->dateAquired);
			strcpy(node->digital, temp->digital);

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp);
        }
    }

    // If the tree had only one node then return
    if (node == NULL)
      return node;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0){
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(Node *root){
	if(root != NULL){
		if(root->title[strlen(root->title)-1] == '\n')
			printf("%s", root->title);
		else
			printf("%s\n", root->title);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void printNode(Node *root);

Node *searchSpecific(Node *root, char movie[]){
	Node *tempS = root;
	if(tempS == NULL){
		// printf("Returned Null\n");
		return NULL;
	}
	char Movie[200];
	char NodeTitle[200];
	strcpy(Movie, LOW(movie));
	strcpy(Movie,clipArticle(Movie));
	strcpy(NodeTitle, LOW(tempS->title));
	strcpy(NodeTitle, clipArticle(NodeTitle));
	int two = strlen(NodeTitle);
	NodeTitle[two] = '\0';


	if(strcmp(Movie, NodeTitle) == 0){
		return tempS;
	}
	else{
		if(strcmp(Movie, NodeTitle) < 0){
			return searchSpecific(tempS->left, Movie);
		}
		else if(strcmp(Movie, NodeTitle) > 0){
        	return searchSpecific(tempS->right, Movie);
		}
	}
}

int searchGeneral(Node *root, char movie[]){
	if(root == NULL){
		return 0;
	}
	Node *tempG = root;
	char Movie2[200];
	char *NodeTitle2 = malloc(200 * sizeof(char));
	char NodeTitleR[200];
	char NodeTitleL[200];
	strcpy(Movie2, LOW(movie));
	strcpy(Movie2, clipArticle(Movie2));
	strcpy(NodeTitle2, LOW(tempG->title));
	strcpy(NodeTitle2, clipArticle(NodeTitle2));

	if(tempG == NULL){
		// printf("The database is empty\n");
		return 0;
	}
	else if(strcmp(Movie2,NodeTitle2) == 0){
		return 34;
	}
    else if(strncmp(Movie2, NodeTitle2, strlen(Movie2)) < 0 /*e < t->data*/ )
    	searchGeneral(tempG->left, Movie2);
    else if(strncmp(Movie2, NodeTitle2, strlen(Movie2)) > 0 /*e > t->data*/ )
        searchGeneral(tempG->right, Movie2);
    else{
        printNode(tempG);
		if(tempG->left != NULL)
			searchGeneral(tempG->left, Movie2);
		if(tempG->right != NULL)
			searchGeneral(tempG->right, Movie2);
	}



}

void preOrderFile(Node *lists){
	if(lists != NULL){
		FILE *lastOp = fopen("replica.txt", "a");
		char buffer[200];

		strcpy(buffer, lists->title);
		fprintf(lastOp, "%s\n", buffer);
		fclose(lastOp);
		preOrderFile(lists->left);
		preOrderFile(lists->right);
		// remove("ListNames");
	}
}
//prints a nodes details to the terminal
void printNode(Node *root){
	if(root != NULL){
		printf("\nTitle: %s\n", root->title);
		if(strcmp(root->genre, " ") != 0){
			printf("\tRelease year: %s\n", root->releaseYear);
	    	printf("\tRuntime: %s\n", root->runTime);
	    	printf("\tGenre: %s\n", root->genre);
			printf("\tMedia Type: %s\n", root->digital);
			printf("\tDate Purchased: %s\n", root->dateAquired);
		}
	}
	else{
		printf("(null)\n");
	}
}

//This prints a node and its contents to the passed file
// Used for writing movie info to a list
void printNodeFile(FILE *fp, Node *root){
	fprintf(fp, "Title: %s\n", root->title);
    fprintf(fp, "\tRelease year: %s\n", root->releaseYear);
    fprintf(fp, "\tRuntime: %s\n", root->runTime);
	root->genre[strlen(root->genre) - 1] = '\0';
    fprintf(fp, "\tGenre: %s\n", root->genre);
	fprintf(fp, "\tMedia Type: %s\n", root->digital);
	fprintf(fp, "\tDate Purchased: %s\n\n", root->dateAquired);
}
