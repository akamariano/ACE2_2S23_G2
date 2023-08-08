import org.gicentre.utils.stat.*;
import java.util.ArrayList;
import java.util.HashMap;

public class GraficoA extends PApplet { 

  // Crea variables para almacenar los gráficos de barras
  int sensor_type = 3;
  BarChart barChart1;
  
  public void settings() {
    size(1100, 810);
  }

  public void setup() {
    background(221, 214, 204);

    // Inicializa y configura el primer gráfico de barras
    barChart1 = new BarChart(this);
    
    // Settear valores de barChart
    barChart1 = barChartReadValues(barChart1, sensor_type); 
       
    textFont(createFont("Serif", 20), 20);
    barChart1.showValueAxis(true);
    barChart1.setValueFormat("#");
    barChart1.setBarColour(color(201, 79, 79, 150));
    barChart1.setBarGap(2);

    barChart1.showCategoryAxis(true);
    barChart1.transposeAxes(true);
  }

  public void draw() {
    background(221, 214, 204);

    // Dibuja los cuatro gráficos de barras en la pantalla
    barChart1.draw(60, 100, 900, 650);

    pushStyle();
    fill(25, 34, 43);
    rect(370, 30, 310, 40, 15);
    printText("Calidad de Aire", 30, 420, 60, 255, 255, 255);
    popStyle();
  }

  public void printText(String texto, int tam, int x, int y, int r, int g, int b) {
    textSize(tam);      // TAMAÑO LETRA
    fill(r, g, b);      // COLOR RGB DE LETRA
    font = createFont("Arial Bold", tam);
    textFont(font);     // FUENTE EN NEGRITA
    text(texto, x, y);  // TEXTO, POSX, POSY
  }

  // Método para salir de la aplicación
  public void exit() {
    dispose(); // Libera los recursos utilizados por la aplicación
  }
}
