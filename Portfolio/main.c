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
    root = readIn();

    int count = 0;
    char listTitle[150];
    char lookup[150];

    char arrayoflists[100][100];
    char inLine[128];
    FILE *ListN = fopen("ListNames", "r");
    while(fgets(inLine, sizeof(inLine), ListN) != NULL){
        inLine[strlen(inLine)-1] = '\0';
        strcpy(arrayoflists[count], inLine);
        count++;
    }
    fclose(ListN);

    char errand;

    while(command != 9){

        if(command == 7 || command == 0){
            resetCommand();
            promptInitial();
        }

        else if(command == 1){
            int r = 0;
            if(count == 0){
                printf("\nThere currently are no made lists.\n\n");
            }
            else{
                for(r; r<count; r++){
                    printf("%s\n", arrayoflists[r]);
                }
                printf("\n");
            }
            resetCommand();
            promptInitial();
        }

        else if(command == 2){

            int key = 0;
            int i;

            char *listname = malloc(100 * sizeof(char));
            char *compare = malloc(100 * sizeof(char));

            printf("Enter the title of the list you wish to Create or Edit.\n");
            printf("->");
            scanf(" %[^\n]s", listTitle);
            strcpy(listname, LOW(listTitle));

            while(arrayoflists[i] != NULL){
                //printf("In while...\n");
                strcpy(compare, LOW(arrayoflists[i]));
                if(strcmp(listname,compare) == 0){
                    printf("The List Exists\n");
                    key = 34;
                    break;
                }
                if(i > count)break;
                i++;
            }
            i--;

            if (key != 34){
                int input;
                printf("The list does not exist yet. Would you like to create it?\n");
                printf("Enter (1) for Yes\n");
                printf("Enter (2) for No\n");
                printf("->");
                scanf("%d", &input);
                if(input == 1){
                    count++;
                    strcpy(arrayoflists[i], listTitle);
                    FILE *fp = fopen("ListNames", "w");
                    int h = 0;
                    for(h; h<count; h++){
                        fprintf(fp, "%s\n", arrayoflists[h]);
                    }
                    fclose(fp);
                }
                else{
                    printf("\nThe list was not created.\n\n");
                    resetCommand();
                    promptInitial();
                }
            }
            resetCommand();
            promptSecond();
        }
        else if (command == 3){
            printf("Enter the the name of the list you wish to Delete:\n");
            printf("->");
            scanf(" %[^\n]s", lookup);
            errand = getchar();
            printf("Your varible (lookup) = %s\n",lookup);
            char *lowerLookup = malloc(100*sizeof(char));
            char *lowerCompare = malloc(100*sizeof(char));
            FILE *fpoint;
            strcpy(lowerLookup, LOW(lookup));
            int exists = 0;
            int index = 0;
            while(arrayoflists[index] != NULL){
                //printf("In while...\n");
                strcpy(lowerCompare, LOW(arrayoflists[index]));
                if(strcmp(lowerLookup,lowerCompare)==0){
                    printf("The List Exists\n");
                    for(index; index<count; index++){
                        strcpy(arrayoflists[index], arrayoflists[index+1]);
                    }
                    strcpy(arrayoflists[count],"\0");
                    fpoint = fopen(listTitle, "r");
                    exists = 1;
                    break;
                }
                if(index > count)break;
                index++;
            }
            index--;
            if(fpoint == NULL){
                if(exists != 1 ){
                    printf("The list you are looking for DNE.\n");
                }
                resetCommand();
                promptInitial();
            }
            else{
                if(remove(listTitle)==0){
                    printf("file was successfully deleted\n");
                    resetCommand();
                    promptInitial();
                }
                else{
                    printf("The file was not deleted\n");
                    perror("This was the error\n");
                    resetCommand();
                    promptInitial();
                }
            }
        }
        else if(command == 4){
            char line[128];
            FILE *fptr = fopen(listTitle, "r");
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
            promptSecond();
        }
        else if(command == 5){
            printf("Enter the title you want to search for:\n->");
            scanf(" %[^\n]s", lookup);
            printf("You entered: %s\n", lookup);
            Node *found = searchFor(root, lookup);
            if(found != NULL){
                printNode(found);
                printf("Are you you sure you want to add this to your list? (Y/N)\n");
                printf("->");
                char c;
                scanf(" %c", &c);
                if(c == 'Y' || c == 'y'){
                    FILE *fp = fopen(listTitle, "a");
                    printNodeFile(fp, found);
                    fclose(fp);
                }
                // else{
                //     printf("Please enter 'Y' for yes and 'N' for no.\n");
                //     printf("->");
                //     scanf("%c", &c);
                // }
            }
            else{
                printf("%s could not be found.\n", lookup);
            }
            resetCommand();
            promptSecond();
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

return 0;
}
