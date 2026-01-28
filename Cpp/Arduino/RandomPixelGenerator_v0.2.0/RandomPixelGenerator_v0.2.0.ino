#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
int y = 0;
int x = 1;
int anim_x = 20;
int anim_y = 0;
int animtime = 0;
int boxsize = 30;
int box_y = 0;
int box_x = 0;
int w = 2;
int a = 3;
int s = 4;
int d = 5;
unsigned long lt = 0;
unsigned long t = millis();
#define TFT_CS   10
#define TFT_RS   8
#define TFT_RST  9   
int yl = 0;
int xl = 0;
int rengz[] = {ST77XX_BLACK, ST77XX_BLUE, ST77XX_RED, ST77XX_GREEN, ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW, ST77XX_WHITE, ST77XX_ORANGE};
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_RS, TFT_RST);
  void startanim() {
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2); 
  while (animtime <= 40){
    tft.fillRect(anim_x + 10, anim_y - 5, 60, 40, ST77XX_BLACK);          
    tft.setCursor(anim_x, anim_y);         
    tft.println(" Hello");
    tft.setCursor(anim_x, anim_y + 20);         
    tft.println(" World");
    anim_y++;
    animtime++;
}
}
void setup() {
  Serial.begin(9600);
  pinMode(w, INPUT_PULLUP);
  pinMode(a, INPUT_PULLUP);
  pinMode(s, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  tft.initR(INITR_144GREENTAB);   
  tft.fillScreen(ST77XX_BLACK);
}
 void loop() {
  startanim();
  String input = Serial.readStringUntil('\n');
  input.trim();
  input.toLowerCase();
  if (input == "russia" || (digitalRead(d)) == 0 ){
    tft.fillRect(0,0,tft.width(),tft.height(),ST77XX_WHITE);
    tft.fillRect(0,42,tft.width(),tft.height(),ST77XX_BLUE);
    tft.fillRect(0,84,tft.width(),tft.height(),ST77XX_RED);
  }
  if (input == "cool" || (digitalRead(a)) == 0 ){
    tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
  while(true){
    while(x != 0 || y != 128){
      int colorIndex = random(0, 9);
      tft.drawPixel(x, y, rengz[colorIndex]);
      y++;
      x--;
      if (x == 0){
      x = xl + 1;
      xl = x;
      y = 0;
      }
      if (x == 128 && y == 128){
      y = 0;
      yl = 0;
      x = 1;
      xl = 0;
    }
    }
}
}
 if (input == "box" || (digitalRead(w)) == 0 ){
  tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
  tft.setCursor(0, 40);
  tft.setTextSize(2); 
  tft.println("Try moving");
  tft.println("via the");
  tft.println("buttons");
    while(true){
    tft.fillRect(box_x, box_y, boxsize, boxsize, ST77XX_BLACK);
    if(digitalRead(d) == 0 && box_x+boxsize < 128 ){
      box_x++;}
    if(digitalRead(a) == 0 && box_x > 0){
      box_x--;}
    if(digitalRead(s) == 0 && box_y+boxsize < 128){
      box_y++;}
    if(digitalRead(w) == 0 && box_y > 0){
      box_y--;}      
      tft.fillRect(box_x, box_y, boxsize, boxsize, ST77XX_GREEN);
   }
  }
}