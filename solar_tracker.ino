#include <Servo.h>

Servo servoX;
Servo servoY;

int ldrTopLeft = A0;
int ldrTopRight = A1;
int ldrBottomLeft = A2;
int ldrBottomRight = A3;
int tol = 50;

void setup() {
  servoX.attach(9);
  servoY.attach(10);
  servoX.write(90);
  servoY.write(90);
  delay(1000);
}

void loop() {
  int tl = analogRead(ldrTopLeft);
  int tr = analogRead(ldrTopRight);
  int bl = analogRead(ldrBottomLeft);
  int br = analogRead(ldrBottomRight);

  int avgTop = (tl + tr) / 2;
  int avgBottom = (bl + br) / 2;
  int avgLeft = (tl + bl) / 2;
  int avgRight = (tr + br) / 2;

  int posX = servoX.read();
  int posY = servoY.read();

  if (abs(avgTop - avgBottom) > tol) {
    if (avgTop > avgBottom && posY < 180) posY++;
    else if (avgTop < avgBottom && posY > 0) posY--;
    servoY.write(posY);
  }

  if (abs(avgLeft - avgRight) > tol) {
    if (avgLeft > avgRight && posX > 0) posX--;
    else if (avgLeft < avgRight && posX < 180) posX++;
    servoX.write(posX);
  }

  delay(200);
}
