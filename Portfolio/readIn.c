#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function

#include "readIn.h"
#include "blankAVL.h"

//this function reads in the data file and the file containing list names to AVL trees
Node *readIn(char string[]){
    //stuff for reading
    char filename[20];
    strcpy(filename, string);
    char line[128]; /* or other suitable maximum line size */
    FILE *file = fopen(filename, "r");

    //variables for tokening
    if(file){
        if(strcmp(filename, "movie_records") == 0){
            Node *root = NULL;
            char *token;

            char title[100];
            char releaseYear[10];
            char runTime[5];
            char genre[100];

            int tokenCount = 1;
            if (file != NULL){
                while(fgets(line, sizeof(line), file) != NULL){
                    token = strtok(line, "\t");
                    while(token != NULL){
                        if(tokenCount == 3){
                            strcpy(title,token);
                        }
                        else if(tokenCount == 6){
                            strcpy(releaseYear,token);
                        }
                        else if(tokenCount == 8){
                            strcpy(runTime,token);
                        }
                        else if(tokenCount == 9){
                            token[strlen(token) - 1] = '\0';//where the newline occurs in data set
                            strcpy(genre,token);
                        }
                        // token = strtok(NULL, "\t");
                        token = strtok(NULL, "\t");
                        tokenCount++;
                    }
                    tokenCount = 1;
                    root = insert(root, title, releaseYear, runTime, genre);
                }
                fclose(file);
            }
            else{
                perror(filename); /* why didn't the file open? */
            }
            return root;
        }
        else if(strcmp(filename, "ListNames.txt") == 0){
            char clipNewLn[200];
            char readin;
            int i = 0;
            Node *existingLists;

            while(readin!=EOF){
                readin = fgetc(file);
                if(readin != '\n'){
                    clipNewLn[i] = readin;
                    i++;
                }
                else{
                    clipNewLn[i] = '\0';
                    i = 0;
                    // printf("Created string: %s\n", clipNewLn);
                    existingLists = insert(existingLists, clipNewLn, " ", " ", " ");
                    strcpy(clipNewLn, " ");
                }
            }
            fclose(file);
            return existingLists;
        }
    }
    else{
        return NULL;
    }
}
