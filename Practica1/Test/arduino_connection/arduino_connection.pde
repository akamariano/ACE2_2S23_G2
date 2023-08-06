import processing.serial.*;

Serial arduinoPort;
float temperature, humidity, airQuality, lightLevel;

void setup() {
  arduinoPort = new Serial(this, "COM3", 9600);
  arduinoPort.bufferUntil('\n');
  
  size(400, 400); // Define el tamaño del lienzo
  background(200); // Establece el color de fondo en gris claro
}

void draw() {
  fill(255, 0, 0); // Relleno rojo
  ellipse(200, 200, 100, 100); // Dibuja una elipse en el centro del lienzo
}

void serialEvent(Serial p){
  String data = arduinoPort.readString();
  String[] dataPackage = splitTokens(data, "/\n\r");
  
  // Temperature
  if (dataPackage[0].equals("S1")){
    println("Temperatura: " + int(dataPackage[1]));
    temperature = int(dataPackage[1]);
  }
  
  // Humidity
  else if (dataPackage[0].equals("S2")){
    println("Humedad: " + int(dataPackage[1]));
    humidity = int(dataPackage[1]);
  }
  
  // Air Quality
  else if (dataPackage[0].equals("S3")){
    println("CO2: " + int(dataPackage[1]));
    airQuality = int(dataPackage[1]);
  }
  
  // Light Level
  else if (dataPackage[0].equals("S4")){
    println("Luz: " + int(dataPackage[1]));
    lightLevel = int(dataPackage[1]);
  }
}
