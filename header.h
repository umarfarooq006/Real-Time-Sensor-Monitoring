#ifndef HEADER_H
#define HEADER_H

#include <LPC21xx.H>

// UART functions
void uart_init(unsigned int baud);
void uart_tx(unsigned char ch);
char uart_rx(void);
void uart_str(char *p);
void uart_int(int num);
void uart_float(float num);

// ADC functions
void adc_init(void);
unsigned int adc_read(unsigned int ch);

// Timer1 function
void vic_for_timer1(void);

// Delay functions
void delay_sec(unsigned int sec);
void delay_ms(unsigned int ms);

// Task array
extern volatile int task[5];

#endif