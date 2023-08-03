void setup() {
  size(840, 900); // ancho X largo
  background(221, 214, 204); 
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
  printText("Análisis Meteorológico IOT", 50, 140, 100);// TEXTO, TAMAÑO LETRA, POSX, POY
  printText("Dashboard", 22, 360, 130);// TEXTO, TAMAÑO LETRA, POSX, POY
  
  //MOSAICOS-------------------------------------------->
  noStroke();// QUITA EL BORDE COLOR NEGRO DE LOS PANELES
  // TEMPERATURA
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 240, 320, 290);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  // LUZ
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 240, 320, 290);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  // HUMEDAD
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(70, 560, 320, 290);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
  // CONCENTRACION DE CO2
  fill(248, 246, 243);// COLOR DEL PANEL
  rect(450, 560, 320, 290);// POSICION DEL PANEL (X, Y, WIDTH, HEIGHT)
}

// FUNCIONES PARA EL LIENZO----------------------------------->
// TEXTO COLOR BLANCO
void printText(String texto, int tam, int x, int y){
  textSize(tam);// TAMAÑO LETRA
  fill(255, 255, 255);// COLOR RGB DE LETRA
  text(texto, x, y);// TEXTO, POSX, POSY
}
