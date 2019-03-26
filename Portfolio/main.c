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
    char arrayoflists[100][100];
    char listTitle[150];
    char lookup[150];

    char inLine[128];
    FILE *ListN = fopen("ListNames", "r");
    while(fgets(inLine, sizeof(inLine), ListN) != NULL){
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
                printf("There currently are no made lists.\n");
            }
            else{
                for(r; r<count; r++){
                    printf("%s", arrayoflists[r]);
                }
                printf("\n");
            }
            resetCommand();
            promptInitial();
        }

        else if(command == 2){
            printf("Enter the title of the list you wish ot Create or Edit.\n");
            printf("->");
            scanf(" %[^\n]s", listTitle);
            errand = getchar();
            int key = 0;
            int i = 0;
            char *listname = malloc(100 * sizeof(char));
            char *compare = malloc(100 * sizeof(char));
            strcpy(listname, LOW(listTitle));
            while(arrayoflists[i] != NULL){
                //printf("In while...\n");
                strcpy(compare, LOW(arrayoflists[i]));
                if(strcmp(listname,compare)==0){
                    printf("The List Exists\n");
                    key = 34;
                    break;
                }
                if(i > count)break;
                i++;
            }
            i--;
            if (key != 34){
                printf("I...Count is    %d...%d\n", i, count);
                char ch;
                printf("The list does not exist yet. Would you like to create it? (Y/N)\n");
                printf("->");
                scanf("%c", &ch);
                if((ch == 'Y')||(ch == 'y')){
                    count++;
                    strcpy(arrayoflists[i], listTitle);
                    FILE *fp = fopen("ListNames", "w");
                    int h = 0;
                    for(h; h<count; h++){
                        fprintf(fp, "%s", arrayoflists[h]);
                    }
                    fclose(fp);
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

            strcpy(lowerLookup, LOW(lookup));
            int exists = 0;
            int index = 0;
            while(arrayoflists[index] != NULL){
                //printf("In while...\n");
                //strcpy(lowerCompare, LOW(arrayoflists[index]));
                if(strcmp(lookup,arrayoflists[index])==0){
                    printf("The List Exists\n");
                    exists = 1;
                    break;
                }
                if(index > count)break;
                index++;
            }
            index--;
            if(exists == 1){
                for(index; index<count; index++){
                    strcpy(arrayoflists[index], arrayoflists[index+1]);
                }
                int status = remove(listTitle);
                if(status == 0){
                    printf("file was successfully deleted\n");
                }
                else{
                    printf("The file was not deleted\n");
                    perror("This was the error\n");
                }
            }
            else if(exists != 1 ){
                printf("The list you are looking for DNE.\n");
                resetCommand();
                promptInitial();
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
                printf("Are you you sure you want to add this to your list? (Y/N)\n\n");
                printf("->");
                char c;
                scanf(" %c", &c);
                if(c == 'Y' || c == 'y'){
                    FILE *fp = fopen(listTitle, "a");
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
        else if(command == 6){
            // DELETE MOVIE FROM FOUND LIST
        }
        else if (command != 1||2||3||4||5||6||7||9){
            printf("INVALID INPUT... returning to top\n\n");
            command = 7;
        }
    }

return 0;
}
