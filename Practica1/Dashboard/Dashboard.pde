termometro t = new termometro();
PFont font;

void setup() {
  size(840, 900); // ancho X largo
  //background(221, 214, 204); 
  t.setSize(1.5);
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
  rect(0, 0, 840, 187);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  
  //TEXTO
  printText("Análisis Meteorológico IOT", 50, 140, 100, 255, 255, 255);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  printText("Dashboard", 22, 360, 130, 255, 255, 255);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  
  //MOSAICOS-------------------------------------------->
  noStroke();// QUITA EL BORDE COLOR NEGRO DE LOS PANELES
  // TEMPERATURA
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 240, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  
  // Termometro para mosaico de temperatura
  t.show();
  t.setPosicion(230,440);
  t.setValor(map(mouseY, 0, height, 0, 100));
  printText("Temperatura °C", 25, 140, 510, 0, 0, 0);// TEXTO, TAMAÑO LETRA, POSX, POY, RED, GREEN, BLUE
  
  // LUZ
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 240, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  // HUMEDAD
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 560, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  // CONCENTRACION DE CO2
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 560, 320, 290, 25);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
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
