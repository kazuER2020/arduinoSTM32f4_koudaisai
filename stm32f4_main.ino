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
  pwmWrite( TIM8_CH1, map(getJoystickPos( PS3_JOYSTICK_LEFT_X), 0x00, 0xff, 0, 60000 ));
  pwmWrite( TIM8_CH2, map(getJoystickPos( PS3_JOYSTICK_LEFT_X), 0x00, 0xff, 60000, 0 ));
  pwmWrite( TIM8_CH3, map(getJoystickPos( PS3_JOYSTICK_LEFT_Y), 0x00, 0xff, 0, 60000 ));
  pwmWrite( TIM8_CH4, map(getJoystickPos( PS3_JOYSTICK_LEFT_Y), 0x00, 0xff, 60000, 0 ));

  old_sw = now_sw;
}


void get_ps3()
{
  int i;

  if (SerialPS3.available() >= 8) { //8byte以上あるかチェック
    if ( connectFlag == 0 ) {
      connectFlag = 1;
      setColor(1, 1, 1);
    }
    if (SerialPS3.read() == 0x80) { //１byte読み込んで0x80のスタートビットかチェック
      for (chksum = ps3data[0], i = 1; i < 8; i++) { //スタートビットは読み込み済みなので、次の７個のデータを読み込む。
        ps3data[i] = SerialPS3.read();
        if (i < 7) chksum += ps3data[i];
      }
    }
  }
}

/* end of file */


