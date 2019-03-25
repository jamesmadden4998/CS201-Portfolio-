#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "blankAVL.h"
#include "readIn.h"

char command[50];
char buffer[150];
char lookup[150];

void promptInitial(){
    printf("Enter the name of the list you wish to create or edit:\n");
    printf("Enter 'q' to exit program\n");
    printf("->");
    scanf(" %[^\n]s", buffer);
    printf("You entered: %s\n\n", buffer);
}

void promptSecond(){
    printf("To view the contents of this list enter 'print'\n");
    printf("To search for a title to add to the list enter'add'\n");
    printf("Enter 'q' to exit program\n");
    printf("->");
    scanf(" %[^\n]s", command);
}

void resetCommand(){
    strcpy(command, "none");
}

int main(){



    Node *root;
    root = readIn();

    int count = 0;
    char arrayoflists[count][100];

    while(strcmp(command, "q") != 0){
        if(count == 0){
            promptInitial();
            strcpy(arrayoflists[count], buffer);
            count++;
            promptSecond();
        }
        else if(strcmp(command,"select") == 0){
            promptInitial();
            // int i = 0;
            int key = 0;
            int i = 0;
            char *listname = malloc(100 * sizeof(char));
            char *compare = malloc(100 * sizeof(char));
            listname = LOW(buffer);
            while(arrayoflists[i] != NULL){
                //printf("In while...\n");
                compare = LOW(arrayoflists[i]);
                if(strcmp(listname,compare)==0){
                    printf("The List Exists\n");
                    key = 34;
                    break;
                }
                else if(i >= count)break;
                i++;
            }
            if (key != 34){
                printf("The list does not exist yet. Would you like to create it? (Y/N)\n");
                printf("->");
                char c;
                scanf(" %c", &c);
                if((c == 'Y')||(c == 'y')){
                    count++;
                    strcpy(arrayoflists[i], buffer);
                    FILE *fp = fopen("ListNames", "w");
                    int h = 0;
                    for(h; h<count; h++){
                        fprintf(fp, "%s\n", arrayoflists[h]);
                    }
                    fclose(fp);
                }
            }
            resetCommand();
            promptSecond();
        }
        else if(strcmp(command,"print") == 0){
            char line[128];
            FILE *fptr = fopen(buffer, "r");
            if(fptr == NULL){
                printf("list is empty\n");
                fclose(fptr);
                exit(1);
            }
            else{
                while(fgets(line, sizeof(line), fptr) != NULL){
                    printf("%s", line);
                }
                fclose(fptr);
            }
            resetCommand();
            promptSecond();
        }
        else if(strcmp(command, "add") == 0){
            printf("Enter the title you want to search for:\n");
            scanf(" %[^\n]s", lookup);
            printf("You entered: %s\n", lookup);
            Node *found = searchFor(root, lookup);
            if(found != NULL){
                printf("Are you you sure you want to add this to your list? (Y/N)\n\n");
                printNode(found);
                char c;
                scanf(" %c", &c);
                if(c == 'Y' || c == 'y'){
                    FILE *fp = fopen(buffer, "a");
                    printNodeFile(fp, found);
                    fclose(fp);
                }
                else{
                    printf("Please enter 'Y' for yes and 'N' for no.\n");
                    printf("->");
                    scanf("%c", &c);
                }
            }
            else{
                printf("%s could not be found.\n", lookup);
            }
            resetCommand();
            promptSecond();
        }
        else if(strcmp(command, "pList") == 0){
            int r = 0;
            for(r; r<count; r++){
                printf("%s\n", arrayoflists[r]);
            }
            resetCommand();
            promptSecond();
        }
    }

return 0;
}
