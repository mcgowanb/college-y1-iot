#include <Bridge.h>

int potPin= A0;  //Declare potPin to be analog pin A0
int LEDPin= 5;  // Declare LEDPin to be arduino digital pin 5
int readValue;  // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED
int button = 2;
int relay = 3;

void setup() {
  //led setup
  pinMode(potPin, INPUT);  
  pinMode(LEDPin, OUTPUT); 
  
  //relay setup
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  
  Bridge.begin();      // turn on bridge for serial data
  Console.begin();
}

void loop() {
  //led dimmer code
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer
 writeValue = (255./1023.) * readValue; //Calculate Write Value for LED
 analogWrite(LEDPin, writeValue);      //Write to the LED
 Console.print("You are writing a value of ");  //for debugging print your values
 Console.println(writeValue);

//relay code
 if (digitalRead(button)==HIGH)
  {
    digitalWrite(relay, HIGH);
    delay(100);
    Console.println("Relay Switch is on");
  }
 else
  {
    digitalWrite(relay, LOW);
  }
 
}
