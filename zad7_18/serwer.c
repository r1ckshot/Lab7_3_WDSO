#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // dla funkcji sleep()

int main(int argc, char** argv) {
    int i;
    for (i = 0; i < 10; ++i) {
        printf("Serwer: wysyłam linie nr %d\n", i);
        fflush(stdout);  // czyszczenie buforu przed wywołaniem sleep()
        sleep(1);  // czeka 1 sekundę przed wysłaniem następnej linii
    }
    return (EXIT_SUCCESS);
}
