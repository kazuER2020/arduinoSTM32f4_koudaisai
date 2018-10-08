
/*
   Title   : stm32f4_main.ino
   Date    : 2018/09/30
   Author  : kazu

   Board             : STM32 Discovery F407
   USB Configration  : USB inactive
   Optimize          : Smallest Code with LTO
   Board Manager URL : https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json


*/
#include "pin_defination.h"

#define PS3_JOYSTICK_LEFT_X 1
#define PS3_JOYSTICK_LEFT_Y 2
#define PS3_JOYSTICK_RIGHT_X 3
#define PS3_JOYSTICK_RIGHT_Y 4

HardwareSerial SerialPS3( USART3, PB10, PB11 );
HardwareSerial Serial_Mizz( USART1, PA9, PA10 );

int i = 0;
int connectFlag = 0;
unsigned char dc_power[4] = {64, 64, 64, 64};

unsigned char ps3data[8] = { 0x00 };

void setup() {

  init_IO();
  SerialPS3.begin(2400);
  Serial_Mizz.begin(9600);
  Serial.begin(9600);
  while (!SerialPS3);
  while (!Serial_Mizz);
  init_TIM5();
  i = 0;
  connectFlag = 0;
  ps3data[0] = 0x80;
}

void loop() {

  get_ps3();

  if ( getJoystickPos( PS3_JOYSTICK_LEFT_X ) == PS3_JOYSTICK_LEFT_X ) {
    motor_X();
  }
  if ( getJoystickPos( PS3_JOYSTICK_LEFT_Y ) == PS3_JOYSTICK_LEFT_Y ) {
    motor_Y();
  }
  if ( getJoystickPos( PS3_JOYSTICK_RIGHT_X ) == PS3_JOYSTICK_RIGHT_X ) {
    motor_rotate();
  }
}


void motor_Y( void ) {
  getJoystickPos( PS3_JOYSTICK_LEFT_Y );
  pwmWrite( TIM1_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) + 64)) + 1) * 128);
  pwmWrite( TIM1_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) - 64)) + 1) * 128);
  pwmWrite( TIM1_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) + 64)) + 1) * 128);
  pwmWrite( TIM1_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) + 64)) + 1) * 128);
  pwmWrite( TIM8_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) + 64)) + 1) * 128);

}



void motor_X( void ) {
  getJoystickPos( PS3_JOYSTICK_LEFT_X );
  pwmWrite( TIM1_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) - 64)) + 1) * 128);
  pwmWrite( TIM1_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) + 64)) + 1) * 128);
  pwmWrite( TIM1_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) + 64)) + 1) * 128);
  pwmWrite( TIM1_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) + 64)) + 1) * 128);
  pwmWrite( TIM8_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) + 64)) + 1) * 128);
  pwmWrite( TIM8_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) - 64)) + 1) * 128);

}


void motor_rotate( void ) {
  getJoystickPos( PS3_JOYSTICK_RIGHT_X );
  pwmWrite( TIM1_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) + 64)) + 1) * 128);
  pwmWrite( TIM1_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) - 64)) + 1) * 128);
  pwmWrite( TIM1_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) + 64)) + 1) * 128);
  pwmWrite( TIM1_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) + 64)) + 1) * 128);
  pwmWrite( TIM8_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) + 64)) + 1) * 128);
  pwmWrite( TIM8_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(2) - 64)) + 1) * 128);

}

/* end of file */


