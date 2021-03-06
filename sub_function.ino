unsigned long cnt1 = 0;
unsigned long cnt2 = 0;
unsigned long cnt3 = 0;
unsigned long cnt4 = 0;

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

  pinMode(TIM8_CH1, PWM);
  pinMode(TIM8_CH2, PWM);
  pinMode(TIM8_CH3, PWM);
  pinMode(TIM8_CH4, PWM);

  pinMode( RED,     OUTPUT);
  pinMode( GREEN,   OUTPUT);
  pinMode( BLUE ,   OUTPUT);

  pinMode( SUB1, OUTPUT );
  pinMode( SUB2, OUTPUT );
  pinMode( SUB3, OUTPUT );
  pinMode( SUB4, OUTPUT );

  pinMode( BZ, OUTPUT );

  pinMode( LCD_BACKLIGHT, OUTPUT );

  digitalWrite( RESET, HIGH );  // RESET SW LED
  digitalWrite( LCD_BACKLIGHT, HIGH ); // backlight for i2cLCD
}

void init_TIM5( void ) {
  // settings for interrupt handler by using Timer5.
  Timer5.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  Timer5.setMode(TIMER_CH2, TIMER_OUTPUT_COMPARE);
  Timer5.setMode(TIMER_CH3, TIMER_OUTPUT_COMPARE);
  Timer5.setMode(TIMER_CH4, TIMER_OUTPUT_COMPARE);
  Timer5.pause();
  Timer5.setCount(0);
  Timer5.setOverflow(5000);
  Timer5.setCompare(TIMER_CH1, 1000);
  Timer5.setCompare(TIMER_CH2, 1000);
  Timer5.setCompare(TIMER_CH3, 1000);
  Timer5.setCompare(TIMER_CH4, 1000);
  Timer5.attachInterrupt(TIMER_CH1, pwmHandler1);
  Timer5.attachInterrupt(TIMER_CH2, pwmHandler2);
  Timer5.attachInterrupt(TIMER_CH3, pwmHandler3);
  Timer5.attachInterrupt(TIMER_CH4, pwmHandler4);
  Timer5.refresh();
  Timer5.resume();
}

// makePWMforarms1.
void pwmHandler1( void ) {
  static int moveFlag = 0;
  cnt1++;
  if ( getLeftArrow() && moveFlag == 0) {
    moveFlag = 1;
    cnt1 = 0;
  }
  if ( getRightArrow() && moveFlag == 0) {
    moveFlag = 1;
    cnt1 = 0;
  }
  if ( getLeftArrow() && moveFlag == 1) {
    if ( cnt1 < 50 ) {
      digitalWrite(SUB2, HIGH);
    }
    else if ( cnt1 < 110 ) {
      digitalWrite( SUB2, LOW);
    }
    else {
      cnt1 = 0;
    }
  }

  if ( getRightArrow() && moveFlag == 1 ) {
    if ( cnt1 < 5 ) {
      digitalWrite(SUB2, HIGH);
    }
    else if ( cnt1 < 110 ) {
      digitalWrite( SUB2, LOW);
    }
    else {
      cnt1 = 0;

    }
  }

  if ( getUpArrow() && moveFlag == 0) {
    moveFlag = 1;
    cnt1 = 0;
  }

  if ( getUpArrow() && moveFlag == 1) {
    if ( cnt1 < 19 ) {
      digitalWrite(SUB4, HIGH);
    }
    else if ( cnt1 < 110 ) {
      digitalWrite( SUB4, LOW);
    }
    else {
      cnt1 = 0;
    }
  }

  if ( getDownArrow() && moveFlag == 1 ) {
    if ( cnt1 < 10 ) {
      digitalWrite(SUB4, HIGH);
    }
    else if ( cnt1 < 110 ) {
      digitalWrite( SUB4, LOW);
    }
    else {
      cnt1 = 0;

    }
  }
}

// makePWMforarms2.
void pwmHandler2( void ) {
  static int moveFlag = 0;
  static int handState = 0;
  cnt2++;
  if ( getL1 && moveFlag == 0) {
    moveFlag = 1;
    cnt2 = 0;
  }

  if ( getL1() && moveFlag == 1) {
    if ( cnt2 < 73 ) {
      digitalWrite(SUB3, HIGH);
    }
    else if ( cnt2 < 180 ) {
      digitalWrite( SUB3, LOW);
    }
    else {
      cnt2 = 0;
    }
  }


  if ( getL2() && moveFlag == 1 ) {
    if ( cnt2 < 5 ) {
      digitalWrite(SUB3, HIGH);
    }
    else if ( cnt2 < 310 ) {
      digitalWrite( SUB3, LOW);
    }
    else {
      cnt2 = 0;
    }
  }


  if ( getBatu() && moveFlag == 1 ) {
    handState = 1;
  }
  if ( getMaru() && moveFlag == 1 ) {
    handState = 2;
  }
  if ( getR1() ) {
    handState = 0;
  }
  switch ( handState ) {
    case 0:
      break;

    case 1:
      if ( cnt2 < 40 ) {
        digitalWrite(SUB1, HIGH);
      }
      else if ( cnt2 < 90 ) {
        digitalWrite( SUB1, LOW);
      }
      else {
        cnt2 = 0;
      }
      break;

    case 2:
      if ( cnt2 < 5 ) {
        digitalWrite(SUB1, HIGH);
      }
      else if ( cnt2 < 310 ) {
        digitalWrite( SUB1, LOW);
      }
      else {
        cnt2 = 0;
      }
      break;
  }



}

// we don't using pwmHandler4 now(2018/09/30)
void pwmHandler3( void ) {
  cnt3++;
  if ( cnt3 < 500 ) {
    digitalWrite( LCD_BACKLIGHT, HIGH );
  }
  else if ( cnt3 < 1000 ) {
    digitalWrite( LCD_BACKLIGHT, LOW );
  }
  else {
    cnt3 = 0;
  }
}

void pwmHandler4( void ) {
  cnt4++;
  if ( digitalRead(SW3) == HIGH ) {
    if ( cnt4 < 3) {
      digitalWrite(BZ, HIGH);
    }
    else if (cnt4 < 4) {
      digitalWrite(BZ, LOW);
    }
    else {
      cnt4 = 0;
    }
  }
}

////////////////////////////////////////////////////////////

// set Color for fullcolorLED.
void setColor( int state_r, int state_g, int state_b ) {
  digitalWrite(RED, state_r);
  digitalWrite(GREEN, state_g);
  digitalWrite(BLUE, state_b);
}

////////////////////////////////////////////////////////////

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

// ps3 〇取得
int getMaru( void ) {
  int ret = 0;

  if ( ps3data[2] == 0x40 && ps3data[7] == 0x40 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {

    ret = 1;
  }

  return ret;
}

// ps3 △取得
int getSankaku( void ) {
  int ret = 0;

  if ( ps3data[2] == 0x10 && ps3data[7] == 0x10 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {

    ret = 1;
  }

  return ret;
}

// ps3 ×取得
int getBatu( void ) {
  int ret = 0;

  if ( ps3data[2] == 0x20 && ps3data[7] == 0x20 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {

    ret = 1;
  }
  return ret;
}

// ps3 □取得
int getShikaku( void ) {
  int ret = 0;
  if ( ps3data[1] == 0x01 && ps3data[7] == 0x01 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {

    ret = 1;
  }
  return ret;
}

// ps3 ↑取得
int getUpArrow( void ) {
  int ret = 0;
  if ( ps3data[2] == 0x01 && ps3data[7] == 0x01 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    ret = 1;
  }
  return ret;
}

// ps3 ←取得
int getLeftArrow( void ) {
  int ret = 0;
  if ( ps3data[2] == 0x08 && ps3data[7] == 0x08 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    ret = 1;
  }
  return ret;
}

// ps3 →取得
int getRightArrow( void ) {
  int ret = 0;
  if ( ps3data[2] == 0x04 && ps3data[7] == 0x04 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    ret = 1;
  }
  return ret;
}

// ps3 ↓取得
int getDownArrow( void ) {
  int ret = 0;
  if ( ps3data[2] == 0x02 && ps3data[7] == 0x02 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    ret = 1;
  }
  return ret;
}

// ps3 L1取得
int getL1( void ) {
  int ret = 0;
  if ( ps3data[1] == 0x02 && ps3data[7] == 0x02 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    // L1
    ret = 1;
  }
  return ret;
}

// ps3 L2取得
int getL2( void ) {
  int ret = 0;
  if ( ps3data[1] == 0x04 && ps3data[7] == 0x04 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    // L2
    ret = 1;
  }
  return ret;
}

// ps3 R1取得
int getR1( void ) {
  int ret = 0;
  if ( ps3data[1] == 0x08 && ps3data[7] == 0x08 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    // R1
    ret = 1;
  }
  return ret;
}

// ps3 R2取得
int getR2( void ) {
  int ret = 0;
  if ( ps3data[1] == 0x10 && ps3data[7] == 0x10 &&
       ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 &&  ps3data[6] == 0x40 ) {
    // R2
    ret = 1;
  }
  return ret;
}

int getJoystickPos( int pos ) {
  int code;
  switch ( pos ) {
    case PS3_JOYSTICK_LEFT_X:
      // 左アナログ左右
      if ( ps3data[1] == 0x00 && ps3data[2] == 0x00 &&
           ps3data[4] == 0x40 && ps3data[5] == 0x40 && ps3data[6] == 0x40 ) {
        dc_power[0] = ps3data[3];

        setColor(1, 0, 0);
        code = PS3_JOYSTICK_LEFT_X;
      }
      break;

    case PS3_JOYSTICK_LEFT_Y:
      // 左アナログ上下
      if ( ps3data[1] == 0x00 && ps3data[2] == 0x00 &&
           ps3data[3] == 0x40 && ps3data[5] == 0x40 && ps3data[6] == 0x40 ) {
        dc_power[1] = ps3data[4];
        setColor(0, 0, 1);
        code = PS3_JOYSTICK_LEFT_Y;
      }
      break;

    case PS3_JOYSTICK_RIGHT_X:
      // 右アナログ左右
      if ( ps3data[1] == 0x00 && ps3data[2] == 0x00 &&
           ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[6] == 0x40 ) {
        dc_power[2] = ps3data[5];
        setColor(0, 1, 0);
        code = PS3_JOYSTICK_RIGHT_X;
      }
      break;
    /*
        case PS3_JOYSTICK_RIGHT_Y:
          // 右アナログ上下
          if ( ps3data[1] == 0x00 && ps3data[2] == 0x00 &&
               ps3data[3] == 0x40 && ps3data[4] == 0x40 && ps3data[5] == 0x40 ) {

            raw[3] = ps3data[6];
            setColor(1, 0, 1);

          }
          break;
    */
    default:
      setColor(0, 0, 0);
      code = -1;
      break;
  }
  return code;
}

int getDCpower( int motor_num ) {
  return dc_power[ motor_num ];
}

