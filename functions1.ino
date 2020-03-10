void sendTemp() {

  String page = "<!DOCTYPE html>";
  page +="    <meta http-equiv='refresh' content='";
  page += String(refresh);// how often temperature is read
  page +="'/>";  
  page +="<html>";
  page +="<body>"; 
/// html body
  page +="<h1>MODULE ESP GPS</h1>";    
  page +="<p style=\"font-size:50px;\">Temperature:<br/>";  
  page +="<p style=\"color:red; font-size:50px;\">";
  page += String(tValue, 2);
  page +=" *C</p>";
  page +="<p style=\"font-size:50px;\">Humidity:<br/>";  
  page +="<p style=\"color:green; font-size:50px;\">";
  page += String(hValue, 2);
  page +=" %</p>";
/// html body
  page +="</p>";  
  page +="</body>";  
  page +="</html>";  
 server.send(200,  "text/html",page);

}

void handleNotFound() {
 
  String message = "File Not Found";
  message += "URI: ";
  message += server.uri();
  message += "Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "Arguments: ";
  message += server.args();
  message += "";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + ""; }
  server.send(404, "text/plain", message);

}
