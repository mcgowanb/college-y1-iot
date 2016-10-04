#include <Bridge.h>
#include <YunServer.h>
#include <BridgeClient.h>

const int relayControl = 2;
int buttonState;
YunServer server;


void setup() {

  pinMode(relayControl, OUTPUT);
  buttonState = 0;

  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
   Bridge.begin();
  Console.begin();
  server.listenOnLocalhost();
  server.begin();
  Console.println("Ready");
  digitalWrite(13, HIGH);
}

void loop() {
  
  buttonState = digitalRead(relayControl);
  BridgeClient client = server.accept();
  
  if (client) {
    Console.println("Client Connected");
    String request = client.readString();
    Console.println(request);
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}

void process(BridgeClient client) {
  String command = client.readStringUntil('\r');
  String otherCommand = client.readStringUntil('/');
  
  client.println("Printing until R" + command);
  client.println("Printing until slash" + otherCommand);
  Console.println("Printing until R" + command);
  Console.println("Printing until slash" + otherCommand);
}
