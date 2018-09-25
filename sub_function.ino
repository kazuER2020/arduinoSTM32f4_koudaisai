
// initialize for I/O.
void init_IO( void ) {
  pinMode( LED1, OUTPUT );
  pinMode( LED2, OUTPUT );
  pinMode( LED3, OUTPUT );
  pinMode( LED4, OUTPUT );
  pinMode( LED5, OUTPUT );
  pinMode( LED6, OUTPUT );
  pinMode( LED7, OUTPUT );
  pinMode( LED8, OUTPUT );
  pinMode( RESET, OUTPUT );

  pinMode( SW1,  INPUT );
  pinMode( SW3,  INPUT );
  pinMode( SW4,  INPUT );
  pinMode( SW5,  INPUT );

  pinMode(TIM1_CH1, PWM);
  pinMode(TIM1_CH2, PWM);
  pinMode(TIM1_CH3, PWM);
  pinMode(TIM1_CH4, PWM);

  pinMode(TIM2_CH1, PWM);
  pinMode(TIM2_CH2, PWM);
  pinMode(TIM2_CH3, PWM);
  pinMode(TIM2_CH4, PWM);

  pinMode(TIM8_CH1, PWM);
  pinMode(TIM8_CH2, PWM);
  pinMode(TIM8_CH3, PWM);
  pinMode(TIM8_CH4, PWM);

  pinMode( RED,     PWM);
  pinMode( GREEN,   PWM);
  pinMode( BLUE ,   PWM);  

  pinMode( BZ, PWM );
  
  digitalWrite( RESET, HIGH );  // RESET SW LED
  pwmWrite(RED, 60000);

}


