/////////ADC/////////
#include "header.h"

// ADC initialization
void adc_init(void)
{
    // Configure ADC pins P0.28, P0.29, P0.30
    PINSEL1 = (PINSEL1 & ~0x3FC00000) | 0x15400000;

    // Enable ADC and set clock divider
    ADCR = 0x00200400;
}

// Read ADC value
unsigned int adc_read(unsigned int ch)
{
    unsigned int value;

    if(ch > 7)
        return 0;

    // Select ADC channel
    ADCR &= ~0xFF;
    ADCR |= (1U << ch);

    // Start conversion
    ADCR &= ~(7U << 24);
    ADCR |= (1U << 24);

    // Wait until conversion completes
    while((ADDR & (1U << 31)) == 0);

    // Read 10-bit ADC value
    value = (ADDR >> 6) & 0x3FF;

    // Stop conversion
    ADCR &= ~(7U << 24);

    // Clear channel selection
    ADCR &= ~(1U << ch);

    return value;
}