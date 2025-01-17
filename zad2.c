#include <stdio.h>
#include <stdlib.h>

int main(){
    int n=0;
    int liczba = 0;
    FILE *dodatnie = fopen("dodatnie.txt", "w");
    FILE *ujemne = fopen("ujemne.txt", "w");
    if (dodatnie == NULL || ujemne == NULL) {
        perror("Błąd otwierania pliku");
        return 1;
    }

    printf("Podaj ile chcesz wpisac liczb: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("Podaj liczbę: ");
        scanf("%d", &liczba);
        if(liczba == 0){
            fprintf(stderr, "Błąd podano 0");
            fclose(ujemne);
            fclose(dodatnie);
            return 1;
        }
        if(liczba > 0){
            fprintf(dodatnie, "%d \n", liczba);
        }else{
            fprintf(ujemne, "%d \n", liczba);
        }
    
    }
    fclose(ujemne);
    fclose(dodatnie);
    //system("pause");
    return 0;
}