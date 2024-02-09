#include "timers.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

volatile typedef struct timers{
		uint32_t startTime;
		uint32_t remainTime;
		uint8_t isActive;
		callBackFuncT callbackFunc;
	}customTimer;

volatile customTimer timerArray[5];


ISR(TIMER1_OVF_vect){
	for(int i = 0; i < 5; i++){
		if(timerArray[i].isActive == 1){
			timerArray[i].remainTime--;
			if(timerArray[i].remainTime <= 0){
				cli();
				timerArray[i].callbackFunc();
				timerArray[i].isActive = 0;
				sei();
			}
	
		}
	}
}

void initCoustomTimers(){
	
	TIMSK1 |= (1<<TOIE1);
	//prescaling Timer 1(64)
	TCCR1B &= ~(1<<CS12); //set bit 2 to 0
	TCCR1B |= (1<<CS11); //set bit 1 to 1
	TCCR1B |= (1<<CS10); //set bit 0 to 1
	TCNT1 = 65286;
	
	for(int i = 0; i < 5 ; i++){
		
		timerArray[i].startTime = 0;
		timerArray[i].remainTime = 0;
		timerArray[i].isActive = 0;
		timerArray[i].callbackFunc = 0;
		
	}
}

void declareTimer(uint8_t i, uint8_t duration, callBackFuncT callback)
{
	timerArray[i].startTime = duration; 
	timerArray[i].callbackFunc = callback;
}

void startTimer(uint8_t i)
{
	timerArray[1].remainTime = timerArray[1].startTime;
	timerArray[i].isActive = 1;
}

void deleteTimer(uint8_t i)
{
	timerArray[i].startTime = 0;
	timerArray[i].remainTime = 0;
	timerArray[i].isActive = 0;
	timerArray[i].callbackFunc = 0;
}
