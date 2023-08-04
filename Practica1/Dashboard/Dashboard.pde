termometro t = new termometro();
PFont font;
int colorNube = 0;
int colorCO2 = 255;
boolean subiendo = true;
boolean subiendo2 = true;

// HUMEDAD
float[] yPositions;
float frequency = 0.02;
float amplitude = 8;
float yOffset = 0; // Ajusta la posición vertical del relleno



void setup() {
  size(840, 810); // ancho X largo
  t.setSize(1.5);
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
  // TEMPERATURA
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 180, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  
  // Termometro para mosaico de temperatura
  t.show();
  t.setPosicion(230,365);
  t.setValor(map(mouseY, 0, height, 0, 100));
  printText("Temperatura °C", 25, 140, 440, 0, 0, 0);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  
  // LUZ
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 180, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  
  
  
  
  
  // HUMEDAD--------------------------------------------------------------------------------------------
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 500, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  drawCloud(610, 325, 140);
  
  
  
  drawWaterDrop(610, 340, 50);
  printText("Humedad", 25, 555, 440, 0, 0, 0);// TEXTO, TAMAÑO_LETRA, POSX, POY, RED, GREEN, BLUE
  noStroke();
  //-----------------------------------------------------------------------------------------------------
  
  
  
  
  
  
  // CONCENTRACION DE CO2
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 500, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  
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
  
}

// FUNCIONES PARA EL LIENZO----------------------------------->
// TEXTO COLOR BLANCO
void printText(String texto, int tam, int x, int y, int r, int g, int b){
  textSize(tam);// TAMAÑO LETRA
  fill(r, g, b);// COLOR RGB DE LETRA
  font = createFont("Arial Bold", tam);
  textFont(font); // ESTABLECEMOS FUENTE EN NEGRITA  
  text(texto, x, y);// TEXTO, POSX, POSY
}

void drawCloud(float x, float y, float size) {
  noStroke();
  fill(211, 226, 235);
  
  // Cuerpo de la nube (elipse principal)
  ellipse(x, y, size * 1.5, size);
  
  // Grumos (elipses más pequeñas)
  ellipse(x - size * 0.5, y, size * 0.8, size * 0.8);
  ellipse(x + size * 0.5, y, size * 0.8, size * 0.8);
  ellipse(x, y - size * 0.3, size * 0.8, size * 0.8);
}







void drawWaterDrop(float x1, float y1, float size) {
  //noStroke();
  //fill(135, 206, 235); // Color azul para la gota

  
  strokeWeight(1);
  noFill();
  stroke(135, 206, 235); // Borde negro
  float x = x1 + 0.4;
  float y = y1 - 2.5;
  float diametro = size - 13;
  ellipse(x, y, diametro, size - 2);
  
  
  
  
  
  
  // Dibujar las ondas de agua dentro de la elipse
  noFill();
  stroke(0, 100, 255); // Color azul para el agua
  beginShape();
  for (int i = 0; i < yPositions.length; i++) {
    float angle = map(i, 0, yPositions.length - 1, 0, PI);
    x = cos(angle) * (diametro / 2) + width / 2 + 0.4;
    y = height / 2 + yPositions[i];
    
    // Limitar los extremos izquierdo y derecho a la elipse
    float maxY = height / 2 + sqrt(sq(diametro / 2) * (1 - sq((x - width / 2 - 0.4) / (diametro / 2))));
    if (y > maxY) {
      y = maxY;
    }
    
    // Mantener las ondas dentro de la elipse
    if (dist(x, y, width / 2 + 0.4, height / 2 - 2.5) <= diametro / 2) {
      vertex(x, y);
    }
  }
  endShape();
  
 for (int i = 0; i < yPositions.length; i++) {
    yPositions[i] = sin(frequency * i + millis() * 0.01) * amplitude;
  }
  
  
  
  
  
  
  
  
  
  
  
  
  // Triángulo dentro de la gota (un poco más abajo y un poco más grande)
  /*fill(0, 0, 255);
  float triangleSize = size * 0.30; // Ajusta el tamaño del triángulo
  float triangleOffsetY = size * 0.23 + 7.7; // Ajusta esta variable para cambiar la posición vertical del triángulo
  triangle(x - triangleSize, y - size * 0.70 + triangleOffsetY, x + triangleSize, y - size * 0.75 + triangleOffsetY, x, y - size * 1.5 + triangleOffsetY);
  */
  //PRIMER VERTICE ES IZQUIERDA
  //
  //
}
