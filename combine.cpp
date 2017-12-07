/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sstream>
#include <ctype.h>
#include <string>
     
     
RCSwitch mySwitch_r;
 
 int together(int a, int b) {
    int magnitude = 1;
    while(magnitude <= b) magnitude *= 10;
    return magnitude * a + b;
}


int main(int argc, char *argv[]) {
   int PIN = 0;
     int PIN_r = 2;
        timespec ts;
        timespec ts1;
        int x = 1;

     unsigned int value=0;
     unsigned int new_value=20;
    // Parse the first parameter to this command as an integer
    int protocol = 0; // A value of 0 will use rc-switch's default value
    int pulseLength = 0;

    // If no command line argument is given, print the help text
    if (argc == 1) {
        printf("Usage: %s decimalcode [protocol] [pulselength]\n", argv[0]);
        printf("decimalcode\t- As decoded by RFSniffer\n");
        printf("protocol\t- According to rc-switch definitions\n");
        printf("pulselength\t- pulselength in microseconds\n");
        return -1;
    }

    // Change protocol and pulse length accroding to parameters
    int code = atoi(argv[1]);
    if (argc >= 3) protocol = atoi(argv[2]);
    if (argc >= 4) pulseLength = atoi(argv[3]);
    
    if (wiringPiSetup () == -1) return 1;
    //printf("sending code[%i]\n", code);
    RCSwitch mySwitch = RCSwitch();
    if (protocol != 0) mySwitch.setProtocol(protocol);
    if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
    mySwitch.enableTransmit(PIN);
    
    //code = time(NULL);
    //float c1 = time(NULL);
    //printf("sending code[%f]\n", c1);
    //code = code % 1000000 ;
    mySwitch_r = RCSwitch();
    mySwitch_r.enableReceive(PIN_r);  // Receiver on interrupt 0 => that is pin #2
    mySwitch.setProtocol(2);
    //code = clock();
    while(1){
    clock_gettime(CLOCK_REALTIME, &ts);
    code = 1;
    int ts_sec = ts.tv_sec;
    unsigned int ts_nsec = ts.tv_nsec;
    //printf("sending code[%u]\n", code);
    mySwitch.send(code, 3);
    //int flag = clock()-code;
    //printf("flag %i\n",flag);
    //printf("timesec : %i\n",ts_sec);
    //printf("timenano : %i\n",ts.tv_nsec);
    ///////////////////////////////////////////////////////////////////////////////////	
     
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     //int PIN_r = 2;
     
     /*if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }*/

     /*int pulseLength_r = 0;
     if (argv[1] != NULL) pulseLength_r = atoi(argv[1]);

     mySwitch_r = RCSwitch();
     if (pulseLength_r != 0) mySwitch.setPulseLength(pulseLength_r);*/
     //mySwitch_r = RCSwitch();
     //mySwitch_r.enableReceive(PIN_r);  // Receiver on interrupt 0 => that is pin #2
     //printf("\n");
     
     if(x == 1) {
		//printf("here12\n");
      if (mySwitch_r.available()) {
         //printf("here2\n");
        value = mySwitch_r.getReceivedValue();
        clock_gettime(CLOCK_REALTIME, &ts1);
        int recvSec = ts1.tv_sec;
        //printf("timenano2 : %i\n",ts1);
        printf("value : %i\n",value);
		unsigned int recvT = ts1.tv_nsec;
		
        if (value == 0) {
			//printf("here3\n");
          printf("Unknown encoding\n");
        } else if(value == 12){    
			//printf("here4\n");
			int timeT_sec = recvSec - ts_sec;
	      unsigned int timeT_nano = recvT>ts_nsec?(recvT - ts_nsec):(1000000000*timeT_sec+(recvT - ts_nsec));
	      
	      //float timeD = (float)timeT_nano/CLOCKS_PER_SEC;
	      printf("Received at(nano) %u\n", recvT );
	      printf("Received %u\n", value );
          printf("Travel clock time(nano) %u\n", timeT_nano );
          //printf("Travel clock time(sec) %u\n", timeT_sec );
          printf("travel time %.10lf\n", ((double)timeT_nano/1000000000));  //0.1617705383-0.15950798
          //printf("timenano : %i",ts1-ts);
          x = 0;
        }
    //printf("here5\n");
        mySwitch_r.resetAvailable();
    
      }
      //printf("here6\n");
  
  }
  /*mySwitch.send((together(value,new_value)),3);
  printf("Sending %u\n", together(value,new_value) );
//printf("here7\n");*/
}
  exit(0);


}


