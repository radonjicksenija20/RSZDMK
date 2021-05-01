/*
 * main.c
 *
 *  Created on: Apr 9, 2021
 *      Author: KSENIJA
 */



volatile unsigned long ms = 0;
unsigned char fi=0 ;
unsigned char smjer=1;

int main()
{
	DDRB |= 1 << 5;
	timer0InteruptInit();



	while(1);
}



/*******************************************************************/

void timer0InteruptInit()
{
	// Inicijalizacija tajmera 0 tako da perioda prekida bude 10us
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	OCR0A = 159;
	TIMSK0 = 0x02;

	// Podesavanje globalne dozvole prekida
	sei();
}

/******************************************************************************************/

ISR(TIMER0_COMPA_vect)
{
	// Inkrementovanje broja milisekundi koje su prosle od pokretanja aplikacije je 10us
	ms++;
	if(ms == 781){
		ms=0;

		if(smjer){
			fi++;
			if(fi==255)
				smjer=0;
		}
		else{
			fi--;
			if(smjer==0)
				smjer=1;
		}
	}

	if(ms<fi)
		PORTB |= 1<<5;
	else
	    PORTB &= ~(1<<5);

}

/********************************************************************************************/

