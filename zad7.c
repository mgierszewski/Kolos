#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Plik/folder o najkrotszej nazwie:\n");
    system("ls ~ | awk '{print length($0), $0}' | sort -n | head -n 1");

    printf("\nPlik/folder o najdluzszej nazwie:\n");
    system("ls ~ | awk '{print length($0), $0}' | sort -n -r | head -n 1");

    return 0;
}
