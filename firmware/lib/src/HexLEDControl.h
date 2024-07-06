#ifndef _HEX_LED_H_
#define _HEX_LED_H_

#include <FastLED.h>

#define NUM_LEDS 37
//#define LED_DATA_PIN 9    //PORTB
//#define LED_DATA_PIN 32    //Core2 PORTA
//#define LED_DATA_PIN 2    //CoreS3 PORTA
#define LED_BRIGHTNESS 6

// 色の定義は他にもたくさんある。FastLEDのpixeltypes.hを参照。
#define C0 (CRGB::Black)
#define C1 (CRGB::Blue)
#define C2 (CRGB::Green)
#define C3 (CRGB::DarkOrange)
#define C4 (CRGB::Red)
#define C5 (CRGB::WhiteSmoke)
#define C6 (CRGB::DimGray)
#define C7 (0x202020)

//void hex_led_init(void);
void hex_led_init(int brightness = LED_BRIGHTNESS);
void hex_led_set(const CRGB* ptn);
void hex_led_off(void);
void hex_led_rotate(void);
void hex_led_anime_set(const CRGB ptn[][NUM_LEDS], int frame, int rate);
bool hex_led_scroll_set(const CRGB* ptn, int width, int rate);


#endif //_HEX_LED_H_