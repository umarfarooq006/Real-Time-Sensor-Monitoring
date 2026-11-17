//////////timer//////////
#include "header.h"

volatile int task[5] = {0};
unsigned int count = 0;

// Timer1 interrupt function
void timer1_handler(void) __irq
{
    T1IR = 1;

    count++;

    if(count == 10)
        task[0] = 1;

    if(count == 13)
        task[1] = 1;

    if(count == 16)
        task[2] = 1;

    if(count == 18)
        task[3] = 1;

    if(count == 20)
    {
        task[4] = 1;
        count = 0;
    }

    VICVectAddr = 0;
}

// Timer1 initialization
void vic_for_timer1(void)
{
    // Reset Timer1
    T1TCR = 0x02;

    // Timer interval = 1 ms per count
    T1PR = 15000 - 1;

    T1TC = 0;
    T1PC = 0;

    // Match register
    T1MR0 = 100;

    // Generate interrupt and reset timer
    T1MCR = 3;

    // Configure VIC
    VICIntSelect &= ~(1U << 5);
    VICVectAddr0 = (unsigned int)timer1_handler;
    VICVectCntl0 = (1U << 5) | 5;

    // Enable interrupt
    VICIntEnable = (1U << 5);

    // Start Timer1
    T1TCR = 1;
}