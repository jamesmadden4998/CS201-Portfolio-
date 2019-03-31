#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "blankAVL.h"
#include "readIn.h"

int command;

void promptInitial(){
    printf("Enter (1) to View all list titles.\n");
    printf("Enter (2) to Create or Edit a list.\n");
    printf("Enter (3) to Delete a list.\n");
    printf("Enter (9) to Exit program\n");
    printf("->");
    scanf(" %d", &command);
}

void promptSecond(){
    printf("Enter (1) to View all list titles.\n");
    printf("Enter (4) To View the contents of this list.\n");
    printf("Enter (5) to Add to this list.\n");
    printf("Enter (6) to Delete a movie from this.\n");
    printf("Enter (7) to Select a different list.\n");
    printf("Enter (9) to exit program.\n");
    printf("->");
    scanf(" %d", &command);
}

void resetCommand(){
    command = -1;
}

int main(){

    Node *root;
    root = readIn("movie_records2");

    // preOrder(root);

    Node *currLists;
    currLists = readIn("ListNames");
    // preOrder(root);

    // printf("\n\n");
    // printNode(currLists);
    // printf("\n\n");

    // preOrder(currLists);

    char listTitle[150];
    char lookup[150];

    char arrayoflists[100][100];

    char errand;

    while(command != 9){

        if(command == 7 || command == 0){
            resetCommand();
            promptInitial();
        }
        else if(command == 1){
            int r = 0;
            if(currLists == NULL){
                printf("\nThere currently are no made lists.\n\n");
            }
            else{
                preOrder(currLists);
                printf("\n");
            }
            resetCommand();
            promptInitial();
        }
        else if(command == 2){
            int i;
            printf("Enter the title of the list you wish to Create or Edit.\n");
            printf("->");
            scanf(" %[^\n]s", listTitle);
            Node *foundList;
            foundList = searchSpecific(currLists, listTitle);
            printNode(foundList);
            if(foundList == NULL){
                printf("%s was not found\n", listTitle);
                printf("Enter (1) to create this list\n");
                printf("Enter (2) to search for a different list\n");
                printf("->");
                scanf("%d", &i);
                if(i == 1){
                    currLists = insert(currLists, listTitle, " ", " ", " ");
                    preOrderFile(currLists);
                    resetCommand();
                    promptSecond();
                }
                else if(i == 2){
                    resetCommand();
                    promptInitial();
                }
            }
            else if(foundList != NULL){
                printf("The list that was found was: ");
                printNode(foundList);
                printf("\n");
                printf("Enter (1) to edit this list\n");
                printf("Enter (2) to search for a different list\n");
                printf("->");
                scanf("%d", &i);
                if(i == 1){
                    resetCommand();
                    promptSecond();
                }
                else{
                    resetCommand();
                    promptInitial();
                }
            }
        }
        else if (command == 3){
            printf("Enter the the name of the list you wish to Delete:\n");
            printf("->");
            scanf(" %[^\n]s", lookup);
            int confirm;
            Node *findList;
            findList = searchSpecific(currLists, lookup);
            if(findList != NULL){
                printf("We found the list: ");
                printNode(findList);
                printf("Enter (1) to confirm deletion.\n");
                printf("Enter (2) to abort\n");
                printf("->");
                scanf("%d", &confirm);
                if(confirm == 1){
                    deleteNode(currLists, findList);
                    preOrderFile(currLists);
                    int status;
                	status = remove(lookup);
                	if (status==0){
                		printf("list was successfully deleted\n");
                	}
                }
                else{
                    printf("Deletion of %s aborted\n", lookup);
                }
            }
            else{
                printf("%s was not found\n", lookup);
                printNode(findList);
            }
            resetCommand();
            promptInitial();
        }
        else if(command == 4){
            char line[128];
            FILE *fptr;
            int nullcheck = -1;
            if(fptr = fopen(listTitle, "r")){
                nullcheck = 1;
            }
            if(nullcheck == 1){
                while(fgets(line, sizeof(line), fptr) != NULL){
                    printf("%s", line);
                }
                fclose(fptr);
            }
            else{
                printf("list is empty\n");
                fclose(fptr);
                // exit(1);
            }
            resetCommand();
            promptSecond();
        }
        else if(command == 5){
            printf("Enter the title you want to search for:\n->");
            scanf(" %[^\n]s", lookup);
            printf("You entered: %s\n", lookup);
            int search;
            int yesOno = -1;
            Node *specific = NULL;
            search = searchGeneral(root, lookup);
            if(search == 0){
                printf("Enter the full Title of the movie you wish to add\n->");
                scanf(" %[^\n]s", lookup);
                specific = searchSpecific(root, lookup);
                if(specific != NULL){
                    printNode(specific);
                    printf("Is this ^ the movie you were looking for?\n");
                    printf("Enter (1) for 'Yes'.\n");
                    printf("Enter (2) for 'No'.\n");
                    printf("->");
                    scanf("%d", &yesOno);
                    int nullcheck = -1;
                    if(yesOno == 1){
                        // int fileLine;
                        FILE *fp;
                        if(fp = fopen(listTitle, "r")){
                            fclose(fp);
                            nullcheck = 1;
                        }
                        if(nullcheck == 1){
                            FILE *fp4 = fopen(listTitle, "a");
                            printNodeFile(fp4, specific);
                            fclose(fp4);
                        }
                        else{
                            FILE *fp5 = fopen(listTitle, "w");
                            printNodeFile(fp5, specific);
                            fclose(fp5);
                        }
                    }
                    else{
                        printf("The title you searched for was not found\n");
                    }
                    resetCommand();
                    promptInitial();
                }
            }
            else if(search == 34){
                specific = searchSpecific(root, lookup);
                if(specific != NULL){
                    printNode(specific);
                    printf("Is this ^ the movie you were looking for?\n");
                    printf("Enter (1) for 'Yes'.\n");
                    printf("Enter (2) for 'No'.\n");
                    printf("->");
                    scanf("%d", &yesOno);
                    int nullcheck = -1;
                    if(yesOno == 1){
                        FILE *file34;
                        if(file34 = fopen(listTitle, "r")){
                            fclose(file34);
                            nullcheck=1;
                        }
                        if(nullcheck == 1){
                            FILE *fp2 = fopen(listTitle, "a");
                            printNodeFile(fp2, specific);
                            fclose(fp2);
                        }
                        else{
                            FILE *fp3 = fopen(listTitle, "w");
                            printNodeFile(fp3, specific);
                            fclose(fp3);
                        }
                    }
                    else{
                        printf("The title you searched for was not found\n");
                    }
                }
                resetCommand();
                promptInitial();
            }
        }
        else if(command == 6){
            int hold;
            int line = 0;
            int key = 0;
            char buffTitle[207] = "Title: ";
            char readTitle[200];
            char readFile[207];

            printf("Enter the title of the movie you wish to delete:\n->");
            scanf(" %[^\n]s", readTitle);

            strncat(buffTitle, readTitle, strlen(readTitle));
            FILE *old = fopen(listTitle, "r");
            FILE *new = fopen("replica", "w");
            while(fgets(readFile, sizeof(readFile), old) != NULL){
                readFile[strlen(readFile)-1] = '\0';
                if(strcmp(buffTitle, readFile) == 0){
                    hold = line + 4;
                    key = -20;
                }
                if((line < hold) && (key == -20)){
                    line++;
                }
                else{
                    fprintf(new, "%s\n", readFile);
                }
            }
            fclose(old);
            fclose(new);
            remove(listTitle);
            rename("replica", listTitle);
            resetCommand();
            promptSecond();
        }
        else if (command != 1||2||3||4||5||6||7||9){
            printf("\nINVALID INPUT... returning to top\n\n");
            command = 7;
        }
    }
    preOrderFile(currLists);

return 0;
}
