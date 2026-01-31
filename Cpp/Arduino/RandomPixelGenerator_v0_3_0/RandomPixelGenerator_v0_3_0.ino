#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

const char* menuItems[] = {"RandmPixel","Box","Russia",};
int menuIndex = 0;
int sellected = -1;

int y = 0;
int x = 1;
int anim_x = 28;
int anim_y = 0;
int animtime = 0;
int boxsize = 30;
int box_y = 0;
int box_x = 0;
int w = 2;
int a = 3;
int s = 4;
int d = 5;
unsigned long St = 0;
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
  while (animtime <= 55){
    tft.fillRect(anim_x , anim_y - 3, 70, 17, ST77XX_BLACK);          
    tft.setCursor(anim_x, anim_y);         
    tft.println("V0_3_0");
    anim_y++;
    animtime++;
} }
void menudraw() {
  int menu_y = 10;
    for (int i = 0; i < 3; i++) {
      tft.setCursor(0, menu_y);         
      menu_y+= 45;
      if (i == menuIndex) {
        tft.setTextColor(ST77XX_GREEN);
      }
      else {
      tft.setTextColor(ST77XX_WHITE);
      }
      tft.print(menuItems[i]);
}   }

void menu() {
  if (digitalRead(s) == 0 && menuIndex != 2) {
    menuIndex++;
    menudraw();}
  if (digitalRead(w) == 0 && menuIndex > 0) {
    menuIndex--;
    menudraw();}
  if (digitalRead(d) == 0 && digitalRead(a) != 0) {
    sellected = menuIndex; }
  }


void goback() {
static unsigned long pressedStart = 0;
  if (digitalRead(d) == 0 && digitalRead(a) == 0) {
    if (pressedStart == 0) {
      pressedStart = millis();
    }
    if (millis() - pressedStart >= 1000) {
      sellected = -1;
      tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
      menudraw();
      pressedStart = 0;
    }
  } else {
  pressedStart = 0;
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(w, INPUT_PULLUP);
  pinMode(a, INPUT_PULLUP);
  pinMode(s, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  tft.initR(INITR_144GREENTAB);
  tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
  startanim();
  delay(400);
  tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
  menudraw();
  menu();


   
}
 void loop() {
  String input = Serial.readStringUntil('\n');
  input.trim();
  input.toLowerCase();
  menu();
  goback();

  if ((input == "russia" || sellected == 2) && sellected != -1){
    goback();
    tft.fillRect(0,0,tft.width(),tft.height(),ST77XX_WHITE);
    tft.fillRect(0,42,tft.width(),tft.height(),ST77XX_BLUE);
    tft.fillRect(0,84,tft.width(),tft.height(),ST77XX_RED);
  }
  if ((input == "randompixel"|| sellected == 0) && sellected != -1){
    tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
  while(sellected == 0){
    while((x != 0 || y != 128) && sellected != -1){
      int colorIndex = random(0, 9);
      tft.drawPixel(x, y, rengz[colorIndex]);
      goback();
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
 if ((input == "box" || sellected == 1) && sellected != -1){
  tft.fillRect(0, 0, tft.width(), tft.height(), ST77XX_BLACK);
  tft.setCursor(0, 40);
  tft.setTextSize(2); 
  tft.println("Try moving");
  tft.println("via the");
  tft.println("buttons");
    while(sellected == 1 && sellected != -1){
    tft.fillRect(box_x, box_y, boxsize, boxsize, ST77XX_BLACK);
    goback();
    if(digitalRead(d) == 0 && box_x+boxsize < 128 ){
      box_x++;}
    if(digitalRead(a) == 0 && box_x > 0){
      box_x--;}
    if(digitalRead(s) == 0 && box_y+boxsize < 128){
      box_y++;}
    if(digitalRead(w) == 0 && box_y > 0){
      box_y--;}      
          
    if( sellected != -1){     
      tft.fillRect(box_x, box_y, boxsize, boxsize, ST77XX_GREEN);}    
   }
  }
}