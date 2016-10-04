#include <Bridge.h>

int potPin= A0;  //Declare potPin to be analog pin A0
int LEDPin= 5;  // Declare LEDPin to be arduino pin 9
int readValue;  // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED

void setup() {
  pinMode(potPin, INPUT);  //set potPin to be an input
  pinMode(LEDPin, OUTPUT); //set LEDPin to be an OUTPUT
  Bridge.begin();      // turn on Serial Port
  Console.begin();
}

void loop() {
  
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer
 writeValue = (255./1023.) * readValue; //Calculate Write Value for LED
 analogWrite(LEDPin, writeValue);      //Write to the LED
 Console.print("You are writing a value of ");  //for debugging print your values
 Console.println(writeValue);
 
}
