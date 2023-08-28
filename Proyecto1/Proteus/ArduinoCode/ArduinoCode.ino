/*
  Arquitectura de Computadores y Ensambladores 1
  Grupo: 03
  Integrantes:
    - Samuel Zea
    - Jeser Rodas 
    - Mariano Rac
    - Harry Sanic
    - Kevin García
*/

#include "definitions.h"

// Objeto DHT
DHT dht(DHT_PIN, DHT_TYPE);

// Variables para el temporizador
const unsigned long secondInterval = 1000;
unsigned long previousMillis = 0;
int timerLight = 0;

// Banderas
bool isFanOn = false;

// Banderas para el estado de ciclos
int lightCurrentCycle = CYCLE_ONE;

void generatePullTrigger() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(4);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
}

void printSensorValues(long distance, float temperature, int lightLevel, int airQuality) {
  Serial.println("--------------");
  Serial.print("Distancia (cm): ");
  Serial.println(distance);
  Serial.print("Temperatura (c): ");
  Serial.println(temperature);
  Serial.print("Luz (lx): ");
  Serial.println(lightLevel);
  Serial.print("Aire (ppm): ");
  Serial.println(airQuality);
}

bool thereIsPerson(long distance){
  if (distance <= 0) {
    return false;
  } else if (distance < MIN_DISTANCE) {
    return true;
  } else {
    return false;
  }
}


int updateTimer(int timer){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= secondInterval) {
    previousMillis = currentMillis;  
    return (timer + 1);
  }
  return timer;
}

void sendAlert(String alert){
  // TODO: Enviar alerta a usuaria a la App.
  Serial.println(alert);
}

void monitorLight(long distance){
  // Verificar si hay alguna persona en la habitacion
  if (thereIsPerson(distance)){
    // Reiniciar temporizador y el ciclo actual a 1.
    timerLight = 0;
    lightCurrentCycle = CYCLE_ONE;
    // TODO: La luz puede ser manipulada manualmente
    if (digitalRead(LED_SWITCH_PIN) == HIGH){
      (digitalRead(LED_PIN) == HIGH) ? digitalWrite(LED_PIN, LOW) : digitalWrite(LED_PIN, HIGH);
      delay(100);
    }
    return;
  }

  // Verificar si no hay alguna persona y la luz está encendida
  if (!thereIsPerson(distance) && (digitalRead(LED_PIN) == HIGH)){
    // Actualizar temporizador
    timerLight = updateTimer(timerLight);

    switch(lightCurrentCycle){
      case CYCLE_ONE:
        // Verificar si terminó el temporizador
        if (timerLight >= TIMER_LIMIT_LIGHT){
          // Enviar alerta
          sendAlert("LUZ ALERTA 1: La luz esta encendida y la habitacion esta vacia");
          
          // Reiniciar temporizador y pasar al siguiente ciclo
          timerLight = 0;
          lightCurrentCycle = CYCLE_TWO;
        }
        break;
      case CYCLE_TWO:
        // Verificar si terminó el temporizador
        if (timerLight >= TIMER_LIMIT_LIGHT){
          // Enviar alerta
          sendAlert("LUZ ALERTA 2: Apagando la luz de la habitación");

          // Reiniciar temporizador y reiniciar el ciclo.
          timerLight = 0;
          lightCurrentCycle = CYCLE_ONE;
          
          // Apagar la luz
          digitalWrite(LED_PIN, LOW);
        }
        break;
    }
  }
  return;
}

void monitorTemperature(float temperature){
  if (temperature > MIN_TEMPERATURE && !isFanOn) {
    digitalWrite(FAN_PIN, HIGH);
    isFanOn = true;
  
    Serial.println("FAN: ENCENDIENDO VENTILADOR");
    return;
  }
  
  if (temperature < MIN_TEMPERATURE && isFanOn) {
    digitalWrite(FAN_PIN, LOW);
    isFanOn = false;
    Serial.println("FAN: APAGANDO VENTILADOR");
    return; 
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Pins de sensor de proximidad
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // Pins de sensor MQ135
  pinMode(MQ135_PIN, INPUT);

  // Pins de sensor LDR
  pinMode(LDR_PIN, INPUT);

  // Pins de ventilador
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  // Pins de LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  // Obtener valores de los sensores
  generatePullTrigger();
  long time = pulseIn(PIN_ECHO, HIGH);
  long distance = time / 58.3;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightLevel = analogRead(LDR_PIN);
  int airQuality = analogRead(MQ135_PIN);

  // Imprimir los valores en Monitor Serial
  printSensorValues(distance, temperature, lightLevel, airQuality);

  // Monitorear la luz.
  monitorLight(distance);

  // Monitorear la temperatura.
  monitorTemperature(temperature);

  delay(1000);
}