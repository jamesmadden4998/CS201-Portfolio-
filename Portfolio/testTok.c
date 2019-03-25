#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool leadArticle(char title[]){

    char article[4];
    int i = 0;
    char the[4] = "The";
    char and[4] = "And";
    char a[2] = "A";
    for(i; i<3; i++){
        article[i] = title[i];
        if(i == 0 && (strcmp(article,a)==0)){
            printf("The leading article is: %s\n", article);
            return true;
        }
        else if((i == 2)&&((strcmp(article,and)==0)||(strcmp(article,the)==0))){
            printf("The leading article is: %s\n", article);
            break;
        }
    }
}


int main(){

    char title[150];
    char title2[150];
    printf("Enter movie title:");
    scanf (" %[^\n]s", title);
    strcpy(title2, title);

    int j = 3;
    if(leadArticle(title)){
        for(j; j<strlen(title); j++){
            if(title[j] != title2[j]){
                break;
            }
            printf("%c", title2[j]);
        }
    }

    return 0;
}
