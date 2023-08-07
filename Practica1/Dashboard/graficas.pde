import org.gicentre.utils.stat.*; // Importa la librería gicentre para crear gráficos

public class Grafico extends PApplet { // Clase Grafico que extiende de PApplet
  
  // Crea variables para almacenar los gráficos de barras
  BarChart barChart1, barChart2, barChart3, barChart4;
 
  public void settings() { // Método para configurar la aplicación
    size(840, 810); // Establece el tamaño de la ventana
  }

  public void setup() { // Método para inicializar la aplicación
    background(221, 214, 204); // Establece el color de fondo
    
    // Inicializa y configura el primer gráfico de barras
    barChart1 = new BarChart(this);
    barChart1.setData(new float[] {0.76, 0.24, 0.39, 0.18, 0.20, 0.80});
    barChart1.setMinValue(0);
    barChart1.setMaxValue(1);
    textFont(createFont("Serif",20),20);
    barChart1.showValueAxis(true);
    barChart1.setValueFormat("#.##");
    barChart1.setBarColour(color(201,79,79,150));
    barChart1.setBarGap(2);
    barChart1.setBarLabels(new String[] {"Jeser","Kevin","Mariano",
                                       "Harry","Samuel", "Ale"});
    barChart1.showCategoryAxis(true);
    
    // Inicializa y configura el segundo gráfico de barras
    barChart2 = new BarChart(this);
    barChart2.setData(new float[] {0.76, 0.24, 0.39, 0.18, 0.20});
    barChart2.setMinValue(0);
    barChart2.setMaxValue(1);
    textFont(createFont("Serif",20),20);
    barChart2.showValueAxis(true);
    barChart2.setValueFormat("#%");
    barChart2.setBarColour(color(83,79,202,150));
    barChart2.setBarGap(4);
    barChart2.setBarLabels(new String[] {"Jeser","Kevin","Mariano",
                                       "Harry","Samuel"});
    barChart2.showCategoryAxis(true);
    
    // Inicializa y configura el tercer gráfico de barras
    barChart3 = new BarChart(this);
    barChart3.setData(new float[] {0.76, 0.24, 0.39, 0.18, 0.20});
    barChart3.setMinValue(0);
    barChart3.setMaxValue(1);
    textFont(createFont("Serif",20),20);
    barChart3.showValueAxis(true);
    barChart3.setValueFormat("#%");
    barChart3.setBarColour(color(81,81,84,150));
    barChart3.setBarGap(4);
    barChart3.setBarLabels(new String[] {"Jeser","Kevin","Mariano",
                                       "Harry","Samuel"});
    barChart3.showCategoryAxis(true);
    
    // Inicializa y configura el cuarto gráfico de barras
    barChart4 = new BarChart(this);
    barChart4.setData(new float[] {0.76, 0.24, 0.39, 0.18, 0.20});
    barChart4.setMinValue(0);
    barChart4.setMaxValue(1);
    textFont(createFont("Serif",20),20);
    barChart4.showValueAxis(true);
    barChart4.setValueFormat("#%");
    barChart4.setBarColour(color(183,180,75,150));
    barChart4.setBarGap(4);
    barChart4.setBarLabels(new String[] {"Jeser","Kevin","Mariano",
                                       "Harry","Samuel"});
    barChart4.showCategoryAxis(true);
  }
  
  public void draw(){ // Método para dibujar en la pantalla
    background(221, 214, 204); // Establece el color de fondo
    
    // Dibuja los cuatro gráficos de barras en la pantalla
    barChart1.draw(20, 80, 380, 300);
    
    pushStyle();
    fill(25, 34, 43);
    rect(50, 30, 310, 40, 15);
    printText("Temperatura", 30, 60, 60, 255, 255, 255);
    popStyle();
    
    barChart2.draw(420, 80, 380, 300);
    
    pushStyle();
    fill(25, 34, 43);
    rect(470, 30, 310, 40, 15);
    printText("Humedad", 30, 500, 60, 255, 255, 255);
    popStyle();
    
    barChart3.draw(20, 480, 380, 300);
    
    pushStyle();
    fill(25, 34, 43);
    rect(40, 420, 340, 40, 15);
    printText("Calidad de aire", 30, 50, 450, 255, 255, 255);
    popStyle();
    
    barChart4.draw(420, 480, 380, 300);
    
    pushStyle();
    fill(25, 34, 43);
    rect(470, 420, 310, 40, 15);
    printText("Iluminación", 30, 485, 450, 255, 255, 255);
    popStyle();
  }
  
  public void printText(String texto, int tam, int x, int y, int r, int g, int b) {
    textSize(tam);// TAMAÑO LETRA
    fill(r, g, b);// COLOR RGB DE LETRA
    font = createFont("Arial Bold", tam);
    textFont(font); // ESTABLECEMOS FUENTE EN NEGRITA
    text(texto, x, y);// TEXTO, POSX, POSY
  }
  
  public void exit() { // Método para salir de la aplicación
    dispose(); // Libera los recursos utilizados por la aplicación
  }
}
