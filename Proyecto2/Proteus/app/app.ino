#include <Arduino.h>
#include "definitions.h"

// Objeto DHT
DHT dht(DHT_PIN, DHT_TYPE);

// Banderas para el estado de ciclos
int lightCurrentCycle = CYCLE_ONE;
int airCurrentCycle = CYCLE_ONE;

// Variables para los temporizadores
const unsigned long secondInterval = 1000;
unsigned long previousMillis = 0;
int timerLight = 0;
int timerAir = 0;

// Flag para evitar colision de temperatura y aire
// 0: Esta libre
// 1: Esta siendo usado por el monitoreo de aire
// 2: Esta siendo usado por el monitoro de temperatura
int fanIsUsed = 0;

String dataReceived = "";

void setup() {
  // Inicia comunicacion serial
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // Inicialización: Sensor DHT11
  dht.begin();

  // Inicialización: Sensor Ultrasonico
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // Inicialización: Sensor de Aire
  pinMode(MQ135_PIN, INPUT);
  
  // Inicialización: Sensor de Luz
  pinMode(LDR_PIN, INPUT);

  // Inicialización: LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Inicialización: Ventilador
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

void generatePullTrigger() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(4);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
}

bool thereIsPerson(long distance) {
  if (distance <= 0) {
    return false;
  } else if (distance < MIN_DISTANCE) {
    return true;
  } else {
    return false;
  }
}

void printSensorValues(long distance, float temperature, float humidity, float air, float light) {
  Serial1.println("--------------");
  Serial1.print("Distancia (cm): ");
  Serial1.println(distance);
  Serial1.print("Temperatura (c): ");
  Serial1.println(temperature);
  Serial1.print("Humedad (%): ");
  Serial1.println(humidity);
  Serial1.print("Aire (ppm): ");
  Serial1.println(air);
  Serial1.print("Luz (Lum): ");
  Serial1.println(light);
}

void sendSensorValues(long distance, float temperature, float humidity, float air, float light) {
  Serial.print("Distancia ");
  Serial.println(distance);
  Serial.print("Temperatura ");
  Serial.println(temperature);
  Serial.print("Humedad ");
  Serial.println(humidity);
  Serial.print("Aire ");
  Serial.println(air);
  Serial.print("Luz ");
  Serial.println(light);
}

void sendAlert(String keyAlert) {
  return;
}

int updateTimer(int timer) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= secondInterval) {
    previousMillis = currentMillis;
    return (timer + 1);
  }
  return timer;
}

void monitorAirQuality(float airQuality) {
  if (airQuality > MIN_CO2) {
    // Si el aire está contaminado, se actualiza el temporizador.
    timerAir = updateTimer(timerAir);
    switch (airCurrentCycle) {
      case CYCLE_ONE:
        if (timerAir >= TIMER_LIMIT_AIR) {
          // Enviar alerta y pasar al siguiente ciclo
          sendAlert(AIR_ALERT_1);
          airCurrentCycle = CYCLE_TWO;
        }
        break;
      case CYCLE_TWO:
        if (timerAir >= TIMER_LIMIT_AIR) {
          // Iniciar limpieza de aire
          if (fanIsUsed == 0){
            fanIsUsed = 1;
            digitalWrite(FAN_PIN, HIGH);

          }        
          // Reiniciar temporizador y pasar al siguiente ciclo
          timerAir = 0;
          airCurrentCycle = CYCLE_THREE;
        }
        break;
      case CYCLE_THREE:
        if (timerAir >= TIMER_LIMIT_FAN) {
          // Finalizar limpieza de aire
          if(fanIsUsed == 1){
            fanIsUsed = 0;
            digitalWrite(FAN_PIN, LOW);
          }
          
          // Reiniciar temporizador y reiniciar ciclado
          timerAir = 0;
          airCurrentCycle = CYCLE_ONE;
          sendAlert(AIR_ALERT_2);
        }
        break;
    }
  } else {
    // Si el aire está en nivel aceptable, se reinicia el temporizador y el ciclado
    timerAir = 0;
    airCurrentCycle = CYCLE_ONE;
  }
  return;
}

/*
  Descripcion:  Leer la bandera de encendido de la DB para encender la luz.
                Si viene un dato L1 en la DB extraer el valor que contiene.
                1: Encender LED
                2: Apagar LED
*/
void switchLight() {
  // String sValue;
  // if (Firebase.RTDB.getString(&Proyecto1, "/L1")) {
  //   if (Proyecto1.dataType() == "string") {
  //     sValue = Proyecto1.stringData();
  //     int a = sValue.toInt();
  //     if (a == 1) {
  //       digitalWrite(LED_PIN, HIGH);
  //     } else {
  //       digitalWrite(LED_PIN, LOW);
  //     }
  //   }
  // }
}

void monitorLight(long distance) {
  // Verificar si hay alguna persona en la habitacion
  if (thereIsPerson(distance)) {
    // Reiniciar temporizador y el ciclo actual a 1.
    timerLight = 0;
    lightCurrentCycle = CYCLE_ONE;
    // TODO: La luz puede ser manipulada manualmente
    switchLight();
    return;
  }

  // Verificar si no hay alguna persona y la luz está encendida
  if (!thereIsPerson(distance) && (digitalRead(LED_PIN) == HIGH)) {
    // Actualizar temporizador
    timerLight = updateTimer(timerLight);

    switch (lightCurrentCycle) {
      case CYCLE_ONE:
        // Verificar si terminó el temporizador
        if (timerLight >= TIMER_LIMIT_LIGHT) {
          // Enviar alerta
          sendAlert(LIGHT_ALERT_1);

          // Reiniciar temporizador y pasar al siguiente ciclo
          timerLight = 0;
          lightCurrentCycle = CYCLE_TWO;
        }
        break;
      case CYCLE_TWO:
        // Verificar si terminó el temporizador
        if (timerLight >= TIMER_LIMIT_LIGHT) {
          // Enviar alerta
          sendAlert(LIGHT_ALERT_2);

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

void switchTemperatureFan() {
  // String sValue;
  // if (Firebase.RTDB.getString(&Proyecto1, "/T1")) {
  //   if (Proyecto1.dataType() == "string") {
  //     sValue = Proyecto1.stringData();
  //     int a = sValue.toInt();
  //     if (a == 1) {
  //       fanIsUsed = 2;
  //       digitalWrite(FAN_PIN, HIGH);
  //     } else {
  //       fanIsUsed = 0;
  //       digitalWrite(FAN_PIN, LOW);
  //     }
  //   }
  // }
}

void monitorTemperature(float temperature) {
  // Si el FAN está apagado, detectar cambios
  if (digitalRead(FAN_PIN) == LOW) {
    switchTemperatureFan();
    return;
  }

  // Si la temperatura está arriba del máximo y el FAN está activo: Continuar
  if (temperature >= MAX_TEMPERATURE && digitalRead(FAN_PIN) == HIGH){
    return;
  }
  
  // Si la temperatura está debajo del máximo y el FAN está activo: Apagar FAN
  if (temperature < MAX_TEMPERATURE && digitalRead(FAN_PIN) == HIGH && fanIsUsed == 2){
    sendAlert(TEMP_ALERT_1);
    switchTemperatureFan();
    return;
  }
}

void loop() {
  // Leer datos de los sensores
  generatePullTrigger();
  long time = pulseIn(PIN_ECHO, HIGH);
  long distance = time / 58.3;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float air = analogRead(MQ135_PIN);
  float light = analogRead(LDR_PIN);

  // Imprimir datos de los sensores
  printSensorValues(distance, temperature, humidity, air, light);
  
  while (Serial.available() > 0) {
    char character = Serial.read(); // Lee un carácter

    // Si se recibe un carácter de nueva línea, significa que la cadena ha terminado
    if (character == '\n') {
      // Haz algo con la cadena recibida, por ejemplo, imprimir en el puerto serie
      Serial1.print("\nCadena recibida: ");
      Serial1.println(dataReceived);

      // Limpia la variable para recibir la próxima cadena
      dataReceived = "";
    } else {
      // Agrega el carácter a la cadena en construcción
      dataReceived += character;
    }
  }

  sendSensorValues(distance, temperature, humidity, air, light);

  // Monitor de luz
  // monitorLight(distance);

  // Monitor de calidad de aire
  // monitorAirQuality(air);

  // Monitor de temperatura
  // monitorTemperature(temperature);

  delay(1000);
}
