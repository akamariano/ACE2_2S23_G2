// Serialización
import processing.serial.*;

// <-------------- VARIABLES GLOBALES ----------------->
Serial serial;  // Objeto Serial para comunicarse con Arduino

// DATOS
static String data;         // Variable para almacenar los datos recibidos

float luz; // Valor de la luz
float temperatura; // Valor de la temperatura
float humedad; // Valor de la humedad
float aire;  // Valor de la calidad del aire

// ILUMINACION
float altura = -33;
float lineHeight = 10;
float maxHeight = 24;
float minHeight = 10;
float growthSpeed = 0.5;
float currentHeight = minHeight;
boolean growing = true;
float tonalidad_ = 90;

// TEMPERATURA------------------->
termometro t = new termometro();
PFont font;

// CO2--------------------------->
int colorNube = 0;
int colorCO2 = 255;
boolean subiendo = true;
boolean subiendo2 = true;

// HUMEDAD----------------------->
humedad h = new humedad(50);
float[] yPositions;

// MENU Y BOTONES
int weightButton = 100;
int heightButton = 30;
// <--------------------------------------------------->

void setup() {
  size(840, 810); // ancho X largo
  //TEMPERATURA
  t.setSize(1.5);
  //HUMEDAD
  yPositions = new float[width];
  
  // Abre el puerto COM3 a una velocidad de 9600 baudios
  serial = new Serial(this, "COM2", 9600);
  serial.bufferUntil('\n'); // Espera hasta que se reciba un salto de línea
}

// PALETA DE COLORES
// https://htmlcolorcodes.com/es/
// negro     -> 19222B  ->  RGB(25, 34, 43)
// amarillo  -> BD9240  ->  RGB(189, 146, 64)
// rojo      -> B84357  ->  RGB(184, 67, 87)
// blanco    -> DDD6CC  ->  RGB(221, 214, 204)

void draw() {
  // REINICIO DE PINTADO
  background(221, 214, 204);

  //PANEL SUPERIOR
  fill(184, 67, 87);// COLOR DEL PANEL EN RGB
  rect(0, 0, 840, 155);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  
  // MENU
  fill(25, 34, 43);
  stroke(255);
  strokeWeight(0.2);
  rect(0, 0, 840, 30, 5);
    
  // BOTON
  if (mouseOver()){
    fill(235, 201, 133);
  } else {
    fill(189, 146, 64); 
  }
  rect(0, 0, weightButton, heightButton, 5);
  printText("Gráficas", 20, 10, 22, 0, 0, 0);
   
  //TEXTO
  printText("Análisis Meteorológico IOT", 40, 155, 90, 255, 255, 255);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  printText("Dashboard", 22, 360, 120, 255, 255, 255);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE

  //MOSAICOS-------------------------------------------->
  noStroke();// QUITA EL BORDE COLOR NEGRO DE LOS PANELES

  // TEMPERATURA---------------------------------------------------------------------------------------
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 180, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)

  // Termometro para mosaico de temperatura
  t.show();
  t.setPosicion(230, 365);
  t.setValor(map(mouseY, 0, height, 0, 100));
  printText("Temperatura "+temperatura+"°C", 25, 114, 440, 0, 0, 0);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  // --------------------------------------------------------------------------------------------------


  // LUZ-----------------------------------------------------------------------------------------------
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 500, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT
  int r = int(map(tonalidad_, 0, 100, 251, 255)); // Componente rojo del color
  int g = int(map(tonalidad_, 0, 100, 248, 205)); // Componente verde del color
  int b = int(map(tonalidad_, 0, 100, 237, 0)); // Componente azul del color
  
  //RAYOS DE LUZ
  animacionLuz();
  float startX = 558; // Coordenada x inicial
  float startY = 540; // Coordenada y inicial
  stroke(r, g, b);
  strokeWeight(4.2);
  // Dibuja la línea inclinada
  float x1_luz = startX - lineHeight / 2;
  float y1_luz = startY - currentHeight / 2;
  float x2_luz = startX + lineHeight / 2;
  float y2_luz = startY + currentHeight / 2;
  line(x1_luz+5, y1_luz+3, x2_luz+6, y2_luz+3);
  line(x1_luz+51, y1_luz-9, x2_luz+42.5, y2_luz-9);
  line(x1_luz+100, y1_luz, x2_luz+86, y2_luz);
  noStroke();

  //CIRCULOS
  fill(r, g, b);
  stroke(202, 197, 197);
  strokeWeight(1);
  circuloFoco(610, 600, 90);
  fill(153, 149, 149);
  circuloFoco(609.8, 678.2, 24);
  fill(248, 246, 243);
  rectanguloFoco(592.5, 672);
  fill(248, 246, 243);
  rectanguloFoco(592.5, 665);

  //TRAPECIO
  float posX_trapecio = 1220;
  float posY_trapecio = 645;
  fill(222, 219, 219);
  float topWidth = 35;
  float bottomWidth = 70;
  float x1 = (posX_trapecio - bottomWidth)/2;
  float x2 = x1 + bottomWidth;
  float x3 = (posX_trapecio - topWidth)/2;
  float x4 = x3 + topWidth;
  float y1 = posY_trapecio - altura / 2;
  float y2 = posY_trapecio  + altura / 2;
  // Dibuja el trapecio
  beginShape();
  vertex(x1, y2);
  vertex(x2, y2);
  vertex(x4, y1);
  vertex(x3, y1);
  endShape(CLOSE);

  //RECTANGULOS
  fill(187, 184, 184);
  rectanguloFoco(592.5, 661.3);
  rectanguloFoco(592.5, 668);
  rectanguloFoco(592.5, 675);

  printText("Iluminación "+luz + " Lm", 25, 485, 740, 0, 0, 0);// TEXTO, TAMAÑO_LETRA, POSX, POY, RED, GREEN, BLUE
  // --------------------------------------------------------------------------------------------------

  // HUMEDAD-------------------------------------------------------------------------------------------
  noStroke();
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 180, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  h.NubeDeHumedad(610, 325, 140);
  h.GotaDeHumedad(610, 340, 50);
  printText("Humedad "+humedad + "%", 25, 515, 440, 0, 0, 0);// TEXTO, TAMAÑO_LETRA, POSX, POY, RED, GREEN, BLUE
  noStroke();
  //----------------------------------------------------------------------------------------------------


  // CONCENTRACION DE CO2-------------------------------------------------------------------------------
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 500, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)

  // Nube para mosaico de CO2
  fill(colorNube);
  ellipse(185, 640, 130, 100);
  ellipse(225, 600, 130, 110);
  ellipse(265, 640, 130, 100); // ELLIPSE(POSX, POSY, RADIOX, RADIOY)

  if (subiendo) colorNube++; // SI SUBIENDO ES VERDADERO, INCREMENTAMOS EN UNO
  else colorNube--; // SI ES FALSO, DECREMENTAMOS
  if (colorNube == 100) subiendo = false; // SI EL COLOR ES IGUAL A 180, SUBIENDO ES FALSE
  if (colorNube == 0) subiendo = true; // SI EL COLOR ES IGUAL A 0, SUBIENDO ES TRUE

  stroke(colorNube);
  strokeWeight(15);
  line(178, 682, 260, 682); // LINE(X1, Y1, X2, Y2)
  noStroke();

  printText("CO²", 35, 195, 640, colorCO2, colorCO2, colorCO2);

  if (subiendo2) colorCO2--;
  else colorCO2++;
  if (colorCO2 == 150) subiendo2 = false; // SI EL COLOR ES IGUAL A 180, SUBIENDO ES FALSE
  if (colorCO2 == 255) subiendo2 = true; // SI EL COLOR ES IGUAL A 0, SUBIENDO ES TRUE

  printText("Aire "+aire + " ppm", 25, 135, 745, 0, 0, 0);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  //----------------------------------------------------------------------------------------------------
}

// FUNCIONES PARA EL LIENZO----------------------------------->

void printText(String texto, int tam, int x, int y, int r, int g, int b) {
  textSize(tam);// TAMAÑO LETRA
  fill(r, g, b);// COLOR RGB DE LETRA
  font = createFont("Arial Bold", tam);
  textFont(font); // ESTABLECEMOS FUENTE EN NEGRITA
  text(texto, x, y);// TEXTO, POSX, POSY
}

void rectanguloFoco(float x, float y) {
  float widthR = 34.8;
  float heightR = 6.5;
  float cornerRadius = 12;  // Modifica este valor para cambiar el radio de los bordes

  // Dibuja el rectángulo con bordes redondeados
  rect(x, y, widthR, heightR, cornerRadius);
}

void circuloFoco(float x, float y, float diameter) {
  ellipse(x, y, diameter, diameter);
}

void animacionLuz(){
  // Actualiza la altura de la línea
  if (growing) {
    currentHeight += growthSpeed;
    if (currentHeight >= maxHeight) {
      growing = false;
    }
  } else {
    currentHeight -= growthSpeed;
    if (currentHeight <= minHeight) {
      growing = true;
    }
  }
}

// FUNCION BOOLEANA QUE VERIFICA SI EL CURSOR ESTA DENTRO DEL BOTON
boolean mouseOver(){
  if (mouseX > 0 && mouseX < 0 + weightButton && mouseY > 0 && mouseY < 0 + heightButton){
    return true;
  } else {
    return false;
  }
}

// VERIFICA SI SE HA PRESIONADO EL BOTON
void mousePressed() {
  if (mouseOver()) {
    String[] args = {"Ventana Graficos"};
    Grafico sa = new Grafico();
    PApplet.runSketch(args, sa);
  }
}

// Obtener los datos del Arduino
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
