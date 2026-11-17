////////uart//////////
#include "header.h"

// UART initialization
void uart_init(unsigned int baud)
{
    unsigned int pclk = 15000000;
    unsigned int dl;

    if(baud == 0)
        return;

    dl = pclk / (16 * baud);

    // Select UART0 pins
    PINSEL0 = (PINSEL0 & ~0xF) | 0x5;

    // Enable DLAB
    U0LCR = 0x83;

    // Set baud rate
    U0DLL = dl & 0xFF;
    U0DLM = (dl >> 8) & 0xFF;

    // 8-bit data, 1 stop bit
    U0LCR = 0x03;
}

// Transmit one character
void uart_tx(unsigned char ch)
{
    while((U0LSR & (1<<5)) == 0);

    U0THR = ch;
}

// Receive one character
char uart_rx(void)
{
    while((U0LSR & 1) == 0);

    return U0RBR;
}

// Transmit string
void uart_str(char *p)
{
    while(*p)
    {
        uart_tx(*p);
        p++;
    }
}

// Transmit integer
void uart_int(int num)
{
    int i = 0;
    char a[10];

    if(num == 0)
    {
        uart_tx('0');
        return;
    }

    if(num < 0)
    {
        uart_tx('-');
        num = -num;
    }

    while(num > 0)
    {
        a[i] = (num % 10) + '0';
        num = num / 10;
        i++;
    }

    for(i = i-1; i >= 0; i--)
    {
        uart_tx(a[i]);
    }
}

// Transmit float
void uart_float(float num)
{
    int whole, fraction;

    if(num < 0)
    {
        uart_tx('-');
        num = -num;
    }

    whole = (int)num;
    fraction = (int)((num - whole) * 100 + 0.5);

    if(fraction >= 100)
    {
        whole++;
        fraction = 0;
    }

    uart_int(whole);

    uart_tx('.');

    uart_tx((fraction / 10) + '0');
    uart_tx((fraction % 10) + '0');
}