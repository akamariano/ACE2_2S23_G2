class termometro {
  float posx, posy, diam, size, valor, min, max, valor2, dv;
  color relleno;
  
  // Metodo constructor para clase termometro
  public termometro(){
    posx = 100;
    posy = 100;
    diam = 50;
    size = 1;
    valor = 50;
    min = 0;
    max = 100;
    dv = 1; 
    valor2 = 0;
    relleno = #C94F4F;
  }
  
  // Set de la posicion
  public void setPosicion(float x, float y){
    posx = x;
    posy = y;
  }
  
  // Set del tamaño
  public void setSize(float size){
    this.size = size;
    diam = diam * size;
  }
  
  public void setValor(float valor){
    this.valor = valor;
  }
  
  public void show(){
    dv = valor-valor2;
    valor2 += dv * 0.7;
    pushStyle();
    noStroke();
    fill(50);
    ellipse(posx, posy, diam, diam);
    stroke(50);
    strokeWeight(diam*0.4);
    line(posx, posy, posx, posy-diam*2);
    stroke(25);
    strokeWeight(diam*0.2);
    line(posx, posy, posx, posy-diam*2);
    fill(relleno);
    noStroke();
    ellipse(posx, posy, diam*0.7, diam *0.7);
    stroke(relleno);
    strokeWeight(diam*0.2);
    line(posx, posy, posx, map(valor2,min, max, posy-(diam/2)*0.7, posy-diam*2));
    popStyle();
  }
  
}
