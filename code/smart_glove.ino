#include <Wire.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ---------- FLEX PINS ----------
const int flex1 = 34;
const int flex2 = 35;
const int flex3 = 32;

// ---------- MPU6050 ----------
#define MPU6050_ADDR 0x68

const int FLEX_BEND = 10;
const int FLEX_RELEASE = 5;

const int MOTION_THRESHOLD = 3500;
const int MOTION_RELEASE = 1500;

// ---------- LOCKS ----------
bool flexLocked = false;
bool motionLocked = false;

int16_t baseX = 0;
int16_t baseY = 0;

void sendMessage(String message) {
  Serial.println("MESSAGE: " + message);
  SerialBT.println(message);
}

void readMPU(int16_t &x, int16_t &y, int16_t &z) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU6050_ADDR, 6);

  if (Wire.available() == 6) {
    x = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
  }
}

void setup() {

  Serial.begin(115200);
  SerialBT.begin("ESP32_Glove");

  analogReadResolution(12);

  Wire.begin(21, 22);

  // Wake MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  delay(1000);

  // Calibrate starting position
  long totalX = 0;
  long totalY = 0;

  for (int i = 0; i < 20; i++) {
    int16_t x, y, z;
    readMPU(x, y, z);

    totalX += x;
    totalY += y;

    delay(20);
  }

  baseX = totalX / 20;
  baseY = totalY / 20;

  Serial.println("SMART GLOVE READY");
  SerialBT.println("SMART GLOVE READY");
}

void loop() {

  // =================================================
  // FLEX SENSORS
  // =================================================

  int f1 = analogRead(flex1);
  int f2 = analogRead(flex2);
  int f3 = analogRead(flex3);

  bool allFlexReleased =
    (f1 < FLEX_RELEASE) &&
    (f2 < FLEX_RELEASE) &&
    (f3 < FLEX_RELEASE);

  // ---------- FLEX 1 ----------
  if (!flexLocked) {

    if (f1 > FLEX_BEND && f2 < FLEX_BEND && f3 < FLEX_BEND) {

      sendMessage(
        "Hi, I am Gagan. These are my teammates. "
        "We built a smart glove using three flex sensors "
        "and a motion sensor to help people with paralysis "
        "and speech difficulties communicate."
      );

      flexLocked = true;
    }

    // ---------- FLEX 2 ----------
    else if (f1 < FLEX_BEND && f2 > FLEX_BEND && f3 < FLEX_BEND) {

      sendMessage("What are you doing?");

      flexLocked = true;
    }

    // ---------- FLEX 3 ----------
    else if (f1 < FLEX_BEND && f2 < FLEX_BEND && f3 > FLEX_BEND) {

      sendMessage("How are you?");

      flexLocked = true;
    }
  }

  // Unlock after fingers return straight
  if (flexLocked && allFlexReleased) {
    flexLocked = false;
  }


  // =================================================
  // MPU6050
  // =================================================

  int16_t ax, ay, az;

  readMPU(ax, ay, az);

  int dx = ax - baseX;
  int dy = ay - baseY;


  // =================================================
  // MOTION — ONE MESSAGE PER MOVEMENT
  // =================================================

  if (!motionLocked) {

    // LEFT
    if (dx < -MOTION_THRESHOLD) {

      sendMessage("Please come here.");

      motionLocked = true;
    }

    // RIGHT
    else if (dx > MOTION_THRESHOLD) {

      sendMessage("Please wait for me.");

      motionLocked = true;
    }

    // UP
    else if (dy > MOTION_THRESHOLD) {

      sendMessage("I need help.");

      motionLocked = true;
    }

    // DOWN
    else if (dy < -MOTION_THRESHOLD) {

      sendMessage("Thank you for helping me.");

      motionLocked = true;
    }
  }


  // =================================================
  // UNLOCK MOTION
  // =================================================

  if (motionLocked &&
      abs(dx) < MOTION_RELEASE &&
      abs(dy) < MOTION_RELEASE) {

    motionLocked = false;

    baseX = ax;
    baseY = ay;
  }


  // =================================================
  // SERIAL MONITOR
  // =================================================

  Serial.print("FLEX: ");
  Serial.print(f1);
  Serial.print(" ");
  Serial.print(f2);
  Serial.print(" ");
  Serial.print(f3);

  Serial.print(" | MOTION: ");
  Serial.print(dx);
  Serial.print(" ");
  Serial.println(dy);

  delay(100);
}Yeah, I think this is the code I uploaded, and next I want to tell you something. And I don't have any circuit diagram. From your suggestion I made that, and AI photo is, can I put in this? And yeah, tell me.
