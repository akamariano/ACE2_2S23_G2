#include "definitions.h"

#include <Arduino.h>
#include <Servo.h>

DHT dht(DHT_PIN, DHT_TYPE);
Servo servoMotor;

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

  // Inicialización: Sensor DHT11
  dht.begin();

  // Inicialización: Sensor Ultrasonico
  pinMode(PIN_TRIGGER, OUTPUT);
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

  // Inicialización: Gate
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(GATE_PIN, LOW);

  // Inicializacion: Servo
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(140);   // Inicializa el servo en grados iniciales
}

void generatePullTrigger() {
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(4);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
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
  //Serial1.println("--------------");
  //Serial1.print("Distancia (cm): ");
  //Serial1.println(distance);
  //Serial1.print("Temperatura (c): ");
  //Serial1.println(temperature);
  //Serial1.print("Humedad (%): ");
  //Serial1.println(humidity);
  //Serial1.print("Aire (ppm): ");
  //Serial1.println(air);
  //Serial1.print("Luz (Lum): ");
  //Serial1.println(light);
}

void sendSensorValues(long distance, float temperature, float humidity, float air, float light) {
  Serial.print("arqui2_g2_distancia ");
  Serial.println(distance);
  Serial.print("arqui2_g2_temperatura ");
  Serial.println(temperature);
  Serial.print("arqui2_g2_humedad ");
  Serial.println(humidity);
  Serial.print("arqui2_g2_aire ");
  Serial.println(air);
  Serial.print("arqui2_g2_luz ");
  Serial.println(light);
}

/**
  Envia una alerta a través de conexión serial.
*/
void sendAlert(String keyAlert) {
  Serial.print("arqui2_g2_alerta ");
  Serial.println(keyAlert);
}

/**
  Actualiza un temporizador cada vez que se detecta que ha pasado un segundo.

  @param timer El temporizador a actualizar
  @return El temporizador actualizado
*/
int updateTimer(int timer) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= secondInterval) {
    previousMillis = currentMillis;
    return (timer + 1);
  }
  return timer;
}

/**
  Monitorea la calidad del aire y dependiendo de la misma,
  decide si activar la ventilación. Además, maneja la lógica de los estados de 
  esta función.

  @param airQuality Valor actual de la calidad del aire.
*/
void monitorAirQuality(float airQuality) {
  if (airQuality > MIN_CO2 || airCurrentCycle != CYCLE_ONE) {
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
  if (dataReceived == "") {
    return;
  } else if (dataReceived == "arqui2_g2_led 0") {
    digitalWrite(LED_PIN, LOW);
  } else if (dataReceived == "arqui2_g2_led 1") {
    digitalWrite(LED_PIN, HIGH);
  }
}

void monitorLight(long distance) {


  // Verificar si hay alguna persona en la habitacion
  if (thereIsPerson(distance)) {
    // Reiniciar temporizador y el ciclo actual a 1.
    timerLight = 0;
    lightCurrentCycle = CYCLE_ONE;
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

/**
  Método que verifica si se recibieron datos a través de la conexión serial.
  Luego, según lo recibido, activa o desactiva el FAN.

  TODO: Implementar dos velocidades
*/
void switchTemperatureFan() {
  if (dataReceived == "") {
    return;
  } else if (dataReceived == "arqui2_g2_fan 0") {
    fanIsUsed = 0;
    digitalWrite(FAN_PIN, LOW);
  } else if (dataReceived == "arqui2_g2_fan 1") {
    fanIsUsed = 2;
    digitalWrite(FAN_PIN, HIGH);
    analogWrite(GATE_PIN, 100);
  } else if (dataReceived == "arqui2_g2_fan 2") {
    fanIsUsed = 2;
    digitalWrite(FAN_PIN, HIGH);
    analogWrite(GATE_PIN, 1000);
  }
}

void monitorTemperature(float temperature) {
  // Si el FAN está apagado o siendo utilizado por esta herramienta, detectar cambios
  if (digitalRead(FAN_PIN) == LOW or (digitalRead(FAN_PIN) == HIGH && fanIsUsed == 2)) {
    switchTemperatureFan();
    return;
  }
}

void rotateServoMotor(int angle) {
  if (angle == 0) {
    return;
  } else if (angle > 0) {
    for (int pos = 0; pos <= angle; pos += 1) {
      servoMotor.write(pos);
      delay(15);
    }
  } else if (angle < 0) {
    for (int position = 180; position >= angle; position -= 1) {
      servoMotor.write(position);
      delay(15);
    }
  }
}

void switchActuator() {
  if (dataReceived == "") {
    return;
  } else if (dataReceived == "arqui2_g2_actuador 0") {
    // Mueve el servo de 0 a 130 grados
    for (int pos = 0; pos <= 130; pos += 1) {
      servoMotor.write(pos);
      delay(15);  // Pequeño retardo para suavizar el movimiento
    }
  } else if (dataReceived == "arqui2_g2_actuador 1") {
    // Mueve el servo de 130 a 0 grados
    for (int pos = 130; pos >= 0; pos -= 1) {
      servoMotor.write(pos);
      delay(15);  // Pequeño retardo para suavizar el movimiento
    }
  }
}

void monitorActuator() {
  switchActuator();
}

/**
  Verifica si hay datos entrantes por la conexión serial.

  @return Cadena de los datos entrantes, si no hay, cadena vacia.
*/
String checkDataInput() {
  String dataReceived = "";

  while (Serial.available() > 0) {
    char character = Serial.read();

    // Si se recibe un carácter de nueva línea, significa que la cadena ha terminado
    if (character == '\n') {
      break;
    } else {
      // Agrega el carácter a la cadena en construcción
      dataReceived += character;
    }
  }

  // Si se recibieron datos, se imprimen en el Monitor
  if (dataReceived != "") {
    //Serial1.print(">> Datos recibidos -> ");
    //Serial1.println(dataReceived);
  }

  return dataReceived;
}


void loop() {
  dataReceived = checkDataInput();

  // Leer datos de los sensores
  generatePullTrigger();
  long time = pulseIn(PIN_ECHO, HIGH);
  long distance = time / 58.3;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float air = analogRead(MQ135_PIN);
  float light = analogRead(LDR_PIN);

  // Imprimir datos de los sensores en el monitor.
  printSensorValues(distance, temperature, humidity, air, light);

  // Enviar los datos de los sensores.
  sendSensorValues(distance, temperature, humidity, air, light);

  // Monitor de luz (TEST)
  monitorLight(distance);

  // Monitor de calidad de aire (TEST)
  monitorAirQuality(air);

  // Monitor de temperatura (TEST)
  monitorTemperature(temperature);

  // Monitor de Servo (TEST)
  monitorActuator();

  delay(10000);
}
