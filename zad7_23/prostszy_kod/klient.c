#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE "MYFIFO"
#define BUF_SIZE 2048

int main() {
    int fd;
    char buf[BUF_SIZE];

    // Tworzymy plik FIFO, jeśli jeszcze nie istnieje.
    if (access(FIFO_FILE, F_OK) == -1) {
        if (mkfifo(FIFO_FILE, 0666) == -1) {
            perror("mkfifo");
            exit(1);
        }
    }

    printf("Proces %d otwiera FIFO O_RDONLY\n", getpid());
    fd = open(FIFO_FILE, O_RDONLY);
    printf("Proces %d rezultat %d\n", getpid(), fd);

    if (fd != -1) {
        while (read(fd, buf, BUF_SIZE) > 0) {
            printf("Serwer wysłał: %s", buf);
            sleep(2); // Dodane opóźnienie 2 sekundy.
        }

        close(fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Proces %d zakonczony\n", getpid());
    exit(EXIT_SUCCESS);
}