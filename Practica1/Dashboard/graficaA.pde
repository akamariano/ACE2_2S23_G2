import org.gicentre.utils.stat.*; // Importa la librería gicentre para crear gráficos
import java.util.ArrayList;
import java.util.HashMap;

public class GraficoA extends PApplet { // Clase Grafico que extiende de PApplet

  // Crea variables para almacenar los gráficos de barras
  BarChart barChart1;
  
  public void settings() { // Método para configurar la aplicación
    size(1100, 810); // Establece el tamaño de la ventana
  }

/* --------------------------------------->>>> DESCOMENTAR ESTO PARA RECIBIR DATOS DE LA DATABASE ------------------------>>>
  public void getValues() {
    
    // Obtener los datos de la API
    JSONArray dataSensors = getSensorLevels();

    // ArrayList para obtener los valores y timestamps de cada sensor (Sensor por sensor)
    ArrayList<Float> tempValues = new ArrayList<Float>();
    ArrayList<String> tempTimes = new ArrayList<String>();

    // Obtener los valores del SENSOR 1 (TEMPERATURA)
    for (int i = 0; i < dataSensors.size(); i++) {
      JSONObject element = dataSensors.getJSONObject(i);
      if (element.getInt("sensor_type") == 1) {
        tempValues.add(element.getFloat("value"));
        tempTimes.add(element.getString("timestamp"));
      }
    }

    // Settear valores en barChart 1
    setValues(tempValues, tempTimes);
  }

  public void setValues(ArrayList<Float> tempValues, ArrayList<String> tempTimes) {
    // Imprimir los elementos en la consola
    for (int i = 0; i < tempValues.size(); i++) {
      println("Valor: " + tempValues.get(i));
      println("Timestamp: " + tempTimes.get(i));
    }
    
    // Crear un array normal de floats y de Strings y copiar los datos
    float[] arrayDeFloats = new float[tempValues.size()];
    String[] arrayDeStrings = new String[tempTimes.size()];
    for (int i = 0; i < tempValues.size(); i++) {
      arrayDeFloats[i] = tempValues.get(i);
      arrayDeStrings[i] = tempTimes.get(i);
    }
    
    printArray(arrayDeFloats);
    
    // Settear los datos en el barChart
    barChart1.setData(arrayDeFloats);
    barChart1.setBarLabels(arrayDeStrings);
  }
  <<<----------------------------------------------------------------------------------------------->>>>*/

  public void setup() { // Método para inicializar la aplicación
    background(221, 214, 204); // Establece el color de fondo

    // Inicializa y configura el primer gráfico de barras
    barChart1 = new BarChart(this);
        
    // getValues(); ---------------------------------------------------------------------------------> Quitar comentario para colocar datos de la dataBase
    barChart1.setData(new float[] {10, 25, 25, 5, 45, 50});                             //// -----------------> Eliminar esta linea
    barChart1.setBarLabels(new String[] {"10-12-2023-10-41","11-12-2023-10-41","12-12-2023-10-41",
                                       "13-12-2023-10-41","14-12-2023-10-41", "15-12-2023-10-41"});  //// -----------------> Eliminar estas lineas tambien
    barChart1.setMinValue(0);
    barChart1.setMaxValue(30);
    textFont(createFont("Serif", 20), 20);
    barChart1.showValueAxis(true);
    barChart1.setValueFormat("#");
    barChart1.setBarColour(color(201, 79, 79, 150));
    barChart1.setBarGap(2);

    barChart1.showCategoryAxis(true);
    barChart1.transposeAxes(true);
  }

  public void draw() { // Método para dibujar en la pantalla
    background(221, 214, 204); // Establece el color de fondo

    // Dibuja los cuatro gráficos de barras en la pantalla
    barChart1.draw(60, 100, 900, 650);

    pushStyle();
    fill(25, 34, 43);
    rect(370, 30, 310, 40, 15);
    printText("Calidad de Aire", 30, 420, 60, 255, 255, 255);
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
