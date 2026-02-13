// where is the LED connected
// port
// pin

#define PERIPH_BASE  (0x40000000UL)
#define AHB1OFFSET (0x00020000UL)
#define AHB1BASE   (PERIPH_BASE + AHB1OFFSET)
#define GPIOAOFFSET (0x0000UL)

#define GPIOBASE   (GPIOAOFFSET + AHB1BASE)
#define RCCOFFSET (0x3800UL)
#define RCCBASE (AHB1BASE + RCCOFFSET)

#define RCC_AHB1EN_OFFSET (0x30UL)
#define RCC_AHB1EN_R (*(volatile unsigned int *)(RCCBASE + RCC_AHB1EN_OFFSET))

#define GPIOx_MODER_OFFSET (0x00UL)
#define GPIO_MODE_R (*(volatile unsigned int *)(GPIOBASE + GPIOx_MODER_OFFSET))

#define ODR_OFFSET (0x14UL)
#define GPIOA_OD_R (*(volatile unsigned int *)(GPIOBASE + ODR_OFFSET))

#define GPIOAEN_R (1U<<0)   // enable GPIOA clock

#define PIN5 (1U<<5)
#define LED_PIN PIN5

int main (void )
{
    // enable clock access to GPIOA
    RCC_AHB1EN_R |= GPIOAEN_R;

    // set PA5 as output pin
    GPIO_MODE_R |= (1U<<10);
    GPIO_MODE_R &= ~(1U<<11);

    while(1)
    {
        // toggle PA5 LED pin
        GPIOA_OD_R ^= LED_PIN;
        for(int i = 0; i < 10000; i++){}

        // set PA5 pin low to turn LED OFF
        GPIOA_OD_R &= ~LED_PIN;
        for(int i = 0; i < 10000; i++){}
    }
}
