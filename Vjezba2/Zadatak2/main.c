#include <avr/io.h>
#include <avr/interrupt.h>
#define POD_A
unsigned char slika_led = 0xFF;
unsigned char t0_cnt = 0;
ISR(TIMER0_COMPA_vect)
{
 //prekid tajmera 0 usled dostizanja vrednosti registra OCR0A
 t0_cnt++;
}
int main()
{

 DDRD = 0xff; //port D -> izlaz
 DDRB |= 1 << 4; //PB4 -> izlaz
 PORTB &= ~(1 << 4); //PB4 = 0, cime se ukljucuje tranzistor Q0

 //inicijalizacija tajmera 0:
 TCCR0A = 0x02; //tajmer 0: CTC mod

 TCCR0B = 0x03; //tajmer 0: fclk = fosc/64
 OCR0A = 123; //perioda tajmera 0: 124 Tclk (OCR0A + 1 = 124)

 TIMSK0 = 0x02; //dozvola prekida tajmera 0
 //usled dostizanja vrednosti registra OCR0A

 sei(); //I = 1 (dozvola prekida)
 
 while(1)
 {

 if (t0_cnt){
 t0_cnt = 0;
 slika_led ^= 0x01;
 PORTD = slika_led;
 }
 }
 return 0;
}