/* pins for LED */
#define LED1 PE0
#define LED2 PE1
#define LED3 PE2
#define LED4 PE3
#define LED5 PE8
#define LED6 PE9
#define LED7 PE11
#define LED8 PE13
#define RESET PE4

// for fullColorLED 
#define TIM10_CH1 PB8
#define TIM11_CH1 PB9
#define TIM12_CH1 PB14

// 別名で定義:
#define RED   PB9
#define GREEN PB8
#define BLUE  PB14

////////////////////

/* pins for SW */
#define SW1 PA4
#define SW3 PA7
#define SW4 PB0
#define SW5 PB1
////////////////////

/* pin for PWM */
// for Timer1
#define TIM1_CH1 PE9
#define TIM1_CH2 PE11
#define TIM1_CH3 PE13
#define TIM1_CH4 PE14

// for Timer2
#define TIM2_CH1 PA5
#define TIM2_CH2 PB3
#define TIM2_CH3 PA2
#define TIM2_CH4 PA3

// for Timer8
#define TIM8_CH1 PC6
#define TIM8_CH2 PC7
#define TIM8_CH3 PC8
#define TIM8_CH4 PC9

/////////////////////

/* pins for A/D converter */
#define ADC_IN10 PC0
#define ADC_IN11 PC1
#define ADC_IN12 PC2
#define ADC_IN13 PC3
#define ADC_IN14 PC4
#define ADC_IN15 PC5

/////////////////////

/* pin for Buzzer */
#define BZ PB15 // PWM(TIM12_CH2)

/////////////////////

/* pins for 5V support. */
#define SUB1 PD11
#define SUB2 PD10
#define SUB3 PD9
#define SUB4 PD8

/////////////////////

/* pins for Serial.*/

#define RX PB11
#define TX PB10

/////////////////////

/* pins for AQM0802_BL(i2c.) */

#define LCD_BACKLIGHT PA6
#define LCD_SCA PB6
#define LCD_SDL PB7

/////////////////////
