

#include <SPI.h>
#include <WiFiNINA.h>

const char index_html[] PROGMEM={"<!DOCTYPE html>\n<html>\n<head>\n<meta charset =\"UTF-8\">\n<meta name =\"description\" content=\"website\">\n<title> Matthew's Website </title>\n</head>\n<body> \nHello World\n</body>\n</html>"};

char ssid[] = "001601A1E61F";      // your network SSID (name) 
char pass[] = "jefferyfam";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

/*void handleRoot(){
  server.send_P(200, "text/html", index_html);  
}*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int score = 0;
int gameSetup = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  //server.on("/", handleRoot);
  //server.println(index_html);
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
  pinMode(pushButton, INPUT);
}


void loop() {
  int buttonState = digitalRead(pushButton);
 // Serial.println(buttonState);
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
         client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<style>");
          client.println("#div1 {position:absolute;right: 0px;top: 200px;width:200px;height:200px;border:1px solid #000; background-color:red;animation: moveL 5s 1;}");
          client.println("#player1 {position:absolute;right: 750px;top: 200px;width:150px;height:150px;border:1px solid #000; background-color:blue;}");
          client.println("#player2 {position:absolute;right: 750px;top: 200px;width:150px;height:150px;border:1px solid #000; background-color:blue;animation: moveUp 5s 1;}");
          client.println("@keyframes moveL {100% {right:1300px;} }");
          client.println("@keyframes moveUp {50% {top:0px;} }");
          client.println("</style>");
         // if (score == 0 && gameSetup == 0 ){
            
         // }
          client.println("<body>");
          client.println("<div id =\"div1\">");
          client.println("</div>");
           
          if(buttonState == 1) {
            client.println("<div id=\"player2\">");
            client.println("</div>");
            score = score +1; 
          }
          else {
            client.println("<div id=\"player1\">");
            client.println("</div>");
            client.println("<h2>You Lose</h2>");
            score = 0;
          } 
         
            client.print("score is  ");
            client.print(score);
            client.println("</body>");
          client.println("</html>");
          
           break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    
    // close the connection:
    client.stop();
    //Serial.println("client disonnected");
 }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

