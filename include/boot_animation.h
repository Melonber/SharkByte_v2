// include/boot_animation.h
#ifndef BOOT_ANIMATION_H
#define BOOT_ANIMATION_H

#include <Adafruit_SH110X.h>

// Анимационные кадры акулы (8x8 пикселей)
const uint8_t PROGMEM shark_frames[4][8] = {
  { 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18 }, // Кадр 1 (закрытый рот)
  { 0x18, 0x3C, 0x7A, 0xF5, 0xF5, 0x7A, 0x3C, 0x18 }, // Кадр 2 (приоткрытый)
  { 0x18, 0x3C, 0x72, 0xED, 0xED, 0x72, 0x3C, 0x18 }, // Кадр 3 (открытый)
  { 0x18, 0x3C, 0x7A, 0xF5, 0xF5, 0x7A, 0x3C, 0x18 }  // Кадр 4 (снова приоткрытый)
};

void showSharkBootAnimation(Adafruit_SH1106G &display) {
  display.clearDisplay();
  
  // Начальный текст
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(15, 0);
  display.println("SharkByte");
  display.drawLine(0, 10, display.width(), 10, SH110X_WHITE);
  
  // Анимация с акулой и прогресс-баром
  for(int i=0; i<=100; i+=5) {
    display.clearDisplay();
    
    // Рисуем текст каждый кадр
    display.setCursor(15, 0);
    display.println("EvilTwin Shark");
    display.drawLine(0, 10, display.width(), 10, SH110X_WHITE);
    
    // Анимация акулы (плавает слева направо)
    int shark_x = map(i, 0, 100, -8, display.width());
    int frame = (i/5) % 4; // Цикл по 4 кадрам
    
    display.drawBitmap(shark_x, 20, shark_frames[frame], 8, 8, SH110X_WHITE);
    
    // Волны
    for(int x=0; x<display.width(); x+=8) {
      display.drawPixel(x, 30 + 3*sin(x/10.0 + i/20.0), SH110X_WHITE);
    }
    
    // Прогресс-бар
    display.drawRect(0, 40, display.width(), 8, SH110X_WHITE);
    display.fillRect(0, 40, map(i, 0, 100, 0, display.width()), 8, SH110X_WHITE);
    
    // Статус загрузки
    display.setCursor(0, 50);
    if(i < 30) {
      display.print("Booting... ");
    } else if(i < 70) {
      display.print("Hunting... ");
    } else {
      display.print("Attacking... ");
    }
    display.print(i);
    display.println("%");
    
    display.display();
    delay(50);
  }
  
  // Финал анимации
  for(int i=0; i<3; i++) {
    display.invertDisplay(true);
    delay(150);
    display.invertDisplay(false);
    delay(150);
  }
}

#endif