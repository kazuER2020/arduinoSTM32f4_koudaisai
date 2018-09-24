
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


/*
  pinMode(TIM2_CH1, PWM);
  pinMode(TIM2_CH2, PWM);
  pinMode(TIM2_CH3, PWM);
  pinMode(TIM2_CH4, PWM);

  pinMode(TIM8_CH1, PWM);
  pinMode(TIM8_CH2, PWM);
  pinMode(TIM8_CH3, PWM);
  pinMode(TIM8_CH4, PWM);
*/
  digitalWrite( RESET, HIGH );
}

void init_TIM1( void ) {
  pinMode(TIM1_CH1, PWM);
  pinMode(TIM1_CH2, PWM);
  pinMode(TIM1_CH3, PWM);
  pinMode(TIM1_CH4, PWM);
  Timer1.pause();          
  Timer1.setPrescaleFactor(7200); 
  Timer1.setOverflow(10000 * 2); 
  pwmWrite(TIM1_CH1, 10000);      

  Timer1.setCount(0);          
  Timer1.refresh();             
  Timer1.resume();                  
}


