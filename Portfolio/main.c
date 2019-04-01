#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#include "blankAVL.h"
#include "readIn.h"

int command;

void promptInitial(){
    printf("\nEnter (1) to View all list titles.\n");
    printf("Enter (2) to Create or Edit a list.\n");
    printf("Enter (3) to Delete a list.\n");
    printf("Enter (9) to Exit program\n");
    printf("->");
    char menuBuff[3];
    scanf(" %2[^\n]s", menuBuff);
    command = menuBuff[0];
    command = command - '0';
    if(command > 3 && command != 9){
        command = 0;
    }
}

void promptSecond(){
    printf("\nEnter (4) To View the contents of this list.\n");
    printf("Enter (5) to Add to this list.\n");
    printf("Enter (6) to Delete a movie from this.\n");
    printf("Enter (7) to Select a different list.\n");
    printf("Enter (9) to exit program.\n");
    printf("->");
    char menuBuff[3];
    scanf(" %2[^\n]s", menuBuff);
    command = menuBuff[0];
    command = command - '0';
    if(command < 4){
        command = 0;
    }
}

void resetCommand(){
    command = -1;
}

int main(){

    Node *root;
    // clock_t t;
    // t = clock();
    root = readIn("movie_records2");
    // preOrder(root);

    Node *currLists;
    currLists = readIn("ListNames.txt");

    char listTitle[150];
    char lookup[200];
    command == 0;
    char arrayoflists[100][100];
    char errand;

    // t = clock() - t;
    // double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    // printf("took %f seconds to execute \n", time_taken);
    while(command != 9){

        if(command == 7 || command == 0){
            resetCommand();
            promptInitial();
        }
        else if(command == 1){
            int r = 0;
            if(currLists == NULL){
                printf("\nThere currently are no made lists.\n");
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
            printf("\nEnter the title of the list you wish to Create or Edit.\n");
            printf("->");
            scanf(" %150[^\n]s", listTitle);
            strcat(listTitle, ".log");
            Node *foundList;
            foundList = searchSpecific(currLists, listTitle);
            if(foundList == NULL){
                printf("\nThe list (%s) was not found\n", listTitle);
                printf("Enter (1) to create this list\n");
                printf("Enter (2) to search for a different list\n");
                printf("->");
                scanf("%d", &i);
                //
                if(i == 1){
                    currLists = insert(currLists, listTitle, " ", " ", " ");
                    preOrderFile(currLists);
                    remove("ListNames.txt");
                    rename("replica.txt", "ListNames.txt");
                    resetCommand();//reset command to -1
                    promptSecond();//show menu again for command scan
                }
                else if(i == 2){
                    resetCommand();
                    promptInitial();
                }
            }
            else if(foundList != NULL){
                printf("\nThe list that was found was: ");
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
            printf("\nEnter the the name of the list you wish to Delete:\n");
            printf("->");
            scanf(" %150[^\n]s", lookup);
            strcat(lookup, ".log");
            int confirm;
            Node *findList;
            findList = searchSpecific(currLists, lookup);
            if(findList != NULL){
                printf("\nThis list was found: ");
                printNode(findList);
                printf("Enter (1) to confirm deletion.\n");
                printf("Enter (2) to abort\n");
                printf("->");
                scanf("%d", &confirm);
                if(confirm == 1){
                    // printNode(temp);
                    // Node *temp = deleteNode(currLists, findList);
                    if(deleteNode(currLists, findList) == NULL){
                        remove("ListNames.txt");
                        currLists = readIn("ListNames.txt");
                    }
                    else{
                        preOrderFile(currLists);
                        remove("ListNames.txt");
                        rename("replica.txt", "ListNames.txt");
                    }
                    int status;
                	status = remove(lookup);
                	if (status==0){
                		printf("\nlist was successfully deleted\n");
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
                printf("\n");
                while(fgets(line, sizeof(line), fptr) != NULL){
                    printf("%s", line);
                }
                fclose(fptr);
            }
            else if(nullcheck == -1){
                printf("\nlist is empty\n");
            }
            resetCommand();
            promptSecond();
        }
        else if(command == 5){
            printf("\nEnter the title you want to search for:\n->");
            scanf(" %200[^\n]s", lookup);
            printf("You entered: %s\n", lookup);
            int search;
            int yesOno = -1;
            Node *specific = NULL;
            search = searchGeneral(root, lookup);
            if(search == 0){
                printf("\nEnter the full Title of the movie you wish to add\n->");
                scanf(" %200[^\n]s", lookup);
                specific = searchSpecific(root, lookup);
                if(specific != NULL){
                    printNode(specific);
                    printf("\nIs this ^ the movie you were looking for?\n");
                    printf("Enter (1) for 'Yes'.\n");
                    printf("Enter (2) for 'No'.\n");
                    printf("->");
                    scanf(" %d", &yesOno);
                    int nullcheck = -1;
                    if(yesOno == 1){
                        printf("\nWould you like to update this movie?\n");
                        printf("Enter (1) for 'Yes'.\n");
                        printf("Enter (2) for 'No'.\n");
                        printf("->");
                        scanf("%d", &yesOno);
                        if (yesOno == 1){
                            int choice;
                            printf("\nEnter (1) if you own this movie on Blu-Ray\n");
                            printf("Enter (2) if you own this movie on DVD\n");
                            printf("Enter (3) if you won a digital copy of this movie.\n");
                            printf("->");
                            scanf("%d", &choice);
                            if(choice > 3 || choice<1){
                                printf("\nEnter a 1,2 or 3!\n\n");
                                printf("Enter (1) if you own this movie on Blu-Ray\n");
                                printf("Enter (2) if you own this movie on DVD\n");
                                printf("Enter (3) if you won a digital copy of this movie.\n");
                                printf("->");
                                scanf("%d", &choice);
                            }
                            setDig(specific, choice);
                            printf("\nEnter the date that you bought this movie: (DD/MM/YYYY)\n->");
                            char date[11];
                            scanf(" %11[^\n]s", date);
                            setDate(specific, date);
                        }
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
                    promptSecond();
                }
            }
            else if(search == 34){
                specific = searchSpecific(root, lookup);
                if(specific != NULL){
                    printNode(specific);
                    printf("\nIs this ^ the movie you were looking for?\n");
                    printf("Enter (1) for 'Yes'.\n");
                    printf("Enter (2) for 'No'.\n");
                    printf("->");
                    scanf("%d", &yesOno);
                    int nullcheck = -1;
                    if(yesOno == 1){
                        printf("\nWould you like to update this movie?\n");
                        printf("Enter (1) for 'Yes'.\n");
                        printf("Enter (2) for 'No'.\n");
                        printf("->");
                        scanf("%d", &yesOno);
                        if (yesOno == 1){
                            int choice;
                            printf("\nEnter (1) if you own this movie on Blu-Ray\n");
                            printf("Enter (2) if you own this movie on DVD\n");
                            printf("Enter (3) if you own a digital copy of this movie\n");
                            printf("->");
                            scanf("%d", &choice);
                            if(choice >3 || choice < 1){
                                printf("\nEnter a 1,2 or 3!\n\n");
                                printf("Enter (1) if you own this movie on Blu-Ray\n");
                                printf("Enter (2) if you own this movie on DVD\n");
                                printf("Enter (3) if you own a digital copy of this movie\n");
                                printf("->");
                                int choice;
                                scanf("%d", &choice);
                            }
                            setDig(specific, choice);
                            printf("\nEnter the date that you bought this movie: (DD/MM/YYY)\n->");
                            char date[11];
                            scanf(" %10s", date);
                            setDate(specific, date);
                        }
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
                        printf("\nThe title you searched for was not found\n");
                    }
                }
                resetCommand();
                promptSecond();
            }
            else{
                printf("No titles were found\n");
                resetCommand();
                promptSecond();
            }
        }
        else if(command == 6){
            int hold;
            int line = 0;
            int key = 0;
            char buffTitle[207] = "Title: ";
            char readTitle[200];
            char readFile[207];

            printf("\nEnter the title of the movie you wish to delete:\n->");
            scanf(" %200[^\n]s", readTitle);

            strncat(buffTitle, readTitle, strlen(readTitle));
            FILE *old = fopen(listTitle, "r");
            FILE *new = fopen("replica.txt", "a");
            while(fgets(readFile, sizeof(readFile), old) != NULL){
                readFile[strlen(readFile)-1] = '\0';
                char title[200];
                strcpy(title, LOW(readFile));
                strcpy(title, clipArticle(title));
                strcpy(buffTitle, LOW(buffTitle));
                strcpy(buffTitle, clipArticle(buffTitle));
                if(strcmp(buffTitle, title) == 0){
                    hold = line + 6;
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
            rename("replica.txt", listTitle);
            // if(new = fopen(listTitle, "r")){
            //     remove(listTitle);
            // }
            resetCommand();
            promptSecond();
        }
        else if (command != 1||2||3||4||5||6||7||8||9){
            printf("\nINVALID INPUT...returning to top...please enter 1-7 or 9\n\n");
            command = 7;
        }
    }
    preOrderFile(currLists);
    remove("ListNames.txt");
    rename("replica.txt", "ListNames.txt");

return 0;
}
