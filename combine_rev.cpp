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
     
     
RCSwitch mySwitch;
  int together(int a, int b) {
    int magnitude = 1;
    while(magnitude <= b) magnitude *= 10;
    return (magnitude * a + b)/10;
}


int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int new_value=20;
     int PIN_t = 0;
     int PIN = 2;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }
		
     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     RCSwitch mySwitch_t = RCSwitch();
     mySwitch_t.enableTransmit(PIN_t);
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
		int recvT = clock();
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
	      int timeT = recvT - value;
	      float timeD = (float)timeT/CLOCKS_PER_SEC;
	      //printf("Received %i\n", recvT );
	      printf("Received %i\n", value );
          //printf("Received %i\n", timeT );
          //printf("Received %f\n", timeD );
          mySwitch_t.send((together(value,new_value)),3);
          printf("Sending %u\n", together(value,new_value) );
        }
    
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}

