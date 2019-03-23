#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//#include "blankAVL.h"
//#include "readIn.h"

int main(){

    char buffer[150];
    printf("Enter the name of the list you wish to create/edit:\n");
    scanf("%[^\n]s", buffer);
    printf("You entered: %s\n", buffer);
    FILE *fp;
    fp = fopen(buffer, "w");
    fprintf(fp, "%s\n", buffer);
    fclose(fp);



    /*Node *root = NULL;
    root = readIn();
    preOrder(root);*/


return 0;
}
