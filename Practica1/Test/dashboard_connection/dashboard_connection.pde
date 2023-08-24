
import processing.serial.*;

String data;         // Variable para almacenar los datos recibidos

float temperatura;   // Variable para almacenar el valor de temperatura
float aire;          // Variable para almacenar el valor de aire
float luz;
float humedad;

Serial serial;  // Objeto Serial para comunicarse con Arduino


void setup() {
  size(400, 300);
  background(255);
  // Abre el puerto COM3 a una velocidad de 9600 baudios
  serial = new Serial(this, "COM4", 9600);
  serial.bufferUntil('\n'); // Espera hasta que se reciba un salto de línea
}

void draw() {
  // No necesitamos hacer nada en draw para este ejemplo
}

void serialEvent(Serial port) {
  data = port.readStringUntil('\n'); // Lee el string recibido hasta el salto de línea
  if (data != null) {
    println("Recibido: " + data);
    
    // Divide el string en palabras
    String[] words = split(data, ' ');
    if (words.length == 2) {
      if (words[0].equals("Temperatura")) {
        temperatura = float(words[1]); // Convierte el valor a float y guárdalo
        println("Temperatura: " + temperatura);
      } else if (words[0].equals("Aire")) {
        aire = float(words[1]); // Convierte el valor a float y guárdalo
        println("Aire: " + aire);
      } else if (words[0].equals("Luz")) {
        luz = float(words[1]); // Convierte el valor a float y guárdalo
        println("Luz: " + luz);
      } else if (words[0].equals("Humedad")) {
        humedad = float(words[1]); // Convierte el valor a float y guárdalo
        println("Humedad: " + humedad);
      }
    }
  }
}
