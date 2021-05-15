/**
 *  @file ime_datoteke.c
 *  @brief Glavna petlja
 *  @author Ksenija Radonjic
 *  @date 12 - 05 - 2021
 *  @version 1.0
 *
 */


#include "../Biblioteka_sedme/usart.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

///MAKRO za broj korisnika
#define BROJ_KORISNIKA 10

char baza [BROJ_KORISNIKA] [32]=
{
		"Ime1",
		"Ime2",
		"Ime3",
		"Ime4",
		"Ime5"
};

char pinovi[BROJ_KORISNIKA][4]=
{
		"1234",
		"2345",
		"4568",
		"3456",
		"5555"
};




int main()
{
	char ime[64] ;
	int8_t duzina;
	char PIN[4];
	int8_t str[64];
	char zvjezdice[5] = "*";
	int8_t x;


	while(1)
	{
		usartPutString("Unesite ime i prezime:");
		while(!usartAvailable());
		 _delay_ms(500);

		duzina=usartGetString(ime);
        ime[duzina]= '/0';

        int8_t rez=0;
       	int8_t pomocna_za_niz;

        for(int8_t i=0 ; i < BROJ_KORISNIKA ; i++)
        {
        	if(duzina == strlen(baza[i]))
        	{
               x=1;
				for(int8_t j=0 ; j < duzina ; j++)
				{
						if(ime[j] != baza [i] [j])
						{
								x=0;
								break;
						}
				}
        	}
				if(x == 1)
				{
					rez = 1;
					pomocna_za_niz = i;
					break;
				}
        }

        if(!rez)
        {
        	usartPutString("Pogresno unijeto ime");
        }
        else
        {
			usartPutString("Unosite PIN jedan po jedan broj:");

			for(int8_t i=3 ; i >= 0 ; i--)
			{
				while(!usartAvailable());
				_delay_ms(1000);
				PIN [i] = usartGetChar() ;
				usartPutString(zvjezdice);
			}

			int8_t res = 1;
			for(int8_t i=0 ; i < 4 ; i++)
			{
					if(PIN[i] != pinovi[pomocna_za_niz][i])
					{
						res = 0;
						 break;
					}
			}

			if(res)
				 usartPutString("Tacan je pin");
			else
				 usartPutString("Netacan je pin");
			}
	}
        return 0;
}
