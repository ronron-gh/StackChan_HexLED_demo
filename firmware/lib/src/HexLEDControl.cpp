#include "HexLEDControl.h"
#include <math.h>

CRGB leds[NUM_LEDS];
CRGB leds_rotate_tmp[NUM_LEDS];



const CRGB led_pattern_off[NUM_LEDS] = {
         C0,C0,C0,C0,
       C0,C0,C0,C0,C0,
      C0,C0,C0,C0,C0,C0,
    C0,C0,C0,C0,C0,C0,C0,
      C0,C0,C0,C0,C0,C0,
       C0,C0,C0,C0,C0,
         C0,C0,C0,C0
};


#define SCROLL_LINES  (7)
//#define SCROLL_COLUMNS (52)
//#define SCROLL_COLUMNS (7)
#define SCROLL_MARGIN (7)



#if 0
const CRGB led_scroll_pattern01[SCROLL_LINES][SCROLL_COLUMNS] = {
  // ↓↓↓ LED_Scroll_Pattern.xlsm で変換したコードをここに貼る ↓↓↓
	{		C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C4	,	C4	,	C4	,	C4	,	C4	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	},
	{	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C4	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0		},
	{		C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C4	,	C1	,	C0	,	C1	,	C0	,	C4	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	0x548235	,	0x548235	,	0x548235	,	C0	,	0x548235	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	0x548235	,	C0	,	0x548235	,	C0	,	0xBF8F00	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	},
	{	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C1	,	C1	,	C0	,	C4	,	C0	,	C0	,	0x548235	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	0x548235	,	C0	,	C0	,	C0	,	C0	,	0x548235	,	C0	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	0xBF8F00	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0		},
	{		C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C4	,	C0	,	C0	,	C0	,	C0	,	C4	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	C0	,	0x548235	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	C0	,	C0	,	C0	,	C0	,	0xBF8F00	,	0xBF8F00	,	0xBF8F00	,	C0	,	C0	,	C0	,	0xBF8F00	,	0xBF8F00	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	},
	{	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C4	,	C4	,	C4	,	C4	,	C4	,	C0	,	C0	,	C0	,	C0	,	0x548235	,	C0	,	C0	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	0x548235	,	C0	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	0xBF8F00	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0		},
	{		C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C4	,	C4	,	C0	,	C4	,	C4	,	C4	,	C0	,	C0	,	0x548235	,	0x548235	,	C0	,	C0	,	0x548235	,	C0	,	0x548235	,	C0	,	0x548235	,	C0	,	0x548235	,	0x548235	,	C0	,	0x548235	,	C0	,	0x548235	,	C0	,	0xBF8F00	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	0xBF8F00	,	0xBF8F00	,	C0	,	0xBF8F00	,	0xBF8F00	,	C0	,	0xBF8F00	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	,	C0	},

  // ↑↑↑ LED_Scroll_Pattern.xlsm で変換したコードをここに貼る ↑↑↑
};
#endif

/// 関数プロトタイプ ///
//void hex_led_animation01_callback(TimerHandle_t _xTimer);
//void start_hex_led_animation_timer(TimerCallbackFunction_t pxCallbackFunction);


// 次のようにパターンを回転させるための変換テーブル
//
//       　 0  →  1  →  2  →  3
//        ↑ 　                  ↓ 
//       4     5  →  6  →  7 　  8
//      ↑     ↑             ↓     ↓ 
//     9    10   11  →  12   13   14
//    ↑    ↑    ↑         ↓    ↓    ↓ 
//  15   16   17    18     19   20   21 
//    ↑    ↑    ↑         ↓    ↓    ↓ 
//    22   23    24  ←  25   26   27
//      ↑     ↑             ↓    ↓ 
//      28     29  ← 30  ← 31   32
//        ↑ 　                 ↓ 
//         33  ←  34　← 35 ← 36
                    // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19  
int rotate_next[37] = {3, 8,14,21, 2, 7,13,20,27, 1, 6,12,19,26,32, 0, 5,11,18,25,
                    //20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 
                      31,36, 4,10,17,24,30,35, 9,16,23,29,34,15,22,28,33};


void hex_led_init(int brightness){
  FastLED.addLeds<SK6812, LED_DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness( brightness );
}

void hex_led_set(const CRGB* ptn){
  memcpy(leds, ptn, NUM_LEDS * sizeof(CRGB));
  FastLED.show();
}

void hex_led_off(void){
  hex_led_set(led_pattern_off);
}

void hex_led_rotate(void){
  for(int i=0; i<NUM_LEDS; i++){
    leds_rotate_tmp[rotate_next[i]] = leds[i];
  }
  hex_led_set(leds_rotate_tmp);
}


#if 0
bool hex_led_animation_enable = false;
TimerHandle_t xTimerHexAnimation;
#define HEX_ANIMATION_PERIOD (200)     // 0.2s

void hex_led_animation01_callback(TimerHandle_t _xTimer){

  hex_led_ptn_rotate_set(led_rotate_pattern01, 1);

  if(hex_led_animation_enable){
    start_hex_led_animation_timer(hex_led_animation01_callback);
  }
  else{
    hex_led_off();
  }
}

void start_hex_led_animation_timer(TimerCallbackFunction_t pxCallbackFunction){
  xTimerHexAnimation = xTimerCreate("Timer HEX Animation", HEX_ANIMATION_PERIOD, pdFALSE, 0, pxCallbackFunction);
  
  if(xTimerHexAnimation != NULL){
    xTimerStart(xTimerHexAnimation, 0);
    //Serial.println("Start hex animation timer.");
  }
  else{
    Serial.println("Failed to start hex animation timer.");
  }

}

void hex_led_ptn_thinking_start(void){
  hex_led_animation_enable = true;
  start_hex_led_animation_timer(hex_led_animation01_callback);
}

void hex_led_ptn_thinking_end(void){
  hex_led_animation_enable = false;
}
#endif

void hex_led_anime_set(const CRGB ptn[][NUM_LEDS], int frame, int rate)
{
  for(int i=0; i<frame; i++){
    hex_led_set(ptn[i]);
    delay(rate);
  }
}


CRGB *scroll_line_buf[SCROLL_LINES];

bool hex_led_scroll_set(const CRGB* ptn, int width, int rate){
  
  // スクロールに必要な前後の余白を含めたバッファを確保し、発光パターンを格納
  for(int i=0; i<SCROLL_LINES; i++){
    scroll_line_buf[i] = (CRGB*)calloc(width + SCROLL_MARGIN * 2, sizeof(CRGB));
    if(scroll_line_buf[i] == nullptr){
      Serial.println("Memory allocation failure");
      return false;
    }
    memcpy(&scroll_line_buf[i][SCROLL_MARGIN], &ptn[width * i], sizeof(CRGB) * width);
  }

  // スクロール制御
  for(int frame=0; frame<(width + SCROLL_MARGIN); frame++){

    memcpy(&leds[0], &scroll_line_buf[0][frame + 1], sizeof(CRGB)*4);
    memcpy(&leds[4], &scroll_line_buf[1][frame + 1], sizeof(CRGB)*5);
    memcpy(&leds[9], &scroll_line_buf[2][frame], sizeof(CRGB)*6);
    memcpy(&leds[15], &scroll_line_buf[3][frame], sizeof(CRGB)*7);
    memcpy(&leds[22], &scroll_line_buf[4][frame], sizeof(CRGB)*6);
    memcpy(&leds[28], &scroll_line_buf[5][frame + 1], sizeof(CRGB)*5);
    memcpy(&leds[33], &scroll_line_buf[6][frame + 1], sizeof(CRGB)*4);

    FastLED.show();
    delay(rate);
  }

  // メモリを解放
  for(int i=0; i<SCROLL_LINES; i++){
    free(scroll_line_buf[i]);
  }

  return true;
}

