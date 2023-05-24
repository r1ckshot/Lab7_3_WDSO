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

    // Utwórz plik FIFO.
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // Proces serwera zapisuje do pliku FIFO.
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        sprintf(buf, "Serwer: wysyłam linie nr %d\n", i);
        write(fd, buf, strlen(buf));
    }

    close(fd);
    return 0;
}
