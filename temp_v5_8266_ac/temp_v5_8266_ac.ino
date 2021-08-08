#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Relay setup on D1
int relay = 5;
boolean relay_status = false;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
  // Init relay
  pinMode(relay, OUTPUT);
}

void loop() {
  sensors.requestTemperatures(); 
  //float temperatureC = sensors.getTempCByIndex(0);
  float tempF = sensors.getTempFByIndex(0);
  //Serial.print(temperatureC);
  //Serial.println(" C");
  Serial.print(tempF);
  Serial.println(" F");

  // Temp control logic
  if (tempF >= 75.5) {
    digitalWrite(relay, HIGH);
    relay_status = true; 
  }
  else if (tempF >= 75 && tempF < 75.5 && relay_status == true) {
    digitalWrite(relay, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
    relay_status = false;      
  }
  
  delay(10000);
}
