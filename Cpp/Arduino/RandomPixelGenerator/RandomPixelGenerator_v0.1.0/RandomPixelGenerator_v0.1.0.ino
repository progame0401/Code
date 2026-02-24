#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
int y = 0;
int x = 1;
#define TFT_CS   10
#define TFT_RS   8
#define TFT_RST  9   
int yl = 0;
int xl = 0;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_RS, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.initR(INITR_144GREENTAB);   
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);           
  tft.setCursor(20, 50);         
  tft.println(" Hello");
  tft.setCursor(20, 70);         
  tft.println(" World");


}
int rengz[] = {ST77XX_BLACK, ST77XX_BLUE, ST77XX_RED, ST77XX_GREEN, ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW, ST77XX_WHITE, ST77XX_ORANGE};


 void loop() {

  String input = Serial.readStringUntil('\n');
  input.trim();
  input.toLowerCase();
  if (input == "russia"){
    tft.fillRect(0,0,tft.width(),tft.height(),ST77XX_WHITE);
    tft.fillRect(0,42,tft.width(),tft.height(),ST77XX_BLUE);
    tft.fillRect(0,84,tft.width(),tft.height(),ST77XX_RED);
  }

  if (input == "cool"){
    tft.fillRect(0, 0, tft.width(), 128, ST77XX_BLACK);
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
}

