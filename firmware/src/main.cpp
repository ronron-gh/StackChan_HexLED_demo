#include <Arduino.h>
#include <M5Unified.h>
#include <HexLEDControl.h>
#include <Avatar.h>

using namespace m5avatar;
Avatar avatar;

const CRGB ptn_blink01[NUM_LEDS] = {
         C1,C2,C1,C2,
       C2,C0,C0,C0,C1,
      C1,C0,C1,C2,C0,C2,
    C2,C0,C2,C0,C1,C0,C1,
      C1,C0,C1,C2,C0,C2,
       C2,C0,C0,C0,C1,
         C1,C2,C1,C2
};

const CRGB ptn_blink02[NUM_LEDS] = {
         C2,C1,C2,C1,
       C1,C0,C0,C0,C2,
      C2,C0,C2,C1,C0,C1,
    C1,C0,C1,C0,C2,C0,C2,
      C2,C0,C2,C1,C0,C1,
       C1,C0,C0,C0,C2,
         C2,C1,C2,C1
};

const CRGB ptn_ring[NUM_LEDS] = {
         C0,C0,C0,C0,
       C0,C5,C5,C5,C0,
      C0,C5,C0,C0,C0,C0,
    C0,C6,C0,C0,C0,C0,C0,
      C0,C6,C0,C0,C7,C0,
       C0,C6,C7,C7,C0,
         C0,C0,C0,C0
};


const CRGB ptn_anime[][NUM_LEDS] = {
{
         C0,C0,C0,C0,
       C0,C0,C0,C0,C0,
      C0,C0,C0,C0,C0,C0,
    C0,C0,C0,C3,C3,C3,C3,
      C0,C0,C0,C3,C3,C3,
       C0,C0,C0,C3,C3,
         C0,C0,C0,C3
},
{
         C0,C0,C0,C0,
       C0,C0,C0,C0,C0,
      C0,C0,C0,C0,C0,C0,
    C0,C0,C0,C3,C3,C3,C3,
      C0,C0,C3,C3,C3,C3,
       C0,C3,C3,C3,C3,
         C3,C3,C3,C3
},
{
         C0,C0,C0,C0,
       C0,C0,C0,C0,C0,
      C0,C0,C0,C0,C0,C0,
    C3,C3,C3,C3,C3,C3,C3,
      C3,C3,C3,C3,C3,C3,
       C3,C3,C3,C3,C3,
         C3,C3,C3,C3
},
{
         C3,C0,C0,C0,
       C3,C3,C0,C0,C0,
      C3,C3,C3,C0,C0,C0,
    C3,C3,C3,C3,C3,C3,C3,
      C3,C3,C3,C3,C3,C3,
       C3,C3,C3,C3,C3,
         C3,C3,C3,C3
},
{
         C3,C3,C3,C3,
       C3,C3,C3,C3,C0,
      C3,C3,C3,C3,C0,C0,
    C3,C3,C3,C3,C3,C3,C3,
      C3,C3,C3,C3,C3,C3,
       C3,C3,C3,C3,C3,
         C3,C3,C3,C3
},
{
         C3,C3,C3,C3,
       C3,C3,C3,C3,C3,
      C3,C3,C3,C3,C3,C3,
    C3,C3,C3,C3,C3,C3,C3,
      C3,C3,C3,C3,C3,C3,
       C3,C3,C3,C3,C3,
         C3,C3,C3,C3
},
};


#define SCROLL_LINES  (7)
#define SCROLL_COLUMNS (28)
const CRGB ptn_scroll_robot[SCROLL_LINES][SCROLL_COLUMNS] = {
	{	  C4,	C4,	C4,	C4,	C4,	C0,	C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0 },
	{	C0, C0,	C0,	C0,	C0,	C4,	C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0   },
	{	  C4,	C1,	C0,	C1,	C0,	C4,	C0, C0, C6, C0, C6, C0, C6, C6, C6, C0, C6, C0, C0, C0, C6, C0, C0, C0, C6, C6, C0, C0 },
	{	C0, C0,	C1,	C1,	C0,	C4,	C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C6, C0, C6, C0   },
	{	  C4,	C0,	C0,	C0,	C0,	C4,	C0, C0, C6, C6, C6, C0, C6, C6, C0, C0, C6, C0, C0, C0, C6, C0, C0, C0, C0, C0, C0, C0 },
	{	C0, C4,	C4,	C4,	C4,	C4,	C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C0, C6, C0, C6, C0,  },
	{	  C4,	C4,	C0,	C4,	C4,	C4,	C0, C0, C6, C0, C6, C0, C6, C6, C6, C0 ,C6, C6, C6, C0, C6, C6, C6, C0, C6, C6, C0, C0 },
};

int g_led_mode = 0;

enum
{
    LED_MODE_COLOR,
    LED_MODE_BLINK,
    LED_MODE_ROTATE,
    LED_MODE_ANIME,
    LED_MODE_SCROLL,
    LED_MODE_LIMIT,
};

void continuous_color_change(void)
{
  CRGB ptn[NUM_LEDS];

  for(int h=0; h<=255; h++) {
    for(int i=0; i<NUM_LEDS; i++){
      ptn[i].setHSV(h, 255, 255);
    }

    hex_led_set(ptn);
    delay(10);
  }
}

void ledLoop(void *args) {
  
  while(1){
    if(g_led_mode == LED_MODE_COLOR){
      // 赤色→黄色→緑色→水色→青色→紫色に連続的に変化
      continuous_color_change();
    }
    else if(g_led_mode == LED_MODE_BLINK){
      // Blink
      for(int i=0; i<5; i++){
        hex_led_set(ptn_blink01);
        delay(200);
        hex_led_set(ptn_blink02);
        delay(200);
      }
    }
    else if(g_led_mode == LED_MODE_ROTATE){
      // Rotate
      hex_led_set(ptn_ring);
      for(int i=0; i<18; i++){
        hex_led_rotate();
        delay(200);
      }
    }
    else if(g_led_mode == LED_MODE_ANIME){
      // Animation
      hex_led_anime_set(ptn_anime, 6, 500);
    }
    else if(g_led_mode == LED_MODE_SCROLL){
      // Scroll
      hex_led_scroll_set((const CRGB*)ptn_scroll_robot, SCROLL_COLUMNS, 200); 
    }
  }
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  avatar.init();
  hex_led_init();

  xTaskCreate(ledLoop,     /* Function to implement the task */
              "ledLoop",   /* Name of the task */
              2048,         /* Stack size in words */
              NULL,         /* Task input parameter */
              1,            /* Priority of the task */
              NULL );       /* Task handle. */

}

void loop() {
  // put your main code here, to run repeatedly:

  M5.update();

  if (M5.BtnA.wasPressed())
  {
    g_led_mode++;
    if(g_led_mode == LED_MODE_LIMIT){
      g_led_mode = 0;
    }
  }

}
