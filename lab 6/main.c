#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define MaxLen 128
#define serverPort 10000

int main() {
    int serverFD, connectionFD, in;
    struct sockaddr_in servaddr;
    char nameBuff[MaxLen+1];
    char dataBuff[MaxLen+1];
    char timeBuff[MaxLen+1];
    time_t currentTime;
    
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(serverPort);
    
    bind(serverFD, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(serverFD, 3);
    
    while(1) {
        connectionFD = accept(serverFD, (struct sockaddr*)NULL, NULL);
        if (connectionFD >= 0) {
            in = read(connectionFD, nameBuff, MaxLen);
            printf("\nReceived: %s\n", nameBuff);
            snprintf(dataBuff, MaxLen, "Control system has received: %s", nameBuff);
            write(connectionFD, dataBuff, strlen(dataBuff));
            
            currentTime = time(NULL);
            snprintf(timeBuff, MaxLen, "%s\n", ctime(&currentTime));
            printf("%s\n", timeBuff);
            
            close(connectionFD);
        }
    }   
    return 0;
}