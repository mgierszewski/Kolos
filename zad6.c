#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char wybor;
    printf("Wybierz format archiwum:\n");
    printf("T: utwórz archiwum tar\n");
    printf("Z: utwórz archiwum zip\n");
    printf("Wybierz T lub Z: ");
    scanf(" %c", &wybor);

    if (wybor == 'T' || wybor == 't') {
        system("tar -cvf temp.tar temp/");
        printf("Archiwum temp.tar zostało utworzone.\n");
    }
    else if (wybor == 'Z' || wybor == 'z') {
        system("zip -r temp.zip temp/");
        printf("Archiwum temp.zip zostało utworzone.\n");
    }
    else {
        fprintf(stderr, "Niepoprawny wybór.\n");
        return 1;
    }

    return 0;
}
