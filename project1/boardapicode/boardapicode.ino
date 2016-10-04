#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#include <ArduinoJson.h>


BridgeServer server;
unsigned long startTime;
unsigned long elapsedTime;
int actionValue;
int oldValue;
double baselineTemp = 21.0;


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  pinMode(8, OUTPUT); //relay pin

  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  BridgeClient client = server.accept();
  if (client) {
    process(client);
    client.stop();
  }
  delay(50);

}

void process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }
  else if (command == "temp") {
    adjustTemperature(client);
  }
}

void adjustTemperature(BridgeClient client) {
  double newTemp = client.parseFloat();
  baselineTemp = newTemp;
  client.print("New Baseline temperature: ");
  client.print(baselineTemp);
}

void digitalCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  } else {
    value = digitalRead(pin); // checking state of board here
  }

  actionValue = (int)value;


  char myData[1];
  Bridge.get("8", myData, 1);

  oldValue = (int)myData[0];

  if ((oldValue == 48) && (actionValue == 1)) {
    startTime = millis();
  }

  String key = String(pin);
  Bridge.put(key, String(actionValue));

  int sensorValue = analogRead(A1);
  double temp = Thermister(sensorValue);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  unsigned long currentTime = millis();
  //if heating is off, timer is zero
  if ((oldValue == 48) || (actionValue == 0)) {
    elapsedTime = 0;
  }
  else   elapsedTime = currentTime - startTime;

  checkTemperature(temp, pin);

  root["status"] = value;
  root["temp"] = temp;
  root["currentTime"] = currentTime;
  root["startTime"] = startTime;
  root["elapsedTime"] = elapsedTime;
  root["baselineTemp"] = baselineTemp;
  root.prettyPrintTo(client);
}

void checkTemperature(double Temp, int pin) {
  if (Temp > baselineTemp) {
    digitalWrite(pin, 0);
    String key = String(pin);
    Bridge.put(key, String(actionValue));
  }
}

double Thermister(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
  double Temp;
  Temp = log(((10240000 / RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;              // Convert Kelvin to Celsius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
  return Temp;
}

void calculteTemperature(BridgeClient client)
{
  int sensorValue = analogRead(A1);
  // convert the reading to millivolts:
  float voltage = sensorValue * (5000.0f / 1024.0f);
  // convert the millivolts to temperature celsius:
  float temperature = (voltage - 500.0f) / 10.0f;
  // print the temperature:

  client.print(" &deg;C");
}