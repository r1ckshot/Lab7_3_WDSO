#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define NAZWA_FIFO "/tmp/moje_fifo"

int main() {
    int pipe_fd;
    int res;
    int i;
    char bufor[BUFSIZ + 1];

    if (access(NAZWA_FIFO, F_OK) == -1) {
        res = mkfifo(NAZWA_FIFO, 0777);
        if (res != 0) {
            fprintf(stderr, "Nie moge utworzic fifo %s\n", NAZWA_FIFO);
            exit(EXIT_FAILURE);
        }
    }

    printf("Proces %d otwiera FIFO O_WRONLY | O_NONBLOCK\n", getpid());
    pipe_fd = open(NAZWA_FIFO, O_WRONLY | O_NONBLOCK);
    printf("Proces %d rezultat %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        for (i = 0; i < 10; ++i) {
            sprintf(bufor, "Serwer: wysyłam linie nr %d\n", i);
            res = write(pipe_fd, bufor, strlen(bufor));
            if (res == -1) {
                fprintf(stderr, "Blad zapisu do pipe\n");
                exit(EXIT_FAILURE);
            }
            printf("Zapisano %d bajtow\n", res);
            sleep(1); // opóźnienie 1s
        }
        (void)close(pipe_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Proces %d zakonczony\n", getpid());
    exit(EXIT_SUCCESS);
}
