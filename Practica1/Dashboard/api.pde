import http.requests.*;


void saveSensorLevels(float t, float h, float a, float l) {
  // Crear un JSONArray con tus datos
  JSONArray data = new JSONArray();

  // TEMPERATURE
  JSONObject item1 = new JSONObject();
  item1.setInt("sensor_type", 1);
  item1.setFloat("value", t);
  data.append(item1);

  // HUMIDITY
  JSONObject item2 = new JSONObject();
  item2.setInt("sensor_type", 2);
  item2.setFloat("value", h);
  data.append(item2);

  // AIR QUALITY
  JSONObject item3 = new JSONObject();
  item3.setInt("sensor_type", 3);
  item3.setFloat("value", a);
  data.append(item3);

  // LIGHT LEVEL
  JSONObject item4 = new JSONObject();
  item4.setInt("sensor_type", 4);
  item4.setFloat("value", l);
  data.append(item4);

  // Crear la solicitud POST
  String url = "http://localhost:8000/sensors/create";
  PostRequest post = new PostRequest(url);
  post.addHeader("Content-Type", "application/json");

  println(data.toString());

  post.addData(data.toString());
  post.send();

  // Imprimir la respuesta en la consola
  println("Reponse Content: " + post.getContent());
  println("Reponse Content-Length Header: " + post.getHeader("Content-Length"));
}

JSONArray getSensorLevels() {
  String url = "http://localhost:8000/sensors/read";
  GetRequest get = new GetRequest(url);
  get.send();

  println("response: " + get.getContent());
  JSONArray response = parseJSONArray(get.getContent());
  println(response);
  return response;
}
