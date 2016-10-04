
int button = 3;
int relay = 2;
void setup()
{
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
}

void loop()
{
  if (digitalRead(button)==HIGH)
  {
    digitalWrite(relay, HIGH);
    delay(100);
  }
 else
  {
    digitalWrite(relay, LOW);
  }
}
