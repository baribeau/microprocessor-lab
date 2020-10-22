//Lab 2 for MTE241: Intro to Computer Structures and Real-time Systems
//Authors: Julia Baribeau and Glenn Tipold
//To be run on LPC1768 microcontroller, or using hardware simulator such as in Keil uVision5


#include <lpc17xx.h>
#include <stdio.h>

//MODE SET HERE! Change number below to switch modes of operation and perform different functionality.
#define MODE 3   //MODE 0: buttonLED, MODE 1: binToLED, MODE 2: joystick, MODE 3: converter


void initializeHardware(){ //Set bits corresponding to LEDs as ouput
	LPC_GPIO1->FIODIR |= (1u<<28);
	LPC_GPIO1->FIODIR |= (1u<<29);
	LPC_GPIO1->FIODIR |= (1u<<31);
	LPC_GPIO2->FIODIR |= (1u<<2);
	LPC_GPIO2->FIODIR |= (1u<<3);
	LPC_GPIO2->FIODIR |= (1u<<4);	
	LPC_GPIO2->FIODIR |= (1u<<5);
	LPC_GPIO2->FIODIR |= (1u<<6);
}

void buttonLED(){
	while(1){
		//polling pushstick
		if(!(LPC_GPIO2->FIOPIN & (1u<<10))){
			// turn on LED
			LPC_GPIO2->FIOSET = (1u<<6);
		}
		else{
			// turn off LED
			LPC_GPIO2->FIOCLR = (1u<<6);
		}
	}
}
	
//Joystick pins are P1 23-26
void joystick(){
	while(1){
		
		if(!(LPC_GPIO1->FIOPIN & (1u<<20))){ // joystick pressed down
			printf("pressed in");
		}
		else{
			printf("not pressed in");
		}
		
		if(!(LPC_GPIO1->FIOPIN & (1u<<23))){ // joystick pressed North
			printf(", oriented north\n");
		}
		else if(!(LPC_GPIO1->FIOPIN & (1u<<24))){ // joystick pressed East
			printf(", oriented east\n");
		}
		else if(!(LPC_GPIO1->FIOPIN & (1u<<25))){ // joystick pressed South
			printf(", oriented south\n");
		}
		else if(!(LPC_GPIO1->FIOPIN & (1u<<26))){ // joystick pressed West
			printf(", oriented west\n");
		}
		else {
			printf("\n");
		}
	}
}


void binToLED(){ //Display binary representation of input decimal number on LEDs
	char inputString[4];
	int input;
	int LEDPin[] = {6,5,4,3,2,31,29,28};
	
	while(1){
		
		scanf("%s", inputString); //read input
		sscanf(inputString, "%d", &input); //convert string to int
		
		int b_mask = 128, i=0;

		while (b_mask > 0){
			if (b_mask & input){
				if (i <= 4){
					LPC_GPIO2->FIOSET = (1u<<LEDPin[i]);
				} 
				else {
					LPC_GPIO1->FIOSET = (1u<<LEDPin[i]);	
				}
			}
			else {
				if (i <= 4){
					LPC_GPIO2->FIOCLR = (1u<<LEDPin[i]);
				} 
				else {
					LPC_GPIO1->FIOCLR = (1u<<LEDPin[i]);	
				}
			}	
			b_mask = b_mask >> 1;
			i++;
		}
	}	
}

void converter(){
	
	LPC_SC->PCONP |= 1u<<12; //power on
	LPC_ADC->ADCR = 1u<<21 | 1u<<2 | 1u<<11; //enable ADCR circuitry; set potentiometer (AD0.2) as input; set clock divisor 
	LPC_PINCON->PINSEL1 &= ~(0x03<<18); 
	LPC_PINCON->PINSEL1 |= (0x01<<18); //set pin select register (P0.25)
	
	while(1){
		LPC_ADC->ADCR |= 1u<<24; //set bit to start conversion
		while(!(LPC_ADC->ADGDR & (1u<<31))){} //wait for conversion to complete
		int result = ((LPC_ADC->ADDR2>>4u) & 0xFFF); //12 bit mask
		printf("%d \n", result);
	}
}

#if (MODE == 0)
int main(){
	initializeHardware();
	buttonLED();
}

#elif (MODE == 1)
int main(){
	initializeHardware();
	binToLED();	
}

#elif (MODE == 2)
int main(){
	joystick();
}

#elif (MODE == 3)
int main(){
	converter();
}
#endif



