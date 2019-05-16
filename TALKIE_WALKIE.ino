#include <Adafruit_NeoPixel.h>

#include <Wire.h>
#include "rgb_lcd.h"

#include <PS2Keyboard.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 10 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 600

// How many pixels to light
int lightUp = 0;

// Variable for start and end value
int start = 0;
int ended = 0;

// Variable to store steps triggered
int currentStep = 0;
int nextStep = 1;

// Pins for keyboard
const int DataPin = 8;
const int IRQpin =  3;

//Variable to store input from keyboard
String input;

// Select the input pin for LDR
int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorPin4 = A3;
int sensorPin5 = A4;
int sensorPin6 = A5;
int sensorPin7 = A6;
int sensorPin8 = A7;
int sensorPin9 = A8;
int sensorPin10 = A9;
int sensorPin11 = A10;
int sensorPin12 = A11;
int sensorPin13 = A12;
int sensorPin14 = A13;


// Declaire variable to store LDR input
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0; 
int sensorValue4 = 0; 
int sensorValue5 = 0;
int sensorValue6 = 0;
int sensorValue7 = 0; 
int sensorValue8 = 0; 
int sensorValue9 = 0; 
int sensorValue10 = 0; 
int sensorValue11 = 0; 
int sensorValue12 = 0; 
int sensorValue13 = 0; 
int sensorValue14 = 0; 

// Declaire LDR value for laser (when above, laser is on it, when below, laser interrupted)
int sensorLimit = 1020;

// Declaire keybaord to be used
PS2Keyboard keyboard;

rgb_lcd lcd;

// Declaire led strip to be used
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//#define DELAYVAL 1000 // Time (in milliseconds) to pause between pixels

void setup() {

  pixels.begin(); // Initialise NeoPixel strip 

  keyboard.begin(DataPin, IRQpin); // Initialise keyboard

  Serial.begin(9600); // Initialise and set serial port for communication

  lcd.begin(16, 2); // set up the LCD's number of columns and rows:

  lcd.write("Type a message:");
}

void loop() {

  // read values from sensor and store
  sensorValue1 = analogRead(sensorPin1); 
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  sensorValue5 = analogRead(sensorPin5);
  sensorValue6 = analogRead(sensorPin6);
  sensorValue7 = analogRead(sensorPin7);
  sensorValue8 = analogRead(sensorPin8);
  sensorValue9 = analogRead(sensorPin9);
  sensorValue10 = analogRead(sensorPin10);
  sensorValue11 = analogRead(sensorPin11);
  sensorValue12 = analogRead(sensorPin12);
  sensorValue13 = analogRead(sensorPin13);
  sensorValue14 = analogRead(sensorPin14);
  delay(60);

  if (currentStep == nextStep) {
    lightUp = lightUp + 50;
    nextStep++;
  } 
  
  if (sensorValue1 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 1;
    start = 0;
  } else if (sensorValue2 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 2;
  } else if (sensorValue3 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 3;
  } else if (sensorValue4 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 4;
  } else if (sensorValue5 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 5;
  } else if (sensorValue6 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 6;
  } else if (sensorValue7 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 7;
  } else if (sensorValue8 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 8;
  } else if (sensorValue9 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 9;
  } else if (sensorValue10 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 10;
  } else if (sensorValue11 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 11;
  } else if (sensorValue12 < sensorLimit && currentStep == nextStep - 1){
    currentStep = 12;
    nextStep = 0;
  } else if (currentStep != 0 && currentStep != 12){
    noise();
    delay(1500);
  }
    
  lights();

  // If statements to encode and start session

   if (currentStep == 0 && start == 0){
      keyboardLCD();
    }

   if (sensorValue13 < 200) {
      start = 1;
    }

  if (start == 1) {
    lightStart();
    encodeMessage();
  } 

  if (sensorValue14 < 200) {
    ended = 1;
  }

  if (ended == 1) {
    decodeMessage();
    start = 0;
    ended = 0;
    lightUp = 0;
    input = "";
    currentStep = 0;
    nextStep = 1;
    pixels.clear();
    pixels.show();
  }
  
}

void keyboardLCD() {

  lcd.setCursor(0, 1);
  lcd.print(input);
  
  if (keyboard.available()) {
          
    // read the input and store
    char c = keyboard.read();

    // check for some of the special keys
    if (c == PS2_DELETE) {
      input.remove(input.length() - 1);
      lcd.clear();
      lcd.write("Type a message:");
    } else if (c == PS2_ESC) {
      input = "";
      lcd.clear();
      lcd.write("Type a message:");
    } else {
      input = input + String(c);
    }
  }
  
}

void lights(){

  for(int i=0; i<lightUp; i++) { // For each pixel... = i+4
    
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(100, 100, 100));
    
    // Send the updated pixel colors to the hardware.
    pixels.show();

    }
}

void lightStart(){
    pixels.clear();
    pixels.show();

    for(int i=0; i<10; i++) { // For each pixel... = i+4
    
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(100, 100, 100));
    
    // Send the updated pixel colors to the hardware.
    pixels.show();

    }

   delay(1500);
}

void noise(){

  String weirdText = "?><\|0987654321+=}{;~";

  char r = weirdText.charAt(random(0,20));
  
  input.setCharAt(random(0,16), r);
  
}

void encodeMessage(){
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Message encoded!");
  lcd.setCursor(0, 1);
  lcd.write("Sending message...");
}

void decodeMessage(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Message Decoded:");
  lcd.setCursor(0, 1);
  lcd.print(input);

  delay(30000);
}


