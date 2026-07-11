// INFORMATION
// -------------------------------------------
// Thumb = 4 == (4) Servo
// Index = 10 == (6) Servo
// Middle = 15 == (5) Servo
// Ring = 7 == (3) Servo
// Pinky = 12 == (2) Servo

// A5 == SCL
// A4 == SDA
// -------------------------------------------


#include <Adafruit_PWMServoDriver.h>  // PWM Servo Controller Library
#include <LiquidCrystal_I2C.h> // I2C LCD Library
#include <Wire.h> // Wire Library

Adafruit_PWMServoDriver pwm; // Define the Adafruit PWM Library as "pwm"
LiquidCrystal_I2C lcd(0x27,  16, 2); // Define the LiquidCrystal Library as "lcd" and setting dimenions

#define SERVOMIN 100 // 0 Degree
#define SERVOMAX 600 // 180 Degree
#define SERVOMID 350 // 90 Degree
#define SERVONUM 5 // Number of Servos

int servoPins[5] = {11, 7, 15, 12, 8}; // Define Servo Pins on PWM Controller (7, 8, 11, 12, 15)
int buttonPins[5] = {2, 3, 4, 5, 6}; // Define Button Pins on Arduino'
long loopcount = 0;

int VoltPerCent() { // Calculates the voltage of the batteries through a voltage divider
  int voltpercent;
  float value, voltage=0, voltmax=8.4, voltmin=6.4, voltageraw=0;
  value = analogRead(A2); // Read voltage divider

  voltageraw = value * (5.0/1023.0);
  voltage = voltageraw * ((50.0+61.0)/61.0); // Voltage Divider R1=50kOHM & R2=61kOHM
  voltpercent = (voltage-voltmin)*100.0/(voltmax - voltmin);

  return voltpercent;
}

void LoopCounter(int loops){ // Counts the number of Loops
  loopcount++;

  if(loopcount == loops){ // Execute after a set number of loops
    if(VoltPerCent() > 25){
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("Battery: ");
      lcd.setCursor(9,0); lcd.print(VoltPerCent());
      lcd.setCursor(11,0); lcd.print("%");
      lcd.setCursor(0,1); lcd.print("Operating!");
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("Battery: ");
      lcd.setCursor(9,0); lcd.print(VoltPerCent());
      lcd.setCursor(11,0); lcd.print("%");
      lcd.setCursor(0,1); lcd.print("Please Charge!");
    }

    loopcount = 0;
  }
}

int AngleToPulse(int ang) { // Convert Angle to Pulses for Servo
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // Maps the Angles to Pulses
  return pulse;
}

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial.println("Start Test");

  pwm.begin(); // Initialize PWM Servo Controller
  pwm.setPWMFreq(50); // Set Servo Frequency

  lcd.init(); // Initialize LCD Screen
  lcd.backlight(); // Initialize LCD Backlight

  lcd.setCursor(0,0); lcd.print("Initializing"); // Write on Top Row
  lcd.setCursor(0,1); lcd.print("Please Wait..."); // Write on Bottom Row
  

  for(int i = 0; i < SERVONUM; i++){ // Reset All Servos to 0 Degree
    pwm.setPWM(servoPins[i], 0, AngleToPulse(0));
    delay(1000);
  }

  lcd.clear(); lcd.print("Welcome!"); // Clear LCD and Print
  delay(750);
  lcd.clear();

  LoopCounter(1);

  // Define Pins on Arduino For Buttons
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
}

void loop() {
  LoopCounter(50);

  int incomingAngle = Serial.read();

  // for (int i = 0; i < SERVONUM; i++) {  // Control Fingers with 5 Buttons
  //   if (digitalRead(buttonPins[i]) == HIGH) {
  //     pwm.setPWM(servoPins[i], 0, AngleToPulse(0)); // released
  //     Serial.println("Extend");
  //   }
  //   else if(digitalRead(buttonPins[i]) == LOW) {
  //     pwm.setPWM(servoPins[i], 0, AngleToPulse(130));   // pressed
  //     Serial.println("Curl");
  //   }
  // }

  if (Serial.available() >= 0) {
    if (incomingAngle == 90) {
      pwm.setPWM(servoPins[3], 0, AngleToPulse(130));
      Serial.println(incomingAngle);
    }
    else if (incomingAngle == 0){
      pwm.setPWM(servoPins[3], 0, AngleToPulse(0));
    }
  Serial.println(incomingAngle);
  }

  delay(25);

}