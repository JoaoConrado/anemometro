// Pin definitions
# define Hall sensor 2         //  Pino digital 2

// Constants definitions
const float pi = 3.14159265;           // Numero pi
int period = 5000;               // Tempo de medida(miliseconds)
int delaytime = 2000;             // Time between samples (miliseconds)
int radius = 147;      // Aqui ajusta o raio do anemometro em milimetros  **************
int pin=0;
float valor =0;
int Winddir =0;


// Variable definitions
unsigned int Sample = 0;   // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned int RPM = 0;          // Revolutions per minute
float speedwind = 0;         // Wind speed (m/s)
float windspeed = 0;           // Wind speed (km/h)



void setup()
{
  // Set the pins
  pinMode(0, INPUT);
  pinMode(2, INPUT);
  
  digitalWrite(2, HIGH);     //internall pull-up active
    
  //Start serial 
  Serial.begin(9600);       // sets the serial port to 9600 baud
  }

void RPMcalc(){
  RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
}

// Measure wind speed
void windvelocity(){
  speedwind = 0;
  windspeed = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {
  }
}


void WindSpeed(){
  windspeed = ((4 * pi * radius * RPM)/60) / 1000;  // Calculate wind speed on m/s
 
}

void SpeedWind(){
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  // Calculate wind speed on km/h
 
}

void addcount(){
  counter++;
}   

void loop()
{
  Sample++;
  windvelocity();
  RPMcalc();
  WindSpeed();     
  SpeedWind();
  valor = analogRead(pin)* (5.0 / 1023.0); 
  Serial.print(valor);
  if (valor <= 0.27) {
  Winddir = 315;
  }
  else if (valor <= 0.32) { 
  Winddir = 270;
  }
  else if (valor <= 0.38) { 
  Winddir = 225;
  }
  else if (valor <= 0.45) { 
  Winddir = 180;
  }
  else if (valor <= 0.57) { 
  Winddir = 135;
  }
  else if (valor <= 0.75) { 
  Winddir = 90;
  }
  else if (valor <= 1.25) {  
  Winddir = 45;
  }
  else {  
  Winddir = 000;
  }
   Serial.print((String)Sample + ";" + (String)counter + ";" + (String)RPM + ";" + (String)windspeed + ";" + (String)speedwind + ";" + (String)Winddir );
   
    delay(delaytime);
  }
