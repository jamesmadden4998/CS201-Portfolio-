#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "blankAVL.h"


int main(){
    Node *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, "James");
    root = insert(root, "ryan");
    root = insert(root, "Evan");
    root = insert(root, "john");
    root = insert(root, "Louis");
    root = insert(root, "Trez");

    /* The constructed AVL Tree would be
    			30
    		/ \
    		20 40
    		/ \	 \
    	10 25 50
    */

    printf("Preorder traversal of the constructed AVL"
    		" tree is \n");
    preOrder(root);

return 0;
}
