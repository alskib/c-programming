#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include "randapi.h"

#define MaxLen 128
#define serverPort 10000
#define loopDuration 30
#define expMean 3 // Simulated processing time

int main() {
    int connectionFD;
    struct sockaddr_in servaddr;
    time_t startTime;
    int cycleTime;

    char timeBuff[MaxLen+1];
    char message[MaxLen+1];

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serverPort);
    servaddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );

    while (1) {
        startTime = time(NULL);

        connectionFD = socket(AF_INET, SOCK_STREAM, 0);
        connect(connectionFD, (struct sockaddr*)&servaddr, sizeof(servaddr));

        sleep(getFinalRandExponential(expMean));
        strcpy(message, "Breathing level adjustment data.");

        cycleTime = difftime(time(NULL), startTime);
        snprintf(timeBuff, 60, "\nProcessing time elapsed: %d seconds.\n", cycleTime);
        strcat(message, timeBuff);

        write(connectionFD, message, strlen(message)+1);
        close(connectionFD);

        if (!(cycleTime >= loopDuration))
            sleep(loopDuration-cycleTime); // sleep only if <30 seconds elapsed
    }
    return 0;
}
