
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

int now_sw;
int old_sw;
int i = 0;
int connectFlag = 0;
unsigned char DC_Power[4] = {0};

unsigned char x = 0, y = 0;
unsigned long chksum;
unsigned long timer_set = 0;
unsigned char ps3data[8] = { 0x00 };

void setup() {

  init_IO();
  SerialPS3.begin(2400);
  while (!SerialPS3);
  init_TIM5();
  i = 0;
  connectFlag = 0;
  ps3data[0] = 0x80;
}

void loop() {

  get_ps3();


  getJoystickPos( PS3_JOYSTICK_RIGHT_X );

  now_sw = digitalRead( SW1 );

  if ( now_sw && !old_sw ) {
    digitalWrite(LED1, HIGH);
    timer_set += 1000;
    if ( timer_set > 16000 ) {
      timer_set = 0;
      digitalWrite(LED1, LOW );
    }
  }
  // OK.
  pwmWrite( TIM1_CH1, 0 );
  pwmWrite( TIM1_CH2, timer_set );
  pwmWrite( TIM1_CH3, timer_set );
  pwmWrite( TIM1_CH4, 0 );

  // OK.

  getJoystickPos( PS3_JOYSTICK_LEFT_X );
  pwmWrite( TIM8_CH1, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH2, 200 * (sin(2 * 3.14 / 256 * (getDCpower(0) + 64)) + 1) * 128);

  getJoystickPos( PS3_JOYSTICK_LEFT_Y );
  pwmWrite( TIM8_CH3, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) - 64)) + 1) * 128);
  pwmWrite( TIM8_CH4, 200 * (sin(2 * 3.14 / 256 * (getDCpower(1) + 64)) + 1) * 128);

  /*
    getJoystickPos( PS3_JOYSTICK_LEFT_Y );
    pwmWrite( TIM8_CH3, 200 * (sin(2 * 3.14 / 256 * ((millis() / 100) - 64)) + 1) * 128);
    pwmWrite( TIM8_CH4, 200 * (sin(2 * 3.14 / 256 * ((millis() / 100) + 64)) + 1) * 128);
  */
  old_sw = now_sw;
}


void get_ps3()
{
  int i;
  if (SerialPS3.available() >= 8) { //8byte以上あるかチェック
    if ( connectFlag == 0 ) {
      connectFlag = 1;
      // setColor(1, 1, 1);
    }
    if (SerialPS3.read() == 0x80) { //１byte読み込んで0x80のスタートビットかチェック
      for (i = 1; i < 8; i++) { //スタートビットは読み込み済みなので、次の７個のデータを読み込む。
        ps3data[i] = SerialPS3.read();
      }
    }
  }
}

/* end of file */


