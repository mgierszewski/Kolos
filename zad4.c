#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char imie[100];
    char nazwisko[100];
    printf("Podaj imie oraz nazwisko: ");
    scanf("%s %s", imie, nazwisko);
    for (int i = 0; imie[i] != '\0'; i++) {
        if (!( (imie[i] >= 'A' && imie[i] <= 'Z') || (imie[i] >= 'a' && imie[i] <= 'z'))) {
            fprintf(stderr, "Błąd: Imie zawiera niepoprawne znaki.\n");
            return 1;
        }
    }
    for (int j = 0; nazwisko[j] != '\0'; j++) {
        if (!( (nazwisko[j] >= 'A' && nazwisko[j] <= 'Z') || (nazwisko[j] >= 'a' && nazwisko[j] <= 'z'))) {
            fprintf(stderr, "Błąd: Nazwisko zawiera niepoprawne znaki.\n");
            return 1;
        }
    }

    FILE *baza = fopen("baza.txt", "r");
    if (baza == NULL) {
        perror("Błąd otwierania pliku");
        return 1;
    }
    char linia[200];
    int znaleziono = 0;

    while (fgets(linia, sizeof(linia), baza)) {
        char imiePlik[100], nazwiskoPlik[100];

        if (sscanf(linia, "%s %s", imiePlik, nazwiskoPlik) == 2) {
            if (strcmp(imie, imiePlik) == 0 && strcmp(nazwisko, nazwiskoPlik) == 0) {
                printf("Znaleziono osobe: %s %s\n", imiePlik, nazwiskoPlik);
                znaleziono = 1;
                break;
            }
        }
    }

    if (!znaleziono) {
        printf("Nie znaleziono osoby o imieniu %s i nazwisku %s w bazie.\n", imie, nazwisko);
    }

}