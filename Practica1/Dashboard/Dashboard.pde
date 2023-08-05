float altura = -33;
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

void setup() {
  size(840, 810); // ancho X largo
  //TEMPERATURA
  t.setSize(1.5);
  //HUMEDAD
  yPositions = new float[width];
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

  //TEXTO
  printText("Análisis Meteorológico IOT", 40, 155, 70, 255, 255, 255);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  printText("Dashboard", 22, 360, 100, 255, 255, 255);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE


  //MOSAICOS-------------------------------------------->
  noStroke();// QUITA EL BORDE COLOR NEGRO DE LOS PANELES

  // TEMPERATURA---------------------------------------------------------------------------------------
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 180, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)

  // Termometro para mosaico de temperatura
  t.show();
  t.setPosicion(230, 365);
  t.setValor(map(mouseY, 0, height, 0, 100));
  printText("Temperatura °C", 25, 140, 440, 0, 0, 0);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  // --------------------------------------------------------------------------------------------------


  // LUZ-----------------------------------------------------------------------------------------------
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 500, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)

  //CIRCULOS
  fill(250, 242, 55);
  circuloFoco(610, 590, 90);
  fill(153, 149, 149);
  circuloFoco(609.8, 668.2, 24);
  fill(248, 246, 243);
  rectanguloFoco(592.5, 662);
  fill(248, 246, 243);
  rectanguloFoco(592.5, 655);

  //TRAPECIO
  float posX_trapecio = 1220;
  float posY_trapecio = 635;
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
  rectanguloFoco(592.5, 651.3);
  rectanguloFoco(592.5, 658);
  rectanguloFoco(592.5, 665);

  printText("Iluminación", 25, 545, 740, 0, 0, 0);// TEXTO, TAMAÑO_LETRA, POSX, POY, RED, GREEN, BLUE
  // --------------------------------------------------------------------------------------------------


  // HUMEDAD-------------------------------------------------------------------------------------------
  noStroke();
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 180, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  h.NubeDeHumedad(610, 325, 140);
  h.GotaDeHumedad(610, 340, 50);
  printText("Humedad", 25, 555, 440, 0, 0, 0);// TEXTO, TAMAÑO_LETRA, POSX, POY, RED, GREEN, BLUE
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

  printText("Calidad de aire", 25, 135, 745, 0, 0, 0);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
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
