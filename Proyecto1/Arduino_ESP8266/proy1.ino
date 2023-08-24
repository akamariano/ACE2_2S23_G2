#include <DHT.h>
#define PIN_TRIG D0
#define PIN_ECHO D6
#define LDR_PIN   D7 //Luz
#define DHT_PIN   D5 //Temperatura humedad
#define DHT_TYPE  DHT11
#define MQ135_PIN A0//Calidad Aire
DHT dht(DHT_PIN, DHT_TYPE);
float tiempo;
float distancia;
float temperature;
float humidity;
void setup() {
   Serial.begin(9600);
   pinMode(PIN_TRIG, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
   dht.begin();
}

void loop() {
  
   temperature = dht.readTemperature();
   humidity = dht.readHumidity(); 
   digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   
   digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(PIN_TRIG, LOW);
   
   tiempo = pulseIn(PIN_ECHO, HIGH);
   distancia = tiempo/58.3;
    int lightLevel = analogRead(LDR_PIN);
    
  int airQuality = analogRead(MQ135_PIN);
Serial.print("Temperatura ");
  Serial.println(temperature);
  Serial.print("Humedad ");
  Serial.println(humidity);
Serial.println("Luz");
  Serial.println(lightLevel);
  Serial.println("Distancia: ");
   Serial.println(distancia);
  Serial.print("AIre: ");
  Serial.println(airQuality);

   delay(1000);
}
