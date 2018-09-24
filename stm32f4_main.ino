#include "pin_defination.h"
#include <HardwareTimer.h>

int now_sw;
int old_sw;
unsigned long timer_set = 0;

void setup() {
  // put your setup code here, to run once:
  init_IO();
  pinMode(TIM1_CH1, PWM);
  pinMode(TIM1_CH2, PWM);
  pinMode(TIM1_CH3, PWM);
  pinMode(TIM1_CH4, PWM);
}

void loop() {
  now_sw = digitalRead( SW1 );

  if ( now_sw && !old_sw ) {
    digitalWrite(LED1, HIGH);
    timer_set += 10000;
    if ( timer_set > 60000 ) {
      timer_set = 0;
      digitalWrite(LED1, LOW );
    }
  }
  pwmWrite( TIM1_CH1, timer_set );
  pwmWrite( TIM1_CH2, 0 );
  pwmWrite( TIM1_CH3, 0 );
  pwmWrite( TIM1_CH4, 0 );


  old_sw = now_sw;

}



