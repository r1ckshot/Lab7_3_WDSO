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
    pid_t pid;
    char buf[BUF_SIZE];

    // Tworzenie pliku FIFO
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // Fork - proces potomny
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    // Kod dla procesu potomnego
    if (pid == 0) {
        fd = open(FIFO_FILE, O_WRONLY); // Proces potomny zapisuje do pliku FIFO
        if (fd == -1) {
            perror("open");
            exit(1);
        }

        for (int i = 0; i < 10; i++) {
            sprintf(buf, "Serwer: wysyłam linie nr %d\n", i);
            write(fd, buf, strlen(buf));
        }

        close(fd);
        exit(0);
    }
    // Kod dla procesu rodzica.
    else {
        fd = open(FIFO_FILE, O_RDONLY); // Proces rodzic odczytuje z pliku FIFO
        if (fd == -1) {
            perror("open");
            exit(1);
        }

        while (read(fd, buf, BUF_SIZE) > 0) {
            printf("Serwer wysłał: %s", buf);
        }

        close(fd);
    }

    return 0;
}
