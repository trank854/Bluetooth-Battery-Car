/////////////////////////////////////////////////////////////////////////////
// Course Number: CECS 347
// Example project for Hardware PWM controlled Car
// Description: 
// Hardware connections: assume L298N is used for DC motor driver
// PB67 for motor PWM signals: PB6 - Left DC Motor, PB7 - Right DC Motor
// PB5432 for motor directions: PB54 - left DC Motor, PB32 - right DC Motor
// By Min He, 10/19/2022
/////////////////////////////////////////////////////////////////////////////

//////////////////////1. Pre-processor Directives Section////////////////////
#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "GPIO.h"
#include "UART1.h"

//////////////////////2. Subroutines Section/////////////////////////////////
// MAIN: This main is meant for the command configuration of the hc05.
int main(void){ 	
	UART1_Init();
	LED_Init();
	Car_Dir_Init();
	PWM_PB76_Init();
	PWM_PB76_Duty(START_SPEED, START_SPEED);
	
	LED = Dark;
	
	char dir = 'S';
  while(1){
		dir = UART1_InChar();
		if(dir == 'F'){
			LED = Green;
			DIRECTION = FORWARD;
			PWM0_ENABLE_R |= 0x00000003;
		}
		else if(dir == 'B'){
			LED = Blue;
			DIRECTION = BACKWARD;
			PWM0_ENABLE_R |= 0x00000003;
		}
		else if(dir == 'L'){
			LED = Yellow;
			DIRECTION = FORWARD;
			PWM0_ENABLE_R |= 0x00000002; // Enable right wheel
			PWM0_ENABLE_R &= ~0x00000001; // Disable left wheel
		}
		else if(dir == 'R'){
			LED = Purple;
			DIRECTION = FORWARD;
			PWM0_ENABLE_R &= ~0x00000002; // Disable right wheel
			PWM0_ENABLE_R |= 0x00000001; // Enable left wheel
		}
		else if(dir == 'S'){
			LED = Dark;
			PWM0_ENABLE_R &= ~0x00000003;
		}
		else if(dir == 'U'){
			PWM_PB76_Duty(16000*0.9, 16000*0.9);
		}
		else if(dir == 'D'){
			PWM_PB76_Duty(16000*0.5,16000*0.5);
		}
	}
}
