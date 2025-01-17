#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char napis1[100];
    char napis2[100];
    printf("Podaj pierwszy napis: ");
    scanf("%s", napis1);
    printf("Podaj drugi napis: ");
    scanf("%s", napis2);
    FILE *predzej = fopen("predzej.txt", "w");
    FILE *dluzszy = fopen("dluzszy.txt", "w");
     if (predzej == NULL || dluzszy == NULL) {
        perror("Błąd otwierania pliku");
        return 1;
    }
    if(strcmp(napis1, napis2) == 0){
        fprintf(stderr, "To są te same napisy");
        fclose(predzej);
        fclose(dluzszy);
        return 1;
    }
    if(strcmp(napis1, napis2)>0){
        fprintf(predzej, "%s", napis2);
    }else{
        fprintf(predzej, "%s", napis1);
    }
    if(strlen(napis1) > strlen(napis2)){
        fprintf(dluzszy, "%s", napis1);
    }
    if(strlen(napis1) < strlen(napis2)){
        fprintf(dluzszy, "%s", napis2);
    }
    if(strlen(napis1) == strlen(napis2)){
        fprintf(stderr, "Błąd napisy są tak samo długie");
        fclose(predzej);
        fclose(dluzszy);
        return 1;
    }

    fclose(predzej);
    fclose(dluzszy);
    return 0;



}