int pinFan = 9;
int pinTemp = 0;

int fanTimeout = 30 * 1000;
int tempReportInterval = 1000;
int tempThreshold = 30;

int stateFan = LOW;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

void setup()
{
  pinMode(pinFan, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  float curTemperature;

  if (currentMillis - previousMillis1 > tempReportInterval) {
    previousMillis1 = millis();

    curTemperature = getTemperature(pinTemp);

    Serial.println(curTemperature);

    if (curTemperature >= tempThreshold) {
      previousMillis2 = millis();

      if (stateFan == LOW) {
        startFan();
      }
    }
  }

  if (stateFan == HIGH && currentMillis - previousMillis2 > fanTimeout) {
      stopFan();
  }
}

float getTemperature(int pin)
{
  float voltage = (analogRead(pin) * .004882814);
  float temperature = temperature = (voltage - .5) * 100;
  
  return temperature;
}

void startFan()
{
  stateFan = HIGH;

  digitalWrite(pinFan, stateFan);

  Serial.println("Fan started");
}

void stopFan()
{
  stateFan = LOW;

  digitalWrite(pinFan, stateFan);

  Serial.println("Fan stopped");
}