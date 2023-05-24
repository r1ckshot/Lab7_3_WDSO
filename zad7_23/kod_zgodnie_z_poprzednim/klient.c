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
    int otwarty_pipe = 1;
    char bufor[BUFSIZ + 1];

    printf("Proces %d otwiera FIFO O_RDONLY\n", getpid());
    pipe_fd = open(NAZWA_FIFO, O_RDONLY);
    printf("Proces %d rezultat %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        do {
            res = read(pipe_fd, bufor, BUFSIZ);
            bufor[res] = '\0';
            if (res > 0) {
                printf("Odczytano %d bajtow: %s\n", res, bufor);
            } else {
                otwarty_pipe = 0;
            }
            sleep(2); // opóźnienie 2s
        } while (otwarty_pipe);

        (void)close(pipe_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Proces %d zakonczony\n", getpid());
    exit(EXIT_SUCCESS);
}
