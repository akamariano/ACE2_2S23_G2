#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <DHT.h>

// PINES DEL SENSOR ULTRASONICO
#define PIN_TRIG D4
#define PIN_ECHO D2

// PIN DEL SENSOR DE TEMPERATURA Y HUMEDAD
#define DHT_PIN  D5
#define DHT_TYPE DHT11

// PIN DEL SENSOR LDR
#define LDR_PIN D6

// PIN DEL SENSOR DE AIRE
#define MQ135_PIN A0  

// PIN DEL VENTILADOR
#define FAN_PIN D7

// PIN DEL LED
#define LED_PIN D8  

// UMBRALES
#define MIN_DISTANCE 100
#define MAX_TEMPERATURE 30
#define MIN_CO2 400

// CICLOS
#define CYCLE_ONE 1
#define CYCLE_TWO 2
#define CYCLE_THREE 3

// TIEMPO DE TEMPORIZADOR
#define TIMER_LIMIT_LIGHT 3
#define TIMER_LIMIT_AIR   3
#define TIMER_LIMIT_FAN   3

// KEYS DE ALERTAS
#define INIT_ALERT "i"      // Inicializando
#define AIR_ALERT_1 "ad"    // Aire en condiciones deficientes
#define AIR_ALERT_2 "ao"    // Aire en condiciones optimas
#define LIGHT_ALERT_1 "l1"  // La luz esta encendida y la habitacion esta vacia
#define LIGHT_ALERT_2 "l2"  // Apagando la luz
#define TEMP_ALERT_1 "t1"   // La temperatura ha alcanzado niveles aceptables

#endif