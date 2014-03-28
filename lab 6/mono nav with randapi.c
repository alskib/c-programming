#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define MaxLen 128
#define serverPort 10000
#define NUMITERATIONS 1234567L
#define loopDuration 5

void seedRandGenerator();
float getRandFloat();
int getRandInteger(int max);
float getRandExponential();
float getFinalRandExponential(int mean);

int main() {
    int connectionFD;
    struct sockaddr_in servaddr;
    time_t startTime;
    int cycleTime;
    double randNum = rand() / (double)RAND_MAX;

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
        
        strcpy(message, "Navigation data.");
        
        cycleTime = difftime(time(NULL), startTime);
        snprintf(timeBuff, 60, "\nTime elapsed: %d seconds.\n", cycleTime);
        strcat(message, timeBuff);
        //sleep();
        
        write(connectionFD, message, strlen(message)+1);
        close(connectionFD);
        
        printf("Exp mean of 3: %f\n", getFinalRandExponential(3));
        if (!(cycleTime >= loopDuration))
            sleep(loopDuration-cycleTime); // sleep only if <30 seconds elapsed
    }
    return 0;
}

void seedRandGenerator( )
{
	time_t seed;  //The seed repeats every 60 seconds.

	seed = time( NULL );    // srand( time( NULL ) );
	srand( seed );
	return;
}

float getRandFloat( )    //  0 <= random deviate < 1
{					// “RAND_MAX” is largest integer
		float randDeviate;

		randDeviate = ((float)rand( ) / (float)RAND_MAX);
		return randDeviate;

		//return ((float)rand( ) / (float)RAND_MAX);
}

int getRandInteger(int max)
{
	int randDeviate;
	randDeviate = (int)((float)max * rand( ) /
			(RAND_MAX+1.0));  //force float division
	return randDeviate;
}

float getRandExponential( )  //Interpolate between points on
{						//graph: lower bound + slope
    float x, deviate;        //of line * distance on x axis.
						//Note more approximation
    x = getRandFloat( );		//points in exponential tail.

    if (x == 0.0)     
      deviate = 0.0;  
    else if (x <= 0.1)  
      		deviate = ((x - 0.0) * 1.04 + 0.0);
    else if (x <= 0.2)
      		deviate = ((x - 0.1) * 1.18 + 0.104);
    else if (x <= 0.3)
      		deviate = ((x - 0.2) * 1.33 + 0.222);
    else if (x <= 0.4)
      		deviate = ((x - 0.3) * 1.54 + 0.355);
    else if (x <= 0.5)
      		deviate = ((x - 0.4) * 1.81 + 0.509);
    else if (x <= 0.6)
      		deviate = ((x - 0.5) * 2.25 + 0.690);
    else if (x <= 0.7)
      		deviate = ((x - 0.6) * 2.85 + 0.915);
    else if (x <= 0.75)
      		deviate =  ((x - 0.70) * 3.60 + 1.2);
    else if (x <= 0.8)
      		deviate =  ((x - 0.75) * 4.40 + 1.38);
    else if (x <= 0.84)
      		deviate =  ((x - 0.8) * 5.75 + 1.60);
    else if (x <= 0.88)
      		deviate =  ((x - 0.84) * 7.25 + 1.83);
    else if (x <= 0.9)
      		deviate =  ((x - 0.88) * 9.00 + 2.12);
    else if (x <= 0.92)
      		deviate =  ((x - 0.90) * 11.0 + 2.30);
    else if (x <= 0.94)
      		deviate =  ((x - 0.92) * 14.5 + 2.52);
    else if (x<= 0.95)
      		deviate =  ((x - 0.94) * 18.0 + 2.81);
    else if (x <= 0.96)
      	    deviate =  ((x - 0.95) * 21.0 + 2.99);
    else if (x <= 0.97)
      		deviate =  ((x - 0.96) * 30.0 + 3.20);
    else if (x <= 0.98)
      		deviate =  ((x - 0.97) * 40.0 + 3.50);
    else if (x <= 0.99)
      		deviate =  ((x - 0.98) * 70.0 + 3.90);
    else if (x <= 0.995)
      		deviate =  ((x - 0.99) * 140.0 + 4.60);
    else if (x <= 0.998)
      		deviate =  ((x - 0.995) * 300.0 + 5.30);
    else if (x <= 0.999)
    	  	deviate =  ((x - 0.998) * 800.0 + 6.20);
    else
      		deviate =  ((x - 0.9997) * 1000.0 + 8.0);

    return (float)deviate;
}

//	The example in the notes involves calling getRandExponential inside a for loop
//	I only want a clean number and don't want to run the for loop inside my program's main()
float getFinalRandExponential(int mean) { 	
	double floatSum = 0.0;					
	int k;
	for (k = 0; k < NUMITERATIONS; k++)
		floatSum += getRandExponential() * mean;
	return floatSum / (float)NUMITERATIONS;
}