// Const def
int pin=0;
float valor =0;
int Winddir =0;


void setup() {
  //  inicializa a comunicação serial a 9600 bps: 
  Serial.begin(9600); 
}

void loop() {
  
 valor = analogRead(pin)* (5.0 / 1023.0);
 
Serial.print("leitura do sensor :");
Serial.print(valor);
Serial.println(" volt");

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
 Serial.print("Direcao a :");
 Serial.print(Winddir);
 Serial.print(" graus");
 Serial.println();
 delay (1000);
}





