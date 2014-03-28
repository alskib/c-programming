//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include <time.h>
//
//#define MaxLen 128
//#define serverPort 10000
//
//int main(int argc, char *argv[]) {
//    int connectionFD, in, j;
//    struct sockaddr_in servaddr;
//
//    char buff[MaxLen+1];
//    char nameBuff[40];
//    char timeBuff[MaxLen+1];
//    char message[MaxLen+1];
//
//    //strcpy(nameBuff, argv[1]);
//    strcpy(message, "Lighting and temperature level data");
//
//    connectionFD = socket(AF_INET, SOCK_STREAM, 0);
//
//    memset(&servaddr,  0 ,  sizeof(servaddr));
//    servaddr.sin_family =  AF_INET;
//    servaddr.sin_port =  htons( serverPort );
//    servaddr.sin_addr.s_addr =  inet_addr( "127.0.0.1" );  // use server addr, local host
//
//    connect(connectionFD, (struct sockaddr*)&servaddr, sizeof(servaddr));
//
//    //Send server our name.  We assume the connection was made, i.e., connectionFD > 0.
//    //write(connectionFD, nameBuff, strlen(nameBuff)+1 );
//    write(connectionFD, message, strlen(message)+1 );
//
//    //Read server response.
//    for (j = 0; j < MaxLen; j++)
//        timeBuff[j] = '\0';
//    if(in = read(connectionFD,  timeBuff,  MaxLen ) > 0 ){
//        printf("\n%s\n", timeBuff);
//    }
//
//    close( connectionFD );
//
//    return 0;
//}
//
