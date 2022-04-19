#include <Servo.h>
#include <LiquidCrystal.h>

Servo myServo;
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

const int ServoPin = 11;
const int EnterPin = 10;
const int EnterLEDPin = 9;
const int RedLEDPin = 8;
const int BlueLEDPin = 7;
const int GreenLEDPin = 6;
const int RedSensorPin = A0;
const int BlueSensorPin = A1;
const int GreenSensorPin = A2;

int RedValue = 0;
int BlueValue = 0;
int GreenValue = 0;
int RedInput = 0;
int BlueInput = 0;
int GreenInput = 0;
int RedCode = 243;
int BlueCode = 171;
int GreenCode = 8;
int RedAngle = 0;
int BlueAngle = 0;
int GreenAngle = 0;
int CorrectValues = 0;
int ServoAngle;
int EnterButton = 0;

String ColorInputs;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  pinMode(RedLEDPin, OUTPUT);
  pinMode(BlueLEDPin, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(EnterLEDPin, OUTPUT);
  pinMode(EnterPin, INPUT);

  myServo.attach(ServoPin);
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:  
  RedValue = analogRead(RedSensorPin);
  delay(5);
  BlueValue = analogRead(BlueSensorPin);
  delay(5);
  GreenValue = analogRead(GreenSensorPin);
  delay(5);
  
  RedInput = map(RedValue, 0, 1023, 0, 255);
  BlueInput = map(BlueValue, 0, 1023, 0, 255);
  GreenInput = map(GreenValue, 0, 1023, 0, 255);

  analogWrite(RedLEDPin, RedInput);
  analogWrite(BlueLEDPin, BlueInput);
  analogWrite(GreenLEDPin, GreenInput);

  EnterButton = digitalRead(EnterPin);
  if (EnterButton == LOW)
  {
    digitalWrite(EnterLEDPin, HIGH);

    SetColorInputText();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(ColorInputs);
    lcd.setCursor(0, 1);
    lcd.print("Enter a color.");
  }
  else
  {
    digitalWrite(EnterLEDPin, LOW);

    CorrectValues = 0;

    if (RedInput == RedCode)
    {
      RedAngle = 30;
      CorrectValues += 1;
    }
    else {RedAngle = 0; }
    if (BlueInput == BlueCode)
    {
      BlueAngle = 30;
      CorrectValues += 1;
    }
    else {BlueAngle = 0; }
    if (GreenInput == GreenCode)
    {
      GreenAngle = 30;
      CorrectValues += 1;
    }
    else {GreenAngle = 0; }
  
    SetColorInputText();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(ColorInputs);
    lcd.setCursor(0, 1);
    switch(CorrectValues)
    {
      case 0:
        lcd.print("");
        break;
      case 1:
        lcd.print("That's a start.");
        break;
      case 2:
        lcd.print("Almost...");
        break;
      case 3:
        lcd.print("Correct colors!");
        break;
    }
    delay(1000);
    
    ServoAngle = RedAngle + BlueAngle + GreenAngle;
    myServo.write(ServoAngle);
  
    delay(500);
  }
}

void SetColorInputText()
{
    ColorInputs = "";
    ColorInputs += "R:";
    ColorInputs += RedInput;
    ColorInputs += "B:";
    ColorInputs += BlueInput;
    ColorInputs += "G:";
    ColorInputs += GreenInput;
}
