
// Parametros:  barChart:    Un objeto del tipo BarChart al cual se le asignaran los valores leidos
//              sensor_type: Un entero que indique que tipo de sensor se leera
//                           (1) Temperatura
//                           (2) Humedad
//                           (3) CO2
//                            (4) Luz
// Descripción: Filtra los valores de los sensores según el tipo de sensor
//              y luego llama a otro método para settear los valores en el barChart
// Retorna:     barChart: BarChart con los valores setteados.
BarChart barChartReadValues(BarChart barChart, int sensor_type) {
  // Obtener los datos de la API
  JSONArray dataSensors = getSensorLevels();

  // ArrayList para obtener los valores y timestamps del tipo de sensor actual.
  ArrayList<Float> tempValues = new ArrayList<Float>();
  ArrayList<String> tempTimes = new ArrayList<String>();

  // Obtener los valores del sensor actual.
  for (int i = 0; i < dataSensors.size(); i++) {
    JSONObject element = dataSensors.getJSONObject(i);
    if (element.getInt("sensor_type") == sensor_type) {
      tempValues.add(element.getFloat("value"));
      tempTimes.add(element.getString("timestamp"));
    }
  }

  // Mostrar en consola los valores obtenidos.
  // printSensorValues(tempValues, tempTimes);

  // Convertir ArrayList a Array normal.
  float[] floatArray = floatListToArray(tempValues);
  String[] stringArray = stringListToArray(tempTimes);

  // Ordenar los valores a partir de la fecha más antigua a más actual.
  sortSensorValues(floatArray, stringArray);

  // Settear los valores en el barChart
  barChart.setData(floatArray);
  barChart.setBarLabels(stringArray);

  // Settear valor minimo en el barChart
  if ( (Math.round(arrayMaxValue(floatArray)) - 10) <= 0) {
    barChart.setMinValue(0);
  } else {
    int minValue = Math.round( arrayMinValue(floatArray) ) - 10;
    barChart.setMinValue( minValue );
  }

  // Settear valor máximo en el barChart
  barChart.setMaxValue( Math.round(arrayMaxValue(floatArray)) + 10 );

  // Retonar barChart.
  return barChart;
}

// Parametros:   listValues: Un ArrayList de Floats
// Descripción:  Convierte un ArrayList de Floats a un Array normal de floats
// Retorna:      floatArray: Array normal de floats.
float[] floatListToArray(ArrayList<Float> listValues) {
  float[] floatArray = new float[listValues.size()];
  for (int i = 0; i < listValues.size(); i++) {
    floatArray[i] = listValues.get(i);
  }
  return floatArray;
}

// Parametros:   listValues: Un ArrayList de Strings
// Descripción:  Convierte un ArrayList de Strings a un Array normal de Strings
// Retorna:      floatArray: Array normal de Strings.
String[] stringListToArray(ArrayList<String> listValues) {
  String[] stringArray = new String[listValues.size()];
  for (int i = 0; i < listValues.size(); i++) {
    stringArray[i] = listValues.get(i);
  }
  return stringArray;
}

// Parametros:   floatArray: Array de valores de las lecturas del sensor
//               stringArray: Array de timestamps de las lecturas del sensor
// Descripción:  Ordena los array de los datos del sensor según su timestamp
// Retorna:      Nada
void sortSensorValues(float[] floatArray, String[] stringArray) {
  if (stringArray.length <= 1) {
    return; // No es necesario ordenar un arreglo con 0 o 1 elementos.
  }

  // Implementar un algoritmo de ordenamiento
  for (int i = 0; i < stringArray.length - 1; i++) {
    for (int j = 0; j < stringArray.length - i - 1; j++) {
      if (stringArray[j].compareTo(stringArray[j + 1]) > 0) {
        // Intercambiar los elementos
        String temp1 = stringArray[j];
        stringArray[j] = stringArray[j + 1];
        stringArray[j + 1] = temp1;

        float temp2 = floatArray[j];
        floatArray[j] = floatArray[j + 1];
        floatArray[j + 1] = temp2;
      }
    }
  }
}

// Parametros:   values: Array de Floats
// Descripción:  obtiene el valor máximo de un array de floats.
// Retorna:      maxValue: valor máximo del array.
float arrayMaxValue(float[] values) {
  if (values.length == 0) {
    throw new IllegalArgumentException("El arreglo no puede estar vacío.");
  }

  float maxValue = values[0];

  for (int i = 1; i < values.length; i++) {
    if (values[i] > maxValue) {
      maxValue = values[i];
    }
  }

  return maxValue;
}

// Parametros:   values: Array de Floats
// Descripción:  obtiene el valor mínimo de un array de floats.
// Retorna:      maxValue: valor mínimo del array.
float arrayMinValue(float[] values) {
  if (values.length == 0) {
    throw new IllegalArgumentException("El arreglo no puede estar vacío.");
  }

  float minValue = values[0];

  for (int i = 1; i < values.length; i++) {
    if (values[i] < minValue) {
      minValue = values[i];
    }
  }

  return minValue;
}

// Parametros:   tempValues: Array de Floats con las lecturas del sensor
//               tempTimes: Array de Strings con las timestamps lecturas del sensor
// Descripción:  Imprime los datos de las lecturas del sensor.
// Retorna:      Nada.
void printSensorValues(ArrayList<Float> tempValues, ArrayList<String> tempTimes) {
  // Imprimir los elementos en la consola
  for (int i = 0; i < tempValues.size(); i++) {
    println("Valor: " + tempValues.get(i));
    println("Timestamp: " + tempTimes.get(i));
  }
}
