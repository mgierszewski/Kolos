#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    FILE *f = fopen("liczby.txt", "r");    // otwiera plik do odczytu (musi istniec)
    if (f == NULL)
    {
        perror("Nie udalo sie otworzyc pliku notatki.txt");
        return 1;
    }
    puts("Plik otwarty pomyslnie!");

    int tablica[100];
    int i = 0;
    int liczba;
    while(i<100 && fscanf(f, "%d", &liczba)==1){
        tablica[i]=liczba;
        i++;
        printf("(%d)  %d ", i,  tablica[i-1]);
    }
    int min = tablica[0];
    int max = tablica[0];

    for(int j=0; j<i; j++){
        if(tablica[j] < min){
            min = tablica[j];
        }
        if (tablica[j] > max){
            max = tablica[j];
        }
    }
    printf("Najmniejsza liczba: %d", min);
    printf("Największa liczba: %d", max);
    


    fclose(f);
    return 0;
}