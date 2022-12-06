/*
	Interface between Racing wheel and XINPUT Controller library
  Compatible w/ PC
  
	Developer: Daniel Nesvera
	
	WTFPL lincense

*/

#include "stm32_xinput.h"
#include "xinput.h"
#include "math.h"

#define LeftStickVer_Pin GPIO_PIN_0
#define LeftStickVer_GPIO_Port GPIOA
#define LeftStickHori_Pin GPIO_PIN_1
#define LeftStickHori_GPIO_Port GPIOA
#define LeftTrigger_Pin GPIO_PIN_2
#define LeftTrigger_GPIO_Port GPIOA
#define RightTrigger_Pin GPIO_PIN_3
#define RightTrigger_GPIO_Port GPIOA
#define RightStickHori_Pin GPIO_PIN_4
#define RightStickHori_GPIO_Port GPIOA
#define RightStickVer_Pin GPIO_PIN_5
#define RightStickVer_GPIO_Port GPIOA
#define A_Pin GPIO_PIN_7
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_0
#define B_GPIO_Port GPIOB
#define X_Pin GPIO_PIN_1
#define X_GPIO_Port GPIOB
#define Y_Pin GPIO_PIN_10
#define Y_GPIO_Port GPIOB
#define RB_Pin GPIO_PIN_11
#define RB_GPIO_Port GPIOB
#define Dright_Pin GPIO_PIN_12
#define Dright_GPIO_Port GPIOB
#define LB_Pin GPIO_PIN_13
#define LB_GPIO_Port GPIOB
#define Dup_Pin GPIO_PIN_14
#define Dup_GPIO_Port GPIOB
#define Ddown_Pin GPIO_PIN_15
#define Ddown_GPIO_Port GPIOB
#define Dleft_Pin GPIO_PIN_8
#define Dleft_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_9
#define LED_GPIO_Port GPIOA
#define L3_Pin GPIO_PIN_15
#define L3_GPIO_Port GPIOA
#define SELECT_Pin GPIO_PIN_3
#define SELECT_GPIO_Port GPIOB
#define START_Pin GPIO_PIN_4
#define START_GPIO_Port GPIOB
#define R3_Pin GPIO_PIN_5
#define R3_GPIO_Port GPIOB



// Initiate 
int16_t wheelEncoderValue = 0;
uint16_t handbrakeValue = 0;
int16_t leftTriggerValue_ADC = 0;
int16_t rightTriggerValue_ADC = 0;
int16_t xLeftStickValue_ADC = 0;
int16_t yLeftStickValue_ADC = 0;
int16_t xRightStickValue_ADC = 0;
int16_t yRightStickValue_ADC = 0;

int8_t adcValueReady = 0;
int16_t leftTriggerValue = 0;
int16_t rightTriggerValue = 0;
int16_t xLeftStickValue = 0;
int16_t yLeftStickValue = 0;
int16_t xRightStickValue = 0;
int16_t yRightStickValue = 0;

struct _pin digitalArray[NUM_BUTTONS];
struct _pin analogArray[NUM_ANALOG];
struct _pin encoderPins[2];

/* Declare port, pin and state of all buttons
*
*/
void declareButtonPins(){
	digitalArray[0].port  = A_GPIO_Port;		digitalArray[0].pin  = A_Pin;		digitalArray[0].state  = 0;		// A
	digitalArray[1].port  = B_GPIO_Port;		digitalArray[1].pin  = B_Pin;		digitalArray[1].state  = 0;		// B
	digitalArray[2].port  = X_GPIO_Port;		digitalArray[2].pin  = X_Pin;		digitalArray[2].state  = 0;		// X
	digitalArray[3].port  = Y_GPIO_Port;		digitalArray[3].pin  = Y_Pin;		digitalArray[3].state  = 0;		// Y
	digitalArray[4].port  = LB_GPIO_Port;		digitalArray[4].pin  = LB_Pin;		digitalArray[4].state  = 0;		// LB	
	digitalArray[5].port  = RB_GPIO_Port;		digitalArray[5].pin  = RB_Pin;		digitalArray[5].state  = 0;		// RB
	digitalArray[6].port  = L3_GPIO_Port;		digitalArray[6].pin  = L3_Pin;		digitalArray[6].state  = 0;		// L3
	digitalArray[7].port  = R3_GPIO_Port;		digitalArray[7].pin  = R3_Pin;		digitalArray[7].state  = 0;		// R3
	digitalArray[8].port  = START_GPIO_Port;		digitalArray[8].pin  = START_Pin;		digitalArray[8].state  = 0;		// START
	digitalArray[9].port  = SELECT_GPIO_Port;		digitalArray[9].pin  = SELECT_Pin;		digitalArray[9].state  = 0;		// BACK
	digitalArray[10].port = NULL;		digitalArray[10].pin = NULL;		digitalArray[10].state = 0;		// XBOX-LOGO
	digitalArray[11].port = Dup_GPIO_Port;		digitalArray[11].pin = Dup_Pin;		digitalArray[11].state = 0;		// D-UP	
	digitalArray[12].port = Ddown_GPIO_Port;		digitalArray[12].pin = Ddown_Pin;		digitalArray[12].state = 0;		// D-DOWN
	digitalArray[13].port = Dleft_GPIO_Port;		digitalArray[13].pin = Dleft_Pin;		digitalArray[13].state = 0;		// D-LEFT
	digitalArray[14].port = Dright_GPIO_Port;		digitalArray[14].pin = Dright_Pin;		digitalArray[14].state = 0;		// D-RIGHT
}

/* Declare port, pin of the analog inputs
*
*/
void declareAnalogPins(){
	analogArray[0].port = NULL;		analogArray[1].pin = NULL;		analogArray[1].state = 0;			// LEFT TRIGGER
	analogArray[1].port = NULL;		analogArray[2].pin = NULL;		analogArray[2].state = 0;			// RIGHT TRIGGER
	analogArray[2].port = RightStickHori_GPIO_Port;		analogArray[5].pin = RightStickHori_Pin;		analogArray[5].state = 0;			// X RIGHT STICK
	analogArray[3].port = RightStickVer_GPIO_Port;		analogArray[6].pin = RightStickVer_Pin;		analogArray[6].state = 0;			// Y RIGHT STICK
	analogArray[4].port = LeftStickHori_GPIO_Port;		analogArray[3].pin = LeftStickHori_Pin;		analogArray[3].state = 0;			// X LEFT STICK		
	analogArray[5].port = LeftStickVer_GPIO_Port;		analogArray[4].pin = LeftStickVer_Pin;		analogArray[4].state = 0;			// Y LEFT STICK		
	
}

/*	Declare port, pin of the encoder
*
*/
void declareEncoderPins(){
	encoderPins[0].port = NULL;		encoderPins[0].pin = NULL;		encoderPins[0].state = 0;			// Encoder input A - interrupt pin
	encoderPins[1].port = NULL;		encoderPins[1].pin = NULL;		encoderPins[1].state = 0;			// Encoder input B - normal input
}

/*	Read/update buttons and potentiometer of the handrake
*
*/
void readButtons(){
	int i = 0;
	int state = 1;
	uint8_t buttonArray[11] = {0,0,0,0,0,0,0,0,0,0,0};				// initialize array of buttons
	uint8_t dpadArray[4] = {0,0,0,0};													// initialize array from dpad
		
	while( i < NUM_BUTTONS ){
		
		if( digitalArray[i].port != NULL ){
			
			// 0 = PRESSED		1 = NOT PRESSED
			state = HAL_GPIO_ReadPin( digitalArray[i].port, digitalArray[i].pin );	// read buttons, button is active-low
			
			if( i <= 10 ){		// Buttons
				buttonArray[i] = !state;
				
			}else{					// D-PAD
				//dpadArray[i-11] = state;
			}
		}
		
		i++;
	}
			
	XINPUT_buttonArrayUpdate( buttonArray );																					// update buttons
	
	dpadArray[0] = !HAL_GPIO_ReadPin( digitalArray[11].port, digitalArray[11].pin );
	dpadArray[1] = !HAL_GPIO_ReadPin( digitalArray[12].port, digitalArray[12].pin );
	dpadArray[2] = !HAL_GPIO_ReadPin( digitalArray[13].port, digitalArray[13].pin );
	dpadArray[3] = !HAL_GPIO_ReadPin( digitalArray[14].port, digitalArray[14].pin );
	
	XINPUT_dpadUpdate( dpadArray[0], dpadArray[1], dpadArray[2], dpadArray[3] );			// update dpad

}

/*	Read input values from sticks and triggers
*
*/

#define STICK_16_MAX 50000
#define STICK_16_MIN -50000

#define INT16MAX 32767
#define INT16MIN -32767

void readAdcValues(){
	
	if( adcValueReady == 1 ){
		rightTriggerValue = (uint8_t)map( 0, 0, 4040, 0, UINT8_MAX );
		leftTriggerValue 	= (uint8_t)map( 0, 0, 4040, 0, UINT8_MAX );
		
		if (xLeftStickValue_ADC<2020) {
			int32_t tmp = restrict(xLeftStickValue_ADC, 752, 2020);
			xLeftStickValue = (int16_t)map( tmp, 752, 2020, INT16MIN, 0 );
		}else {
			int32_t tmp = restrict(xLeftStickValue_ADC, 3261, 2020);
			xLeftStickValue = (int16_t)map( tmp, 2020, 3261, 0, INT16MAX );
		}
		
		if (yLeftStickValue_ADC<2020) {
			int32_t tmp = restrict(yLeftStickValue_ADC, 895, 2020);
			yLeftStickValue = (int16_t)map( tmp, 895, 2020, INT16MAX, 0 );
		}else {
			int32_t tmp = restrict(yLeftStickValue_ADC, 3211, 2020);
			yLeftStickValue = (int16_t)map( tmp, 2020, 3211, 0, INT16MIN );
		}
		
		if (xRightStickValue_ADC<2020) {
			int32_t tmp = restrict(xRightStickValue_ADC, 816, 2020);
			xRightStickValue = (int16_t)map( tmp, 816, 2020, INT16MAX, 0 );
		}else {
			int32_t tmp = restrict(xRightStickValue_ADC, 3225, 2020);
			xRightStickValue = (int16_t)map( tmp, 2020, 3225, 0, INT16MIN );
		}
		
		if (yRightStickValue_ADC<2020) {
			int32_t tmp = restrict(yRightStickValue_ADC, 922, 2020);
			yRightStickValue = (int16_t)map( tmp, 922, 2020, INT16MIN, 0 );
		}else {
			int32_t tmp = restrict(yRightStickValue_ADC, 3185, 2020);
			yRightStickValue = (int16_t)map( tmp, 2020, 3185, 0, INT16MAX );
		}
		
		
		adcValueReady = 0;
	}
	
}

/*	Update brake and throttle triggers
*
*/
void updateTriggers(){
		
	XINPUT_triggerUpdate(leftTriggerValue, rightTriggerValue);
}

/*	Update right and left sticks
*			LeftStick X-axis comes from steering wheel
*			RightStick comes from potentiometers
*/
void updateSticks(){

	XINPUT_stickUpdate(STICK_LEFT, xLeftStickValue, yLeftStickValue);
	XINPUT_stickUpdate(STICK_RIGHT, xRightStickValue, yRightStickValue );
	
}

/*	Re-maps a number from one range to another
*
*/
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int32_t restrict(int32_t x, int32_t max, int32_t middle) {
	if (max>middle) {
		if (x>max) {return max;}
		else {return x;}
	} else {
	if (x<max) {return max;}
		else {return x;}
	}
}
