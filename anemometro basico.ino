// Pin definitions
# define Hall sensor 2         //  Pino digital 2

// Constants definitions
const float pi = 3.14159265;           // Numero pi
int period = 5000;               // Tempo de medida(miliseconds)
int delaytime = 2000;             // Time between samples (miliseconds)
int radius = 147;      // Aqui ajusta o raio do anemometro em milimetros  **************

// Variable definitions
unsigned int Sample = 0;   // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned int RPM = 0;          // Revolutions per minute
float speedwind = 0;         // Wind speed (m/s)
float windspeed = 0;           // Wind speed (km/h)



void setup()
{
  // Set the pins
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);     //internall pull-up active
    
  //Start serial 
  Serial.begin(9600);       // sets the serial port to 9600 baud
  }

void loop()
{
  Sample++;
  Serial.print(Sample);
  Serial.print(": Start measurement...");
  windvelocity();
  Serial.println("   finished.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print(";  RPM: ");
  RPMcalc();
  Serial.print(RPM);
  Serial.print(";  Wind speed: ");
  
//*****************************************************************
//print m/s  
  WindSpeed();
  Serial.print(windspeed);
  Serial.print(" [m/s] ");              
  
//*****************************************************************
//print km/h  
  SpeedWind();
  Serial.print(speedwind);
  Serial.print(" [km/h] ");  
  Serial.println();


  delay(delaytime);                        //delay between prints
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


void RPMcalc(){
  RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
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

