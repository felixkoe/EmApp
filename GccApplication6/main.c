#include "./defines.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "./timers.h"

volatile uint16_t counter = 0;

volatile uint16_t previousState = 0;

volatile uint8_t event = 0;

volatile uint8_t timer0OverflowCounter = 0;

void InterruptInnit(){
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);
	
	//Prescaller einstellen
	TCCR0B |= (1 << CS00) | (1 << CS02);
	TCCR0B &= ~(1 << CS01);
	//8Bit Timer0 anschalten
	TIMSK0 |= (1 << TOIE0);
	
}

void TimerInnit(){
	//Timer Modus festlegen hier Normal Mode
	TCCR0A &= ~(1 << WGM00); 
	TCCR0A &= ~(1 << WGM01); 
	TCCR0B &= ~(1 << WGM02); 
	
	//Compare MAtch Output Ausschalten
	TCCR0A &= ~(1 << COM0A0);
	TCCR0A &= ~(1 << COM0A1);
	
	
}

void PinInnit(){
	
	//set Pins as Output
	DDRB |= (1<<DDB1) | (1<<DDB0) | (1<<DDB2);
	DDRD |= (1<<DDD7) | (1<<DDD3);
	
	//D7, B1, B0 Rote LED
	//D3 Gelbe LED
	//B2 Grüne LED
	
	//Make Pins HIGH or LOW to set start value
	
	//HIGH
	//PORTB |= (1<<DDB2);
	//LOW
	PORTB &= ~(1<<PORTB1);
	PORTB &= ~(1<<PORTB0);
	PORTB &= ~(1<<PORTB2);
	PORTD &= ~(1<<PORTD7);
	PORTD &= ~(1<<PORTD3);
	
	//set Pins as Input
	DDRD &= ~(1<<DDD6);
	
	//enable Pull Up Resistor
	PORTD |= (1<<PORTD6);
	PORTD |= (1<<PORTD2);
	
}

void setEvent(uint8_t e){
	event |= e;
}

void deleteEvent(uint8_t e){
	event &= ~e;
}

int isEventSet(uint8_t e){
	if(event & e){
		return 1;
	}
	else{
		return 0;
	}
}



ISR(INT0_vect){
	//do something if Ext-Interrupt is triggered
	setEvent(e1);
}

ISR(PCINT0_vect){
	//do something if Interrupt is triggered
}

ISR(TIMER0_OVF_vect){
	timer0OverflowCounter++;

	if(timer0OverflowCounter >= 61){
		PORTD ^= (1 << PIND3);
		timer0OverflowCounter = 0;
	}
}

int flanken(uint16_t currentState){
	if(currentState){
		previousState = 1;
		return 0;
	}
	else{
		if(previousState == 1){
			previousState == 0;
			return 1;
		}
		else
		{
			previousState == 0;
			return 0;
		}
	}
}

void led_counter(uint16_t counter){
	if((counter & (1)) != 0){
		PORTB |= (1<<PORTB1);
	}
	
	else{
		PORTB &= ~(1<<PORTB1);
	}
	if((counter & (1 << 1)) != 0){
		PORTB |= (1<<PORTB0);
	}
	else{
		PORTB &= ~(1<<PORTB0);
	}
	
	if((counter & (1 << 2)) != 0){
		PORTD |= (1<<PORTD7);
	}
	else{
		PORTD &= ~(1<<PORTD7);
	}
}

int main(void)
{
	//initialize Pins
	PinInnit();
	
	//initialize Interrupts
	InterruptInnit();
	sei();
	
	//initialize Timers
	TimerInnit();
	
	
	while (1)
	{
		/*
		if(isEventSet(e1)){
			PORTD |= (1<<PORTD3);
		}
		else{
			PORTD &= ~(1<<PORTD3);
		}
		
		if (flanken(PIND & (1 << PIND6)) == 1) {
			deleteEvent(e1);
		}
		
		if(!isEventSet(e1)){
			
			PORTB |= (1<<PORTB2);
			
			if(counter <= 7){
				led_counter(counter);
				counter++;
			}
			else{
				led_counter(counter);
				counter = 0;
			}
		}
		else{
			PORTB &= ~(1<<PORTB1);
			PORTB &= ~(1<<PORTB0);
			PORTD &= ~(1<<PORTD7);
			PORTB &= ~(1<<PORTB2);
			PORTD |= (1<<PORTD2);
			
			counter = 0;
		}
		_delay_ms(300);*/
	}
}