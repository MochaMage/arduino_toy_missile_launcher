#include <Servo.h>

const int missilePin = 6;
const int buttonPin = 5;
const int servo1Pin = 3;
const int servo2Pin = 9;
const int joystickHorPin = A0;
const int joystickVertPin = A1;

Servo servo1;
Servo servo2;

int buttonState = LOW;
int lastButtonState = LOW;
int lastServo1Value = 0;
int lastServo2Value = 0;

void setup() 
{
  pinMode(missilePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
}

void loop()
{
  // Read in joystick
  int joyHorizontalPos = analogRead(joystickHorPin);
  int joyVerticalPos = analogRead(joystickVertPin);

  // Output to servos
  int mappedJoyHorizontalPos = map(joyHorizontalPos, 0, 1023, 0, 180);
  if(mappedJoyHorizontalPos != lastServo1Value)
  {
    servo1.write(mappedJoyHorizontalPos);
  } 
  
  int mappedJoyVerticalPos = map(joyVerticalPos, 0, 1023, 0, 180);
  if(mappedJoyVerticalPos != lastServo2Value)
  {
    servo2.write(mappedJoyVerticalPos);
  } 
  
  // Read in button data to see if missiles can be fired
  buttonState = digitalRead(buttonPin);
  if(buttonState != lastButtonState)
  {
    if(buttonState == HIGH)
    {
      analogWrite(missilePin, 255);
      delay(100);
      analogWrite(missilePin, 0);
      delay(200);
    }
  }
  lastButtonState = buttonState;
  lastServo1Value = mappedJoyHorizontalPos;
  lastServo2Value = mappedJoyVerticalPos;
}
