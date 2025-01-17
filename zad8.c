#include <stdio.h>
#include <stdlib.h>

int main() {
    char *plik1 = "plik1.txt";
    char *plik2 = "plik2.txt";

    FILE *output1 = popen("wc -w plik1.txt", "r");
    FILE *output2 = popen("wc -w plik2.txt", "r");

    int count1, count2;
    fscanf(output1, "%d", &count1);
    fscanf(output2, "%d", &count2);

    if (count1 > count2) {
        printf("Plik '%s' ma więcej słów (%d słów).\n", plik1, count1);
    } else if (count2 > count1) {
        printf("Plik '%s' ma więcej słów (%d słów).\n", plik2, count2);
    } else {
        printf("Oba pliki mają taką samą liczbę słów (%d słów).\n", count1);
    }

    fclose(output1);
    fclose(output2);

    return 0;
}
