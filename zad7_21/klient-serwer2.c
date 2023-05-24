#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE "MYFIFO"
#define BUF_SIZE 2048

int main() {
    int przetworzone_dane;
    char buforW[BUF_SIZE], buforR[BUF_SIZE];
    pid_t rezultat_fork;
    int i, fd;

    // Tworzymy plik FIFO
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    rezultat_fork = fork();

    if (rezultat_fork == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (rezultat_fork == 0) { // Kod serwera (proces potomny)
        //printf("Proces %d otwiera FIFO O_RDONLY\n", getpid());
        fd = open(FIFO_FILE, O_WRONLY); // plik FIFO do zapisu
        //printf("Proces %d rezultat %d\n", getpid(), fd);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < 10; ++i) {
            sprintf(buforW, "Serwer: wysyłam linie nr %d\n", i);
            przetworzone_dane = write(fd, buforW, strlen(buforW));
            printf("Zapisano %d bajtow\n", przetworzone_dane);
        }
        close(fd);
        exit(EXIT_SUCCESS);
    } else { // Kod klienta (proces rodzica)
        // Otwieramy plik FIFO do odczytu
        fd = open(FIFO_FILE, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        while ((przetworzone_dane = read(fd, buforR, BUF_SIZE)) > 0) {
            printf("Odczytano %d bajtow: %s\n", przetworzone_dane, buforR);
        }
        close(fd);
    }

    // Usuwamy plik FIFO
    unlink(FIFO_FILE);
    //printf("Proces %d zakonczony\n", getpid());
    exit(EXIT_SUCCESS);
}