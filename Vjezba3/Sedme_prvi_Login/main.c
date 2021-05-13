/**
 * @file   main.c
 * @brief   Glavna Petlja
 * @author Radonjic Ksenija
 * @date    13 - 05 - 2021
 * @version 1.0
 * */


#include "usart.h"
#include <util/delay.h>
#include <stdint.h>

/**
 * Provjera -  Funkcija  provjerava jednakost rijeci
 * @param - predefinisana_rijec - rijec koju imamo
 * @param - nova_rijec - onu koju unosimo preko serijskog
 * @param - duzina - duzina rijeci
 * @return - res - vraca 1 ukoliko je tacno a 0 ako nije
 * */
int8_t Provjera(int8_t predefinisana_rijec[], int8_t nova_rijec[], int8_t duzina)
{
	int8_t res=0;
	if(duzina == sizeof(predefinisana_rijec))
	{
		res=1;
		for(int i = 0 ; i < duzina ; i++)
		{
			if(nova_rijec[i] != predefinisana_rijec[i])
			     res=0;
		}
	}
	return res;
}

int main()
{
	///predefinisane vrijednosti
	int8_t USERNAME[64]= "radonjicksenija";
	///predefinisane vrijednosti
	int8_t PASSWORD [64]="kaktus";

	usartInit(9600);
	int8_t lozinka[64];
	int8_t korisnicko_ime[64];
	int8_t duzina1, duzina2;

	while(1)
	{
		usartPutString("Unesite username: \r \n");
		while(!usartAvailable());
		_delay_ms(500);

		duzina1=usartGetString(korisnicko_ime);
		korisnicko_ime[duzina1]= '\0';

		usartPutString("Unesite lozinku: \r \n");
		while(!usartAvailable());
		duzina2=usartGetString(lozinka);
		lozinka[duzina2]= '\0';

		_delay_ms(500);

		if(Provjera(USERNAME, korisnicko_ime , duzina1) && Provjera(PASSWORD, lozinka, duzina2))
		{
			usartPutString("Dobrodosli, ");
		    usartPutString(korisnicko_ime);
		    usartPutString(" \r\n");
		}
		else
		{
			usartPutString("Logovanje neuspjesno '\0'");
		}

	}


	return 0;
}
