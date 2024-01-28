
//dette inkluderer nødvendig library for å kunne bruke timer og dht sensor for temp og humidity
#include <Arduino.h>
#include <timer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 11     //Lager en konstant med navn DHTPIN med verdi 11
#define DHTTYPE DHT11 //Lager en konstant med navn DHTTYPE med verdi DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);  //bruker konstantane til å sette verdier for dht som brukast til DHT library


//bruker float pga sensor gir presise målinger, også lurt forhold til kva data type library bruker
float TempValue = 0.0;  //Lager en variabel for Tempverdi
float HumidValue = 0.0; //Lager en variabel for Humidityverdi

//Lager til ein ny timer
Timer t;

//Funksjon for å lese av temperatur verdi og skrive det til seriel
void TempRead() {
  sensors_event_t event; //lager en event variabel som kan inneholde fleire verdier. Denne henta informasjon fra DHT library om humidity og temperature
  
  dht.temperature().getEvent(&event); //dht.temperature spesifiserer at temperatur fra dht skal hentast. getEvent henter verdiane fra eventen fra tidligare.
  if (!isnan(event.temperature)) {
    TempValue = event.temperature; //Setter verdien til TempValue lik event.temperature
    Serial.print("Temperature: "); //Seriel printer teksten "Temperature:"
    Serial.println(TempValue); //Seriel printer verdien til TempValue
  } else {
    Serial.println("Error reading temperature!"); //Seriel printer "Error reading temperature!" dersom temp verdi er ugyldig
  }

  dht.humidity().getEvent(&event); //dht.humidity spesifiserer at humidity fra dht skal hentast. getEvent henter verdiane fra eventen fra tidligare.
  if (!isnan(event.relative_humidity)) {
    HumidValue = event.relative_humidity; //Setter verdien til HumidValue lik event.relative_humidity 
    Serial.print("Humidity: "); //Seriel printer teksten "Humidity"
    Serial.println(HumidValue); //Seriel printer verdien til HumidValue
  } else {
    Serial.println("Error reading humidity!"); //Seriel printer "Error reading humidity!" dersom humidity verdi er ugyldig
  }
}


void setup() {
  Serial.begin(9600); //Starter seriel kommunikasjon

  dht.begin(); //dht.begin initialiserer kommunikasjon nødvendig for sensor library 
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

