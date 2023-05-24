#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 2048

int main(void) {
    int pipefd[2];  // deskryptory plików dla końców potoku
    pid_t pid;
    char bufor[BUF_SIZE];

    // Tworzenie potoku
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Tworzenie nowego procesu
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // kod dla procesu potomnego ("serwer")
        close(pipefd[0]);  // nie potrzebujemy końca odczytu potoku

        // Generowanie i zapisywanie linii do potoku
        for (int i = 0; i < 10; ++i) {
            sprintf(bufor, "Serwer: wysyłam linie nr %d\n", i);
            write(pipefd[1], bufor, strlen(bufor)+1);
            sleep(1);
        }

        close(pipefd[1]);  // zamykanie końca zapisu potoku
        exit(EXIT_SUCCESS);
    } else {  // kod dla procesu rodzica ("klient")
        close(pipefd[1]);  // nie potrzebujemy końca zapisu potoku

        // Odczytywanie i wyświetlanie linii z potoku
        int bytes_read;
        while ((bytes_read = read(pipefd[0], bufor, BUF_SIZE-1)) > 0) {
            bufor[bytes_read] = '\0'; // ensure null-terminated string
            printf("%s", bufor);
            sleep(1);
        }

        close(pipefd[0]);  // zamykanie końca odczytu potoku
    }

    return EXIT_SUCCESS;
}
