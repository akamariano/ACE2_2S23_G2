#include <Servo.h>

Servo myServo;  // Crea un objeto Servo
int close = 0;
int pos = 0;  // Variable para almacenar la posición actual del servo
boolean movido = false;  // Bandera para controlar si ya se ha movido

void setup() {
  myServo.attach(8);  // Conecta el servo al pin 8
  myServo.write(0);   // Inicializa el servo en 0 grados
}

void loop() {
  if (close == 0 && !movido) {
    // Mueve el servo de 0 a 90 grados
    for (pos = 0; pos <= 90; pos += 1) {
      myServo.write(pos);
      delay(15);  // Pequeño retardo para suavizar el movimiento
    }
    movido = true;  // Establece la bandera en verdadero para indicar que ya se movió
  } else if (close == 1 && !movido) {
    // Mueve el servo de 90 a 0 grados
    for (pos = 90; pos >= 0; pos -= 1) {
      myServo.write(pos);
      delay(15);  // Pequeño retardo para suavizar el movimiento
    }
    movido = true;  // Establece la bandera en verdadero para indicar que ya se movió
  }
}

