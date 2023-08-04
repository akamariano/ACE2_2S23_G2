class humedad{
  
  float frequency, amplitude, yOffset, tonalidad_;
  
  public humedad(float tonalidad){
    frequency = 0.015;
    amplitude = 2;
    yOffset = 0;
    tonalidad_ = tonalidad;
  }
  
  // MOSAICO DE HUMEDAD -COLOR GOTA-
  private int[] tonalidadHumedad(){
    // Mapear la tonalidad a diferentes tonalidades de azul en el modelo RGB
    int r = int(map(tonalidad_, 0, 100, 255, 29)); // Componente rojo del color
    int g = int(map(tonalidad_, 0, 100, 255, 72)); // Componente verde del color
    int b = int(map(tonalidad_, 0, 100, 255, 234)); // Componente azul del color
    
    int[] valores = new int[3];
    valores[0] = r;
    valores[1] = g;
    valores[2] = b;
    return valores;
  }
  
  // MOSAICO DE HUMEDAD -NUBE-
  public void NubeDeHumedad(float x, float y, float size) {
    noStroke();
    fill(211, 226, 235);
  
    // Cuerpo de la nube (elipse principal)
    ellipse(x, y, size * 1.5, size);
  
    // Grumos (elipses más pequeñas)
    ellipse(x - size * 0.5, y, size * 0.8, size * 0.8);
    ellipse(x + size * 0.5, y, size * 0.8, size * 0.8);
    ellipse(x, y - size * 0.3, size * 0.8, size * 0.8);
  }
  
  // MOSAICO DE HUMEDAD -GOTA DE AGUA-
  public void GotaDeHumedad(float x1, float y1, float size) {
    int[] rgb = tonalidadHumedad();
    fill(135, 206, 235); // Color azul para la gota
    strokeWeight(1.9); // Redimensiona el grosor de los bordes
    stroke(135, 206, 235); // Borde azul
    
    // ELIPSE PARA CUERPO DE LA GOTA
    float x = x1 + 0.4;
    float y = y1 - 2.5;
    float diametro = size - 12.5;
    ellipse(x, y, diametro, size - 2);
  
    // TRIANGULO EN LA PARTE SUPERIOR DE LA GOTA
    fill(135, 206, 235);
    float triangleSize = size * 0.30; // Ajusta el tamaño del triángulo
    float triangleOffsetY = size * 0.23 + 7.7; // Ajusta esta variable para cambiar la posición vertical del triángulo
    triangle(x - triangleSize, y - size * 0.70 + triangleOffsetY, x + triangleSize+0.5, y - size * 0.75 + triangleOffsetY+2, x, y - size * 1.5 + triangleOffsetY);
  
    // POSICIONAMIENTO DE LA ONDA QUE SIMULA EL AGUA
    float Xonda = x1;
    float Yonda = y1-5;
    
    // ONDAS DENTRO DE LA ELIPSE QUE SIMULAN EL AGUA
    noFill();
    stroke(rgb[0], rgb[1], rgb[2]); // Color azul para el agua
    beginShape();
    for (int i = 0; i < yPositions.length; i++) {
      float angle = map(i, 0, yPositions.length - 1, 0, PI);
      x = cos(angle) * (diametro / 2) + Xonda;
      y = Yonda+ yPositions[i];
  
      // Limitar los extremos izquierdo y derecho a la elipse
      float maxY = Yonda + sqrt(sq(diametro / 2) * (1 - sq((x - Xonda) / (diametro / 2))));
      if (y > maxY) {
        y = maxY;
      }
  
      // Mantener las ondas dentro de la elipse
      if (dist(x, y, Xonda, Yonda) <= diametro / 2) {
        vertex(x, y);
      }
    }
    endShape();
  
    // REINICIO DE LAS ONDAS
    for (int i = 0; i < yPositions.length; i++) {
      yPositions[i] = sin(frequency * i + millis() * 0.01) * amplitude;
    }
    
    // RELLENO DEBAJO DE LAS ONDAS
    noStroke();
    fill(rgb[0], rgb[1], rgb[2]);
    beginShape();
    vertex(Xonda, Yonda + size / 2); // Vértice inferior
    for (int i = 0; i < yPositions.length; i++) {
      float angle = map(i, 0, yPositions.length - 1, 0, PI);
      x = cos(angle) * (diametro / 2) + Xonda;
      y = Yonda + yPositions[i];
  
      // Limitar los extremos izquierdo y derecho a la elipse
      float maxY = Yonda + sqrt(sq(diametro / 2) * (1 - sq((x - Xonda) / (diametro / 2))));
      if (y > maxY) {
        y = maxY;
      }
  
      // Mantener el relleno dentro de la elipse
      if (dist(x, y, Xonda, Yonda) <= diametro / 2) {
        vertex(x, y);
      }
    }
    vertex(Xonda, Yonda + size / 2); // Vértice inferior
    endShape(CLOSE);
  
    // RELLENOS EXTRAS PARA LA PARTE INFERIOR DE LA GOTA DE AGUA
    // GENERALIDADES DEL CIRCULO
    fill(rgb[0], rgb[1], rgb[2]); // Relleno de color azul claro
    noStroke(); // Sin borde
    float startAngle = 0; // Ángulo de inicio (0 grados)
    float endAngle = PI; // Ángulo de finalización (180 grados)
    
    // CIRCULO 1
    float radius = 20.8; // Radio del círculo
    float xc = 610;
    float yc = 336.6;
    // Dibujar la media esfera rotada 180 grados
    arc(xc, yc, radius * 2, radius * 2, startAngle, endAngle, PIE); // Dibujar el arco
    
    // CIRCULO 2
    float radius2 = 17.2; // Radio del círculo
    float xc2 = 610.5;
    float yc2 = 344.9;
    // Dibujar la media esfera rotada 180 grados
    arc(xc2, yc2, radius2 * 2, radius2 * 2, startAngle, endAngle, PIE); // Dibujar el arco
  }
}
