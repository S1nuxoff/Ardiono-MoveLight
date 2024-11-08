#include <FastLED.h>

#include "GyverButton.h"

#define MOSFET 9
#define B_MOSFET 10
#define PRI 6
#define LDR A0
#define LED 3
#define BTN 5
#define SPK 10

#define NUM_LEDS 5
#define TIMEOUT 60
#define TIMEOUT_LONG 600

CRGB leds[NUM_LEDS];
GButton T_BTN(BTN);

bool modeFlag = true;
bool activeFlag = true;
bool setTimeoutFlag = true;
bool bledFlag = false;
bool tledFlag = true;

enum { S_IDLE, S_WORK, S_AFK } systemState = S_IDLE;
int curBright;
int ledBright = 100;
int b_ledBright = 100;

#define EVERY_MS(x)                  \
  static uint32_t tmr;               \
  bool flag = millis() - tmr >= (x); \
  if (flag) tmr = millis();          \
  if (flag)
//

void setup() {
  FastLED.addLeds<WS2812, LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(20);

  pinMode(MOSFET, OUTPUT);
  pinMode(B_MOSFET, OUTPUT);
  pinMode(SPK, OUTPUT);
  pinMode(PRI, INPUT);
  pinMode(BTN, INPUT);
  pinMode(LDR, INPUT);

  T_BTN.setDebounce(50);  // Время дебаунса в миллисекундах
  T_BTN.setTimeout(1000);  // Таймаут для удерживания кнопки в миллисекундах
  T_BTN.setClickTimeout(
      500);  // Таймаут для определения одиночного клика в миллисекундах
  T_BTN.setStepTimeout(
      400);  // Таймаут для определения шагового двойного клика в миллисекундах
  T_BTN.setType(HIGH_PULL);  // Тип кнопки: HIGH_PULL или LOW_PULL
  T_BTN.setDirection(
      NORM_CLOSE);  // Направление кнопки: NORM_OPEN или NORM_CLOSE
  T_BTN.setTickMode(false);

  Serial.begin(9600);
}

void loop() {
  sysytemMode();
  systemStatus();
  T_BTN.tick();
  buttonStatus();
}
void buttonStatus() {
  if (T_BTN.isSingle()) {
    modeFlag = !modeFlag;
    digitalWrite(SPK, HIGH);
  }

  if (T_BTN.isTriple()) {
    activeFlag = !activeFlag;
  }
}

void sysytemMode() {
  if (activeFlag) {
    if (setTimeoutFlag) {
      if (modeFlag) {
        readSensors();
      }
      if (!modeFlag) {
        maualMode();
      }
      systemStatus();
    }
  }
  if (!activeFlag) {
    systemOff();
  }

  if (!setTimeoutFlag) {
  }
}

void setTimeout() {
  FastLED.clear();
  FastLED.show();
}
void systemOff() {
  FastLED.clear();
  FastLED.show();
  digitalWrite(MOSFET, LOW);
  digitalWrite(B_MOSFET, LOW);
}

void systemStatus() {
  EVERY_MS(100) { curBright = analogRead(LDR); }
  if (curBright < 70 && !S_WORK) {
    systemState = S_IDLE;
  }
  if (curBright > 130) {
    systemState = S_AFK;
  }
  if (systemState == S_AFK && curBright < 80) {
    systemState = S_IDLE;
  }
}

void readSensors() {
  static uint32_t timeoutCounter;
  static bool flag1 = true, flag2 = false;
  if (systemState == S_IDLE) {
    digitalWrite(MOSFET, LOW);
    digitalWrite(B_MOSFET, LOW);
    breathe(255, 255, 255, 30);
    if (digitalRead(PRI)) {
      int fadeAmount = 5;
      int brightness = 0;
      flag2 = true;
      systemState = S_WORK;
      timeoutCounter = millis();
      if (flag1) {
        while (brightness <= ledBright) {
          if (bledFlag) {
            analogWrite(B_MOSFET, b_ledBright);
          } else {
            analogWrite(B_MOSFET, LOW);
          }
          if (tledFlag) {
            analogWrite(MOSFET, brightness);
          } else {
            analogWrite(MOSFET, LOW);
          }
          brightness += fadeAmount;
          delay(3000 / ledBright);
            
        }
      }
    }
  }
  if (systemState == S_AFK) {
    breathe(47, 255, 0, 30);
    digitalWrite(MOSFET, LOW);
    digitalWrite(B_MOSFET, LOW);
  }
  if (systemState == S_WORK) {
    int sec = TIMEOUT - ((millis() - timeoutCounter) / 1000);
    breathe(8, 0, 255, sec);
    if (digitalRead(PRI)) {
      timeoutCounter = millis();
    }
    if (!flag1) {
      if (bledFlag) {
        analogWrite(B_MOSFET, b_ledBright);
      } else {
        analogWrite(B_MOSFET, LOW);
      }
      if (tledFlag) {
        analogWrite(MOSFET, ledBright);
      } else {
        analogWrite(MOSFET, LOW);
      }
    }
  }

  if (systemState == S_WORK && millis() - timeoutCounter >= (TIMEOUT * 1000L)) {
    systemState = S_IDLE;
    digitalWrite(MOSFET, LOW);
    digitalWrite(B_MOSFET, LOW);
    flag1 = true;
    flag2 = false;
  }
}

void maualMode() {
  static uint32_t timeoutCounter = millis();
  int fadeAmount = 5;
  int brightStep = 20;
  static bool flag1 = true, flag2 = false;
  ;
  breathe(255, 165, 0, 30);
  if (T_BTN.isDouble()) {
    bledFlag = !bledFlag;
  }

  if (bledFlag) {
    analogWrite(B_MOSFET, b_ledBright);
  } else {
    analogWrite(B_MOSFET, LOW);
  }
  if (tledFlag) {
    analogWrite(MOSFET, ledBright);
  } else {
    analogWrite(MOSFET, LOW);
  }

  if (T_BTN.isStep()) {
    flag2 = true;
    ledBright += 25;
    delay(100);
  }
  
  if (T_BTN.isStep(2)) {
    flag2 = true;
    b_ledBright += 25;
    delay(100);
  }

  if (T_BTN.isStep(1)) {
    flag2 = true;
    if (ledBright < 25) {
      ledBright = 25;
    } else if (ledBright >= 25) {
      ledBright -= 25;
    }
    delay(100);
  }
  if (T_BTN.isStep(3)) {
    flag2 = true;
    if (b_ledBright < 25) {
      b_ledBright = 25;
    } else if (ledBright >= 25) {
      b_ledBright -= 25;
    }
    delay(100);
  }


  if (ledBright >= 225) {
    ledBright = 225;
  }
  if (b_ledBright >= 225) {
    ledBright = 225;
  }

  if (digitalRead(PRI)) {
    timeoutCounter = millis();
  }

  if (millis() - timeoutCounter >= (TIMEOUT_LONG * 1000L)) {
    digitalWrite(MOSFET, LOW);
    digitalWrite(B_MOSFET, LOW);
    modeFlag = !modeFlag;
    timeoutCounter = millis();
  }
}

void breathe(int red, int green, int blue, const uint32_t breathInterval) {
  static int brightness = 0;
  static int fadeAmount = 5;
  static uint32_t lastBreathTime = 0;

  if (millis() - lastBreathTime >= breathInterval) {
    brightness += fadeAmount;
    fadeAmount =
        (brightness <= 0 || brightness >= 255) ? -fadeAmount : fadeAmount;
    fill_solid(leds, NUM_LEDS,
               CRGB(brightness * red / 255, brightness * green / 255,
                    brightness * blue / 255));
    FastLED.show();
    lastBreathTime = millis();
  }
}
