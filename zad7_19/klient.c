#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 2048

int main(int argc, char** argv) {
    FILE *command_result = popen("./serwer", "r");
    if (command_result) {
        char bufor[BUF_SIZE];
        int numer;

        fgets(bufor, BUF_SIZE, command_result);
        while (!feof(command_result)) {
            sscanf(bufor, "Serwer: wysyłam linie nr %d", &numer);
            printf("Serwer wysłał: %d\n", numer);
            fgets(bufor, BUF_SIZE, command_result);
        }
        pclose(command_result);
        fflush(stdout);
    } else {
        printf("Niepowodzenie funkcji popen \n");
        fflush(stdout);
    }
    return EXIT_SUCCESS;
}
