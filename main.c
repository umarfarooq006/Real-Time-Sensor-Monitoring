///////////main///////////
#include "header.h"

#define LED       (1U<<5)
#define FLAME     ((IOPIN0>>14)&1)
#define VIBRATION ((IOPIN0>>15)&1)

int main()
{
    unsigned int adc;
    float temp, pot;
    unsigned int ldr;

    // Pin configuration
    PINSEL0 &= ~0xF0000000;

    IODIR0 |= LED;
    IODIR0 &= ~((1U<<14)|(1U<<15));

    // Initialize peripherals
    uart_init(9600);
    adc_init();
    vic_for_timer1();

    while(1)
    {
        // Temperature sensor
        if(task[0] == 1)
        {
            task[0] = 0;

            adc = adc_read(1);
            temp = (adc * 3.3 * 100) / 1023;

            uart_str("\r\nTemperature: ");
            uart_float(temp);
            uart_str(" C");

            if(temp > 35)
                IOCLR0 = LED;
            else
                IOSET0 = LED;
        }

        // Potentiometer
        if(task[1] == 1)
        {
            task[1] = 0;

            adc = adc_read(2);
            pot = (adc * 3.3) / 1023;

            uart_str("\r\nVoltage: ");
            uart_float(pot);
            uart_str(" V");
        }

        // LDR sensor
        if(task[2] == 1)
        {
            task[2] = 0;

            adc = adc_read(3);
            ldr = (adc * 100) / 1023;

            uart_str("\r\nLight: ");
            uart_int(ldr);
            uart_str("%");
        }

        // Flame sensor
        if(task[3] == 1)
        {
            task[3] = 0;

            if(FLAME == 0)
                uart_str("\r\nFlame Detected");
            else
                uart_str("\r\nFlame Not Detected");
        }

        // Vibration sensor
        if(task[4] == 1)
        {
            task[4] = 0;

            if(VIBRATION == 1)
                uart_str("\r\nVibration Detected");
            else
                uart_str("\r\nVibration Not Detected");
        }
    }
}