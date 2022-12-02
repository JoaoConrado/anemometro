//A0 entrada do biruta 
//3v3 + biruta
//Gnd - biruta
// 5V + anemometro
// Pino 13 - D7 entrada do anemometro 

#include <ESP8266WiFi.h>
 
const char* server = "api.thingspeak.com";
String apiKey ="CHAVEDOCANALTHING"; //  Chave de seu Canal
const char* MY_SSID = "ID"; //id de seu wifi
const char* MY_PWD = "senha"; //senha de seu wifi
int sent = 0;

int i;

// Constants definitions

// Variable definitions
volatile  int rpmcount = 0;  // magnet counter for sensor - int counter = 0;
float rpm = 0;       // Revolutions per minute
float vel = 0;       // Velocidade (km/s)
float vmax = 0 ;      // Velocidade max
float vmd = 0 ;      // Velocidade media
float vsom = 0 ;     // Somatorio das vel
unsigned long startTime = 0 ;        // long startTime = 0
//unsigned long millis();    // **** não estava definido
unsigned long ML = 0;  //variavel millis
int periodo = 3000;
unsigned long lastmillis = 0;

unsigned long wlast=0; //test

const int pinHall = 13; //D7

int windirinp = A0;  //entrada biruta
int winddirstate = 0 ; 
int winddir_eu =0 ;
int dir = 90; //test

#define myPeriodic 3 //in sec | Thingspeak pub is 15sec

boolean tx_thing=false;


// Measure wind speed
void windvelocity(){
     ML=millis();
     if (ML - lastmillis >= periodo ){ 
    detachInterrupt(pinHall); 
    
    rpm = ((rpmcount)*60)/(periodo/1000);
    
    Serial.println(rpmcount);

    rpmcount = 0;           // Redémarre le compte tour
    lastmillis = millis();  // et réinitialise le chrono
    attachInterrupt(pinHall, rpm_vent, RISING); // Rélance l'interruption du compte tour

  }

delay(2500);
}
    
    
void rpm_vent(){ 

long ttime = micros()- wlast ;
wlast=micros();
if(ttime>50){
  
  rpmcount++;
}
}

void SpeedWind(){
  vel = ((28 * rpm) / 1000) * 3.6 ;  // Calculate wind speed on km/h
   vsom = vsom + vel ;
   if(vel > vmax ){
   vmax = vel;
   }
 
}



float DirWind(){
  
int winddirstate = analogRead(windirinp); 

  if ( (winddirstate >= 250) && (winddirstate <= 280) ) {
    winddir_eu = 0;
  }
  if ( (winddirstate >= 0) && (winddirstate <= 25) ) {
    winddir_eu = 45;
  }
  if ( (winddirstate >= 25) && (winddirstate <= 60) ) {
    winddir_eu = 90;
  }
  if ( (winddirstate >= 60) && (winddirstate <= 95) ) {
    winddir_eu = 135;
  }
  if ( (winddirstate >= 95) && (winddirstate <= 135) ) {
    winddir_eu = 180;
  }
  if ( (winddirstate >= 135) && (winddirstate <= 170) ) {
    winddir_eu = 225;
  }
  if ( (winddirstate >= 170) && (winddirstate <= 210) ) {
    winddir_eu = 270;
  }
  if ( (winddirstate >= 210) && (winddirstate <= 250) ) {
    winddir_eu = 315;
  }

  //if (debug) {
  //Serial.print("Wind Dir : ");
  //Serial.print(winddir_eu);
  Serial.print(" -- Pin Status: ");
  Serial.println(winddirstate);
  //}
  return winddir_eu;
}


void setup() {
  
Serial.begin(115200);
delay(10);
 //pinMode(intPin, INPUT_PULLUP);
 attachInterrupt(pinHall, rpm_vent, RISING);

 connectWifi();

}


void loop() 
{

  for (int i = 0; i < 20; i++) {
  Serial.print(" Leitura: ");
  Serial.println(i);
  windvelocity();
  SpeedWind();

Serial.print("Veloc : ");
Serial.print(vel);
Serial.print("Vel max : ");
Serial.println(vmax);

  delay(1000);

  }
   

  Serial.print("Veloc som :");
  Serial.println(vsom);
  vmd=vsom / 20 ;

DirWind();
Serial.print("Wind Dir OK ");
Serial.println(winddir_eu);

 tx_thing=true;

//sendTeperatureTS();

if (tx_thing){

sendTeperatureTS();
}

int count = myPeriodic;
while(count--)
delay(1000);



delay(100);
} 


void connectWifi()
{
Serial.print("Connecting to "+*MY_SSID);
WiFi.begin(MY_SSID, MY_PWD);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}

Serial.println("");
Serial.println("Connected");
Serial.println(""); 
}//end connect


void sendTeperatureTS()
{ 
WiFiClient client;

if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
Serial.println("WiFi Client connected ");

String postStr = apiKey;
postStr += "&field1=";  // Velocidade média
postStr += String(vmd);
postStr +="&field2="; // Velocidade máx.
postStr += String(vmax);
postStr +="&field3="; // Velocidade máx.
postStr += String(dir);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

Serial.print("Vel media : ");
Serial.print(vmd);
Serial.print("Vel max : ");
Serial.print(vmax);
Serial.print("  Wind Dir : ");
Serial.println(winddir_eu);
Serial.print(" % ");                             
Serial.println("- Send to Thingspeak.");

delay(100);

vsom=0;
vmax=0;

tx_thing=false;



}//end if
sent++;
client.stop();
}//end send               
