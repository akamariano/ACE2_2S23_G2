#include <Servo.h>

Servo miServo;  // Crea un objeto Servo
int condicion = 0; // Variable para la condición (0 o 1)

void setup() {
  miServo.attach(8);  // Conecta el servo al pin 6
  miServo.write(140);   // Inicializa el servo en 0 grados
}

void loop() {
  if (condicion == 1) { // Abrir
    // Mueve el servo de 130 a 0 grados
    for (int pos = 130; pos >= 0; pos -= 1) {
      miServo.write(pos);
      delay(15);  // Pequeño retardo para suavizar el movimiento
    }
    while (condicion == 1) {
      // Espera mientras la condición sea 0 para mantener el servo en 0 grados
    }
  }

  if (condicion == 0) { // Cerrar
    // Mueve el servo de 0 a 130 grados
    for (int pos = 0; pos <= 130; pos += 1) {
      miServo.write(pos);
      delay(15);  // Pequeño retardo para suavizar el movimiento
    }
    while (condicion == 0) {
      // Espera mientras la condición sea 1 para mantener el servo en 90 grados
    }
  }
}

