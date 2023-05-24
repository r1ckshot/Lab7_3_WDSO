#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int przetworzone_dane, potoki_plikowe[2];
    char buforW[BUFSIZ + 1], buforR[BUFSIZ + 1];
    pid_t rezultat_fork;
    int i;

    memset(buforW, '\0', sizeof(buforW));
    memset(buforR, '\0', sizeof(buforR));

    if (pipe(potoki_plikowe) == 0) {
        rezultat_fork = fork();

        if (rezultat_fork == -1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (rezultat_fork == 0) { // Kod serwera (proces potomny)
            close(potoki_plikowe[0]); // Zamkniecie konca potoku do odczytu
            for (i = 0; i < 10; ++i) {
                sprintf(buforW, "Serwer: wysyłam linie nr %d\n", i);
                przetworzone_dane = write(potoki_plikowe[1], buforW, strlen(buforW));
                printf("Zapisano %d bajtow\n", przetworzone_dane);
                printf("%s\n",buforW);
            }
            close(potoki_plikowe[1]); // Zamkniecie konca potoku do zapisu po zakonczeniu zapisu
            exit(EXIT_SUCCESS);
        } else { // Kod klienta (proces rodzica)
            close(potoki_plikowe[1]); // Zamkniecie konca potoku do zapisu
            while ((przetworzone_dane = read(potoki_plikowe[0], buforR, BUFSIZ)) > 0) {
                printf("Odczytano %d bajtow: %s\n", przetworzone_dane, buforR);
            }
            close(potoki_plikowe[0]); // Zamkniecie konca potoku do odczytu po zakonczeniu odczytu
        }
    }

    printf("Uzyte deskryptory %d %d\n", potoki_plikowe[0], potoki_plikowe[1]);
    exit(EXIT_SUCCESS);
}
