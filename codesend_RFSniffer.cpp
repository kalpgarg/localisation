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
     
     
RCSwitch mySwitch_r;
RCSwitch mySwitch_t;
 


int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN_r = 2;

    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN_t = 0;
    
    // Parse the first parameter to this command as an integer
    int protocol = 0; // A value of 0 will use rc-switch's default value
    int pulseLength = 0;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }
	
     int code =0;

     mySwitch_r = RCSwitch();
     mySwitch_t = RCSwitch();

     //mySwitch_r.setProtocol(protocol);
     //mySwitch_r.setPulseLength(pulseLength);

     //mySwitch_t.setProtocol(protocol);
     //mySwitch_t.setPulseLength(pulseLength);

       // Receiver on interrupt 0 => that is pin #2
     
     
    
     while(1) {
  	if(argc >= 2) {
	
	if (mySwitch_r.available()) {
	mySwitch_r.disableReceive();}
	printf("2 \n");
	code = atoi(argv[1]);
	code = code + clock();
	mySwitch_t.enableTransmit(PIN_t);
	mySwitch_t.setRepeatTransmit(5);
	mySwitch_t.send(code, 24); 
	mySwitch_t.disableTransmit();

	}
	mySwitch_r.enableReceive(PIN_r);
      if (mySwitch_r.available()) {
	printf("21 \n");
	int value = mySwitch_r.getReceivedValue();
	int recvT = clock();
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
	      int timeT = recvT - value;
	      float timeD = (float)timeT/CLOCKS_PER_SEC;
	      //printf("Received %i\n", recvT );
	      printf("Received %i\n", value );
          printf("Received %i\n", timeT );
          //printf("Received %f\n", timeD );
        } 
    
        mySwitch_r.resetAvailable();
    
      }
      
  
  }

  exit(0);


}

