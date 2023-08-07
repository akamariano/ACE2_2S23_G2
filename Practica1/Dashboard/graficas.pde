import org.gicentre.utils.stat.*; 

public class Grafico extends PApplet {
  
  BarChart barChart;
 
  public void settings() {
    size(840, 810);
  }

  public void setup() {
    background(221, 214, 204);
    barChart = new BarChart(this);
    barChart.setData(new float[] {0.76, 0.24, 0.39, 0.18, 0.20});
     
    // Scaling
    barChart.setMinValue(0);
    barChart.setMaxValue(1);
   
    // Axis appearance
    textFont(createFont("Serif",20),20);
   
    barChart.showValueAxis(true);
    barChart.setValueFormat("#%");
    barChart.setBarLabels(new String[] {"Jeser","Kevin","Mariano",
                                       "Harry","Samuel"});
    barChart.showCategoryAxis(true);
  }
  
  public void draw(){
    background(255);
    barChart.draw(15,15,width/2,height/2); 
  }
  
  public void exit() {
    dispose();
  }
}
