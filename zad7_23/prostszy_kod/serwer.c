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

    printf("Proces %d otwiera FIFO O_WRONLY | O_NONBLOCK\n", getpid());
    fd = open(FIFO_FILE, O_WRONLY | O_NONBLOCK);
    printf("Proces %d rezultat %d\n", getpid(), fd);

    if (fd != -1) {
        for (int i = 0; i < 10; i++) {
            sprintf(buf, "Serwer: wysyłam linie nr %d\n", i);
            sleep(1); // Dodane opóźnienie 1 sekundy.
            write(fd, buf, strlen(buf));
        }

        close(fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Proces %d zakonczony\n", getpid());
    exit(EXIT_SUCCESS);
}
