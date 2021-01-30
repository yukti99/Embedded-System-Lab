/*
YUKTI KHURANA
2017UCP1234
PIR - Passive Infrared Sensor
PIR sensor is inexpensive, low-power and easy to use Motion Detections Sensor. 
PIR sensor only receives infrared rays, not emits that’s why it’s called passive. 
PIR sense any change in heat, and if there is a change it gives HIGH at OUTPUT. 
PIR Sensor also referred as Pyroelectric or IR motion sensor. 
*/

#include <reg51.h>

sbit detect = P0^0; /* Read PIR sensor's data on this pin */
sbit LED = P1^0;    /* Connect LED to the PORT-1  pin-0 */


void MSdelay(unsigned int val){
    unsigned int i,j;
    for(i=0;i<=val;i++)
        for(j=0;j<112;j++);	/* Delay of 1 ms for 11.0592MHz Frequency */
}

void main(void){
	P1=0;			/* Initially LED turned OFF*/
	MSdelay(3000);	/* Power-on delay for PIR */
	while(1){
		// a high i.e 1 in PIR sensor port means that it detected some motion due to change in heat
		// or emition of infrared rays, so LED is turned to show that PIR has sensed some human motion
		// but when no motion is detected, the LED 
		// CHECK THIS!!!
		if(detect == 1)  /* Check for human motion */
			LED = 0;	/* LED turn OFF for No motion */
		else
			LED = 1;	/* LED turn ON if motion is detected */
	}
}
/*
In this program a pir sensor detects human motion and that triggers 
LED light to turn on or off
if human motion is detected it is turned on,
if no such motion is sensed by PIR then it is turned off.
So LED's blinking can be said to indicate the a temporary human motion nearby
*/