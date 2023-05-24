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

    // Proces klienta odczytuje z pliku FIFO.
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    while (read(fd, buf, BUF_SIZE) > 0) {
        printf("Serwer wysłał: %s", buf);
    }

    close(fd);
    return 0;
}
