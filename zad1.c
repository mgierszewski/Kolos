#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

volatile sig_atomic_t received_sigusr1 = 0;
volatile sig_atomic_t received_sigusr2 = 0;

void zakoncz(int sig) {
    printf("Proces %d otrzymał sygnał %d, kończę działanie.\n", getpid(), sig);
    exit(0);
}

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        received_sigusr1 = 1;
    } else if (sig == SIGUSR2) {
        received_sigusr2 = 1;
    }

    if (received_sigusr1 && received_sigusr2) {
        printf("Proces główny otrzymał oba sygnały. Kończę działanie wszystkich procesów.\n");
        kill(0, SIGTERM); // Wysyła SIGTERM do wszystkich procesów w grupie
    }
}

int losuj_liczbe(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int wszystkie_cyfry_wieksze_od_5(int liczba) {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", liczba);
    for (size_t i = 0; i < strlen(buffer); ++i) {
        if (buffer[i] <= '5') {
            return 0;
        }
    }
    return 1;
}

int wszystkie_cyfry_mniejsze_od_5(int liczba) {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", liczba);
    for (size_t i = 0; i < strlen(buffer); ++i) {
        if (buffer[i] >= '5') {
            return 0;
        }
    }
    return 1;
}

void *watek_1_1(void *arg) {
    int liczba = losuj_liczbe(10, 100);
    FILE *plik = fopen("number1.txt", "w");
    fprintf(plik, "%d", liczba);
    fclose(plik);
    return NULL;
}

void *watek_1_2(void *arg) {
    int liczba = losuj_liczbe(100, 1000);
    FILE *plik = fopen("number2.txt", "w");
    fprintf(plik, "%d", liczba);
    fclose(plik);
    return NULL;
}

void *watek_2_1(void *arg) {
    sleep(losuj_liczbe(1, 5));
    FILE *plik = fopen("number1.txt", "r");
    if (!plik) {
        perror("Nie udało się otworzyć pliku number1.txt");
        return NULL;
    }
    int liczba;
    fscanf(plik, "%d", &liczba);
    fclose(plik);

    if (wszystkie_cyfry_wieksze_od_5(liczba)) {
        kill(getppid(), SIGUSR1);
    }
    return NULL;
}

void *watek_2_2(void *arg) {
    sleep(losuj_liczbe(1, 5));
    FILE *plik = fopen("number2.txt", "r");
    if (!plik) {
        perror("Nie udało się otworzyć pliku number2.txt");
        return NULL;
    }
    int liczba;
    fscanf(plik, "%d", &liczba);
    fclose(plik);

    if (wszystkie_cyfry_mniejsze_od_5(liczba)) {
        kill(getppid(), SIGUSR2);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    pid_t proces_1 = fork();
    if (proces_1 == 0) {
        // Proces potomny 1
        pthread_t watek1_1, watek1_2;

        pthread_create(&watek1_1, NULL, watek_1_1, NULL);
        pthread_create(&watek1_2, NULL, watek_1_2, NULL);

        pthread_join(watek1_1, NULL);
        pthread_join(watek1_2, NULL);

        exit(0);
    }

    pid_t proces_2 = fork();
    if (proces_2 == 0) {
        // Proces potomny 2
        pthread_t watek2_1, watek2_2;

        pthread_create(&watek2_1, NULL, watek_2_1, NULL);
        pthread_create(&watek2_2, NULL, watek_2_2, NULL);

        pthread_join(watek2_1, NULL);
        pthread_join(watek2_2, NULL);

        exit(0);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}
