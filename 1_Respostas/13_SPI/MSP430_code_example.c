#include <msp430g2553.h>

#define MISO BIT1
#define MOSI BIT2
#define SCLK BIT4

#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)

#define DLY1 0x6000
#define DLY2 0x3000

void delay(volatile unsigned int t)
{
    while (t--)
        ;
}

void Send_Data(volatile unsigned char c)
{
    while ((IFG2 & UCA0TXIFG) == 0)
        ;
    UCA0TXBUF = c;
}

void blink(unsigned char pin, char qnt, unsigned int t)
{
    qnt <<= 1;

    while(qnt--)
    {
        P1OUT ^= pin;
        delay(t);
    }
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1SEL2 = P1SEL = MOSI + MISO + SCLK;

    P1DIR |= LEDS;
    P1OUT &= ~LEDS;

    UCA0CTL1 = UCSWRST + UCSSEL_3;
    UCA0CTL0 = UCCKPH + UCMSB + UCMODE_0 + UCSYNC;
    UCA0CTL1 &= ~UCSWRST;

    Send_Data(10);

    IE2 |= UCA0RXIE;

    blink(LEDS, 1, DLY1);

    _BIS_SR(LPM0_bits + GIE);

    return 0;
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void Receive_Data (void)
{
    volatile unsigned char c = UCA0RXBUF;

    P1OUT ^= LED1;

    if (c < 6)
    {
        blink(LED2, c, DLY1);
        Send_Data(c);
    }

    IFG2 &= ~UCA0RXIFG;
    P1OUT ^= LED1;
}
