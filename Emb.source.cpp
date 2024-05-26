void servo_rotate(int pulse_width);
void interrupt(void);
void PWM(unsigned int p, unsigned int d);
void PWM1(unsigned int p, unsigned int d);
void PWMdelay(unsigned int d, unsigned int speed);
void mymsdelay(unsigned int d);
void delay_2s();

void main()
{
    // Initialize variables
    unsigned int speed = 50;

    // Configure interrupts
    INTCON = INTCON | 0x90;

    // Configure OPTION_REG
    OPTION_REG = OPTION_REG & 0xBF;

    // Configure port directions
    TRISD = 0x00;
    TRISC = 0X00;
    PORTC = 0x00;
    TRISB = 0x01;
    PORTB = 0x00;

    // Main loop
    while (1)
    {
        // Call PWM function with period = 10 and speed = 50
        PWM(10, speed);
    }
}

// Interrupt Service Routine
void interrupt(void)
{
    // Set servo speed
    unsigned int speed1 = 70;

    // Reset PORTD and delay for 2 seconds
    PORTD = 0x00;
    delay_2s();

    // Call PWMdelay function with duration 150 and speed1
    PWMdelay(150, speed1);

    // Rotate servo with pulse width of 400
    servo_rotate(400);

    PORTD = 0x05;
    delay_2s();
    PORTD = 0X00;
    servo_rotate(100);
    // Clear interrupt flag
    INTCON = INTCON & 0xFD;
}

// PWM function to generate PWM signal on PORTD
void PWM(unsigned int p, unsigned int d)
{
    unsigned int period = p;
    unsigned int duty = (d * p) / 100;

    unsigned int i;
    for (i = 0; i < period; i++)
    {
        if (i < duty)
        {
            PORTD = 0x05; // PWM ON
        }
        else
        {
            PORTD = 0x00; // PWM OFF
        }
        delay_ms(1);
    }
}

// PWM1 function (Note: Same as PWM, may need further clarification)
void PWM1(unsigned int p, unsigned int d)
{
    unsigned int period = p;
    unsigned int duty = (d * p) / 100;

    unsigned int i;
    for (i = 0; i < period; i++)
    {
        if (i < duty)
        {
            PORTD = 0x05; // PWM ON
        }
        else
        {
            PORTD = 0x00; // PWM OFF
        }
        delay_ms(1);
    }
}

// Servo rotation function with specified pulse width
void servo_rotate(int pulse_width)
{
    unsigned int i;
    for (i = 0; i < pulse_width; i++)
    {
        PORTC = 0x01; // Set PORTC high
        delay_ms(1);
        PORTC = 0x00; // Set PORTC low
        delay_ms(19);
    }
}

// PWMdelay function to generate delayed PWM signal
void PWMdelay(unsigned int d, unsigned int speed)
{
    unsigned int cntr = 0;
    while (cntr < d)
    {
        PWM1(10, speed);
        cntr++;
    }
}

// Simple delay function using NOP (Note: may need further clarification)
void mymsdelay(unsigned int d)
{
    unsigned int cntr = 0;
    while (cntr < d)
    {
        cntr = cntr;
        cntr++;
    }
}

// Delay function for 2 seconds using nested loops
void delay_2s()
{
    unsigned int i, j;

    for (i = 0; i < 2000; i++)
    {
        for (j = 0; j < 100; j++)
        {
            asm{ NOP }; // No operation
        }
    }
}