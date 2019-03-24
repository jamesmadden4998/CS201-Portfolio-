#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "blankAVL.h"
#include "readIn.h"

int main(){

    Node *root;
    root = readIn();

    char buffer[150];
    char lookup[150];
    char command[50] = "none";

    printf("Enter the name of the list you wish to create/edit:");
    scanf("%[^\n]s", buffer);
    printf("You entered: %s\n\n", buffer);

    while(strcmp(command, "q") != 0){
        printf("To view the contents of this list enter 'print'\n");
        printf("To search for a title to add to the list enter'add'\n");
        printf("Enter 'q' to exit program\n");
        printf("->");
        scanf(" %[^\n]s", command);
        if(strcmp(command,"print") == 0){
            char line[128];
            FILE *fptr = fopen(buffer, "r");
            while(fgets(line, sizeof(line), fptr) != NULL){
                printf("%s", line);
            }
            fclose(fptr);
        }
        else if(strcmp(command, "add") == 0){
            printf("Enter the title you want to search for:\n");
            scanf(" %[^\n]s", lookup);
            printf("You entered: %s\n", lookup);
            Node *found = searchFor(root, lookup);
            printf("Are you you sure you want to add this to your list? (Y/N)\n\n");
            printNode(found);
            char c;
            scanf(" %c", &c);
            if(c == 'Y' || c == 'y'){
                FILE *fp = fopen(buffer, "a");
                printNodeFile(fp, found);
                fclose(fp);
            }
        }
    }
    // FILE *fp;
    // fp = fopen(buffer, "w");
    // fprintf(fp, "%s\n", buffer);
    // fprintf(fp, "\t%s\n", lookup);
    // fclose(fp);*/

    //preOrder(root);
    //Node *found = malloc(sizeof(Node));

return 0;
}
