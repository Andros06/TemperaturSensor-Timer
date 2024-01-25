#include <Arduino.h>
#include <timer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 11
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

float TempValue = 0.0;  //Lager en variabel for Tempverdi
float HumidValue = 0.0; //Lager en variabel for Humidityverdi

//Lager til ein ny timer
Timer t;

//Funksjon for å lese av temperatur verdi og skrive det til seriel
void TempRead() {
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    TempValue = event.temperature;
    Serial.print("Temperature: ");
    Serial.println(TempValue);
  } else {
    Serial.println("Error reading temperature!");
  }

  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    HumidValue = event.relative_humidity;
    Serial.print("Humidity: ");
    Serial.println(HumidValue);
  } else {
    Serial.println("Error reading humidity!");
  }
}


void setup() {
  Serial.begin(9600);

  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  //setter opp timer intervall, kalle funksjon, og starter timer
  t.setInterval(1000);
  t.setCallback(TempRead);
  t.start();
 
}


void loop() {
  t.update();  //updaterer tida til timeren konstant
}

