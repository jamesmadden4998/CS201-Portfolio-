#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function

#include "readIn.h"
#include "blankAVL.h"

Node *readIn(char string[]){
    //stuff for reading
    char filename[20];
    strcpy(filename, string);
    char line[128]; /* or other suitable maximum line size */
    FILE *file = fopen(filename, "r");

    //variables for tokening
    if(file){
        if(strcmp(filename, "movie_records2") == 0){
            Node *root = NULL;
            char split[2] = "\t";
            char *token;

            char title[100];
            char releaseYear[10];
            char runTime[500];
            char genre[200];


            int tokenCount = 1;
            if (file != NULL){
                while(fgets(line, sizeof(line), file) != NULL){
                    //fputs(line, stdout); /* write the line */
                    token = strtok(line, split);
                    while(token != NULL){
                        if(tokenCount == 3){
                            strcpy(title,token);
                            //printf(" %s\n", token);
                        }
                        else if(tokenCount == 6){
                            strcpy(releaseYear,token);
                        }
                        else if(tokenCount == 8){
                            strcpy(runTime,token);
                        }
                        else if(tokenCount == 9){
                            strcpy(genre,token);
                        }
                        token = strtok(NULL, split);
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
        else if(strcmp(filename, "ListNames") == 0){
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
