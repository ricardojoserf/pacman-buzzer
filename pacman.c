
#include <msp430.h>

void setBuzzer(int frec);
void setBuzzer2(int frec);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Variables globales //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

#define CONSTANTE 6

#define in			5
#define f	 		60
#define sc   		100
#define scP  		140
#define c 			200
#define cP		 	300
#define n 			400
#define b 			800

#define doo   262
#define doS   277
#define re    294
#define reS   311
#define mi    330
#define fa    349
#define faS   370
#define sol   392
#define solS  415
#define la    440
#define laS   466
#define si    494
#define do2   523
#define doS2  554
#define re2   587
#define reS2  622
#define mi2   659
#define fa2   698
#define faS2  740
#define sol2  784
#define solS2 831
#define la2   880
#define laS2  932
#define si2   988
#define do3   1046
#define doS3  1109
#define a  100000
#define s 1000000

#define NUM_SEGUNDOS 2200


const int frecArray[] = {si  ,si2,faS2,reS2, si2,faS2, reS2,
						 do2 ,do3,sol2, mi2, do3,sol2,  mi2,
						 si  ,si2,faS2,reS2, si2,faS2, reS2,
						 a, reS2,mi2,fa2, a, fa2,faS2,sol2, a, sol2,solS2,la2, a, la2,laS2,si2,s};

const int timeArray[] = {sc , sc,  sc,  sc,f, scP,    c,
						 sc , sc,  sc,  sc,f, scP,    c,
						 sc , sc,  sc,  sc,f, scP,    c,
						 in, f,f,sc, in, f,f,sc,  in, f,f,sc,  in, f,f, c,sc};


volatile int tiempo = 0;


//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Función  //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



void pacman() {

	int i, j;
	for (i = 0; i < 38; i++) {
		setBuzzer(frecArray[i]);
		for (j = 0; j < timeArray[i] * CONSTANTE / 5; j++) {
			__delay_cycles(16000);
		}
	}



}


void setBuzzer(int frec){
	TA0CCR0 = (31250/frec)*256;
	TA0CCR1 = TA0CCR0>>1;
}

void setBuzzer2(int frec){
	TA1CCR0 = (31250/frec)*256;
	TA1CCR1 = TA1CCR0>>1;
}
int main(void)
{
	// Configuracion del chip

	WDTCTL = WDTPW + WDTHOLD;         // Stop WDT
	BCSCTL1 = CALBC1_16MHZ;          // Set range
	DCOCTL = CALDCO_16MHZ;           // Set DCO step + modulation

	P1DIR |= BIT2;                            // P1.2 output
	P1SEL |= BIT2;                            // P1.2 TA1/2 options
	P2DIR |= BIT2;                            // P2.2  output
	P2SEL |= BIT2;                            // P2.2 TA1/2 options
	P2SEL2 = 0;

	TA0CCR0 = 8000-1;                             // PWM Period
	TA0CCTL1 = OUTMOD_7;                         // CCR1 reset/set
	TA0CCR1 = TA0CCR0>>1;                               // CCR1 PWM duty cycle
	TA0CTL = TASSEL_2 + MC_1 + ID_1;                  // SMCLK, up mode

	/*TA1CCTL0 = CCIE;
	TA1CCR0 = 1000;					// Int. de 1KHz
	TA1CTL = TASSEL_2 + MC_2;
*/
	TA1CCR0 = 8000-1;                             // PWM Period
	TA1CCTL1 = OUTMOD_7;                         // CCR1 reset/set
	TA1CCR1 = TA1CCR0>>1;                               // CCR1 PWM duty cycle
	TA1CTL = TASSEL_2 + MC_1 + ID_1;                  // SMCLK, up mode

	_enable_interrupts();

	// fin de configuracion del chip


	//setBuzzer(262);

	//Bucle infinito dentro del main
	for(;;){
		pacman();
	}
}
/*
// Timer A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{

	tiempo++;
}
*/
