#include "pin_defination.h"
#include <HardwareTimer.h>

int now_sw;
int old_sw;
unsigned long timer_set = 0;

void setup() {
  init_IO();
}

void loop() {
  now_sw = digitalRead( SW1 );

  if ( now_sw && !old_sw ) {
    digitalWrite(LED1, HIGH);
    timer_set += 5000;
    if ( timer_set > 60000 ) {
      timer_set = 0;
      digitalWrite(LED1, LOW );
    }
  }
  // OK.
  pwmWrite( TIM1_CH1, 0 );
  pwmWrite( TIM1_CH2, timer_set );
  pwmWrite( TIM1_CH3, timer_set );
  pwmWrite( TIM1_CH4, 0 );
  // wrong?
  /*
  pwmWrite( TIM2_CH1, timer_set );
  pwmWrite( TIM2_CH2, 0 );
  pwmWrite( TIM2_CH3, 0 );
  pwmWrite( TIM2_CH4, timer_set );
  */
  // OK.
  pwmWrite( TIM8_CH1, timer_set );
  pwmWrite( TIM8_CH2, 0 );
  pwmWrite( TIM8_CH3, 0 );
  pwmWrite( TIM8_CH4, timer_set );




  old_sw = now_sw;

}



