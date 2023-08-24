import processing.serial.*;
import http.requests.*;

//Serial arduinoPort;
float temperature, humidity, airQuality, lightLevel;

void setup() {
  //arduinoPort = new Serial(this, "COM3", 9600);
  //arduinoPort.bufferUntil('\n');

  //saveSensorLevels(10, 20, 30, 40);
  getSensorLevels();
  
  size(400, 400); // Define el tamaño del lienzo
  background(200); // Establece el color de fondo en gris claro
}

void draw() {
  fill(255, 0, 0); // Relleno rojo
  ellipse(200, 200, 100, 100); // Dibuja una elipse en el centro del lienzo
}

//void serialEvent(Serial p) {
//  String data = arduinoPort.readString();
//  String[] dataPackage = splitTokens(data, "/\n\r");

//  // Temperature
//  if (dataPackage[0].equals("S1")) {
//    println("Temperatura: " + int(dataPackage[1]));
//    temperature = int(dataPackage[1]);
//  }

//  // Humidity
//  else if (dataPackage[0].equals("S2")) {
//    println("Humedad: " + int(dataPackage[1]));
//    humidity = int(dataPackage[1]);
//  }

//  // Air Quality
//  else if (dataPackage[0].equals("S3")) {
//    println("CO2: " + int(dataPackage[1]));
//    airQuality = int(dataPackage[1]);
//  }

//  // Light Level
//  else if (dataPackage[0].equals("S4")) {
//    println("Luz: " + int(dataPackage[1]));
//    lightLevel = int(dataPackage[1]);
//  }
//}

void saveSensorLevels(float t, float h, float a, float l) {
  // Crear un JSONArray con tus datos
  JSONArray data = new JSONArray();

  // TEMPERATURE
  JSONObject item1 = new JSONObject();
  item1.setInt("sensor_type", 1);
  item1.setFloat("value", t);
  data.append(item1);

  // HUMIDITY
  JSONObject item2 = new JSONObject();
  item2.setInt("sensor_type", 2);
  item2.setFloat("value", h);
  data.append(item2);

  // AIR QUALITY
  JSONObject item3 = new JSONObject();
  item3.setInt("sensor_type", 3);
  item3.setFloat("value", a);
  data.append(item3);

  // LIGHT LEVEL
  JSONObject item4 = new JSONObject();
  item4.setInt("sensor_type", 4);
  item4.setFloat("value", l);
  data.append(item4);

  // Crear la solicitud POST
  String url = "http://localhost:8000/sensors/create";
  PostRequest post = new PostRequest(url);
  post.addHeader("Content-Type", "application/json");

  println(data.toString());

  post.addData(data.toString());
  post.send();

  // Imprimir la respuesta en la consola
  println("Reponse Content: " + post.getContent());
  println("Reponse Content-Length Header: " + post.getHeader("Content-Length"));
}

void getSensorLevels(){
  String url = "http://localhost:8000/sensors/read";
  GetRequest get = new GetRequest(url);
  get.send();
  
  println("response: " + get.getContent());
  JSONArray response = parseJSONArray(get.getContent());
  println(response);
}
