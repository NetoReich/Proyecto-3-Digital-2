//Programación ESP32

#include <WiFi.h> //Librería para manejar el Wifi
#include <WiFiClient.h> //Librería para manejar Clientes
#include <WebServer.h> //Librería para manejar el servidor
#include <ESPmDNS.h> //Librería para asegurarse que la IP no cambie
#include <LiquidCrystal.h> //Librería para la pantalla LCD

//Definicion de pines de la pantalla 16x2 (4 bits)
#define RS 25
#define EN 26
#define D4 27
#define D5 14
#define D6 19
#define D7 18

const char* ssid = "Marce"; //Nombre de la red
const char* password = "marcelapad"; //Contraseña
char tiva1; //Variable para recibir del serial de la tiva 1
char tiva2; //Variable para recibir del serial de la tiva 2

WebServer server(80); //Definimos objeto para la librería Webserver en el puerto 80 ya con ese hace el request de http
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Definimos el objeto para la librería LCD y asignamos los pines

//Variables booleanas para los parqueos
bool parqueo1 = false;
bool parqueo2 = false;
bool parqueo3 = false;
bool parqueo4 = false;
bool parqueo5 = false;
bool parqueo6 = false;
bool parqueo7 = false;
bool parqueo8 = false;

//Variables enteras para los totales de los parqueos
uint8_t s1;
uint8_t s2;
uint8_t s3;
uint8_t s4;
uint8_t s5;
uint8_t s6;
uint8_t s7;
uint8_t s8;
uint8_t sotano1;
uint8_t sotano2;
uint8_t disponibles;

//Función para que cuando se este en la pagina principal se ejecute la siguiente función
void handleRoot() {
  server.send(200, "text/html", HTML()); //Código de la página web
}

//Función que llama javascript para que cuando se este en la pagina principal se ejecute la siguiente función
void handleColor1(){
  if (parqueo1 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta vacío enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor2(){
  if (parqueo2 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor3(){
  if (parqueo3 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor4(){
  if (parqueo4 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor5(){
  if (parqueo5 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor6(){
  if (parqueo6 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor7(){
  if (parqueo7 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor8(){
  if (parqueo8 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

//Funcion a llamar si el cliente escribe una direccion que no existe
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200); //Iniciar comunicación serial para ver en la terminal
  Serial1.begin(115200, SERIAL_8N1, 32, 33, false, 20000UL, 112); //Habilitar el UART1 y cambiar los pins
  Serial2.begin(115200); //Habilitar el UART2
  lcd.begin(16, 2); //Setup de la LCD de 16x2
  lcd.setCursor(0,0); //Cursor en 0,0
  lcd.print("Parqueomatic"); //Escribir parqueomatic
  lcd.setCursor(12,0); //Cursor 12,0
  lcd.print("P:"); //Escribir p de parqueos totales
  lcd.setCursor(0,1); //Cursor en 0,1
  lcd.print("S1:"); //Escribir S1
  lcd.setCursor(8,1); //Cursor 8,1
  lcd.print("S2:"); //Escribir S2
  WiFi.mode(WIFI_STA); //Wifi como station mode para unirse a una red que ya existe
  WiFi.begin(ssid, password); //Iniciar la conexión 
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //Escribir la IP para acceder a la página

  //Iniciar multi DNS
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  //Definir las funciones a llamar cuando se haga el request de ciertas direcciones
  server.on("/", handleRoot);
  server.on("/l1", handleColor1);
  server.on("/l2", handleColor2);
  server.on("/l3", handleColor3);
  server.on("/l4", handleColor4);
  server.on("/l5", handleColor5);
  server.on("/l6", handleColor6);
  server.on("/l7", handleColor7);
  server.on("/l8", handleColor8);

  server.onNotFound(handleNotFound); //Cuando se pida una direccion inexistente llamar a la funcion indicada

  server.begin(); //Iniciar el servidor
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient(); //Mantener el servidor 
  check_tiva1(); //Llamar a función para revisar los parqueos de la tiva 1
  check_tiva2(); //Llamar a función para revisar los parqueos de la tiva 2
  check(); //Llamar para poder realizar suma de los parqueos
  sotano1 = s1 + s2 + s3 + s4; //Suma de parqueos en sotano 1
  sotano2 = s5 + s6 + s7 + s8; //Suma de parqueos en sotano 2
  disponibles = s1 + s2 + s3 + s4 + s5 + s6 + s7 +s8; //Suma de disponibles totales
  lcd.setCursor(13, 0); //Cursor en 13,0
  lcd.print(String(disponibles)); //Mostrar parqueos totales dispnibles
  lcd.setCursor(3,1); //Cursor en 3,1
  lcd.print(String(sotano1)); //Mostrar los parqueos dispnibles en el sotano 1
  lcd.setCursor(12,1); //Cursor en 12,1
  lcd.print(String(sotano2)); //Mostrar los parqueos disponibles en el sotano 2
}

//Código HTML, CSS y Javascript para la página WEB
String HTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr +="<title>PARQUEOMATIC</title>\n";
  ptr +="  <style>\n";
  ptr +="    /* CSS Styling */\n";
  ptr +="    body {\n";
  ptr +="      font-family: Arial, sans-serif;\n";
  ptr +="      background-color:  #857d6a;\n"; 
  ptr +="      color: #333;\n";
  ptr +="      margin: 0;\n";
  ptr +="      padding: 20px;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    h1 {\n";
  ptr +="      text-align: center;\n";
  ptr +="    }\n";
  ptr +="\n";

  ptr +="    color1 {\n";
  ptr +="      background-color: #81d8d0;\n";
  ptr +="    }\n";
  ptr +="\n";

  ptr +="    color2 {\n";
  ptr +="      background-color:  #fdf5e6;\n";
  ptr +="    }\n";
  ptr +="\n";
  
  ptr +="    .parking-lot {\n";
//  ptr +="      background-color: #81d8d0;\n";
  ptr +="      display: flex;\n";
  ptr +="      justify-content: center;\n";
  ptr +="      flex-wrap: wrap;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .parking-lot2{\n";
 // ptr +="      background-color:  #fdf5e6;\n";
  ptr +="      display: flex;\n";
  ptr +="      justify-content: center;\n";
  ptr +="      flex-wrap: wrap;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .parking-spot {\n";
  ptr +="      width: 200px;\n";  // CAMBIAR TAMAño
  ptr +="      height: 80px;\n";
  ptr +="      border-radius: 5px;\n";
  ptr +="      margin: 10px;\n";
  ptr +="      display: flex;\n";
  ptr +="      align-items: center;\n"; //  texto
  ptr +="      justify-content: flex-end;\n";
  ptr +="      font-size: 24px;\n";
  ptr +="      font-weight: bold;\n";
  ptr +="      cursor: pointer;\n";
  ptr +="      justify-content: flex-end;\n";

  ptr +="      transition: background-color 0.3s ease;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .vacant {\n";
  ptr +="      background-color: #34c759;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .occupied {\n";
  ptr +="      background-color: #ff3b30;\n";
  ptr +="    }\n";
  ptr +="  </style>\n";
  ptr +="</head>\n";
  ptr +="<body onload=\"process()\">\n";
  ptr +="  <h1>PARQUEOMATIC &#x263A </h1>\n";
  ptr +="\n";
  ptr +="  <h1>CIT 💸 </h1>\n";
  ptr +="  <div class=\"parking-lot\">\n"; 
  ptr +="  <color1>\n"; 
  ptr +="<div id=\"spot1\" class=\"parking-spot\">стоянка 1 &#128652;</div>\n"; 
  ptr +="<div id=\"spot2\" class=\"parking-spot\">стоянка 2 &#128652;</div>\n"; 
  ptr +="<div id=\"spot3\" class=\"parking-spot\">стоянка 3 &#128652;</div>\n"; 
  ptr +="<div id=\"spot4\" class=\"parking-spot\">стоянка 4 &#128652;</div>\n";
  ptr +="  </color1>\n"; 
  ptr +="  </div>\n";
  ptr +="  <h1>HOYO <a href='https://emojitool.com/mountain'>⛰</a> </h1>\n";
  ptr +="  <div class=\"parking-lot2\">\n";
  ptr +="  <color2>\n"; 
  ptr +="<div id=\"spot5\" class=\"parking-spot\">стоянка 5 &#128652;</div>\n";
  ptr +="<div id=\"spot6\" class=\"parking-spot\">стоянка 6 &#128652;</div>\n";
  ptr +="<div id=\"spot7\" class=\"parking-spot\">стоянка 7 &#128652;</div>\n";
  ptr +="<div id=\"spot8\" class=\"parking-spot\">стоянка 8 &#128652;</div>\n";
  ptr +="  </color2>\n"; 
  ptr +="  </div>\n";
  ptr +="\n";
  ptr +="<script>\n";
  ptr +="function updateColor1() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot1').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l1', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor1, 500);}\n";

  ptr +="function updateColor2() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot2').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l2', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor2, 500);}\n";

  ptr +="function updateColor3() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot3').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l3', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor3, 500);}\n";

  ptr +="function updateColor4() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot4').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l4', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor4, 500);}\n";

  ptr +="function updateColor5() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot5').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l5', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor5, 500);}\n";

  ptr +="function updateColor6() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot6').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l6', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor6, 500);}\n";

  ptr +="function updateColor7() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot7').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l7', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor7, 500);}\n";

  ptr +="function updateColor8() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot8').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l8', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor8, 500);}\n";

  ptr +="updateColor1();\n";
  ptr +="updateColor2();\n";
  ptr +="updateColor3();\n";
  ptr +="updateColor4();\n";
  ptr +="updateColor5();\n";
  ptr +="updateColor6();\n";
  ptr +="updateColor7();\n";
  ptr +="updateColor8();\n";
  ptr +="</script>\n";
  
  ptr +="</body>\n";
  ptr +="</html>";
  return ptr;
}

//Función para chequear la información de la Tiva1
void check_tiva1(){
  tiva1 = Serial2.read(); //Leer de UART2

  //Chequear para los parqueos
  if (tiva1 == 0){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 1){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 2){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 3){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 4){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 5){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 6){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 7){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 8){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 9){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 10){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 11){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 12){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = true;
  }
  else if (tiva1 == 13){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = true;
  }
  else if (tiva1 == 14){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = true;
  }
  else if (tiva1 == 15){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = true;
  }
}

void check_tiva2(){
  tiva2 = Serial1.read(); //Leer del UART1

  //Chequear para los parqueos
  if (tiva2 == 0){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 1){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 2){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 3){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 4){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 5){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 6){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 7){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 8){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 9){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 10){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 11){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 12){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = true;
  }
  else if (tiva2 == 13){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = true;
  }
  else if (tiva2 == 14){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = true;
  }
  else if (tiva2 == 15){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = true;
  }
}

//Función para las sumas
void check(){
  //Revisar si están ocupados los parqueos
  if (parqueo1 == true){
    s1 = 1;
  }
  else{
    s1 = 0;
  }
  if (parqueo2 == true){
    s2 = 1;
  }
  else{
    s2 = 0;
  }
  if (parqueo3 == true){
    s3 = 1;
  }
  else{
    s3 = 0;
  }
  if (parqueo4 == true){
    s4 = 1;
  }
  else{
    s4 = 0;
  }
  if (parqueo5 == true){
    s5 = 1;
  }
  else{
    s5 = 0;
  }
  if (parqueo6 == true){
    s6 = 1;
  }
  else{
    s6 = 0;
  }
  if (parqueo7 == true){
    s7 = 1;
  }
  else{
    s7 = 0;
  }
  if (parqueo8 == true){
    s8 = 1;
  }
  else{
    s8 = 0;
  }
