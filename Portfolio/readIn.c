#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function


void readIn(){
    //stuff for reading
    static const char filename[] = "movie_records2";
    char line[128]; /* or other suitable maximum line size */
    FILE *file = fopen (filename, "r");

    //variables for tokening
    char split[2] = "\t";
    char *token;

    char title[100];
    char releaseYear[10];
    char runTime[500];
    char genre[200];

    Node *root = NULL;

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
            insert(root, title, releaseYear, runTime, genre);
        }
        fclose(file);
    }
    else{
        perror(filename); /* why didn't the file open? */
    }
}
