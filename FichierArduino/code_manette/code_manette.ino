int valeurRetour = 0;
int ledVerte = 5;
int RGBrouge = 10;
int RGBvert = 9;
int RGBbleu = 11;
bool clignote = true;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    //led verte
    pinMode(ledVerte,OUTPUT);

    //led RVB/RGB
    pinMode(RGBbleu,OUTPUT);//bleu
    pinMode(RGBvert,OUTPUT);//vert
    pinMode(RGBrouge,OUTPUT);//rouge

    //Joystick
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

   if(Serial.available() > 0) {
      valeurRetour = Serial.read();//valeur recu du code c++
      if(valeurRetour == 118){ // code decimal de v minuscule
        digitalWrite(ledVerte, HIGH);  
      }
      if(valeurRetour == 98){ // code decimal de b minuscule
        digitalWrite(ledVerte, LOW);
      }

      if(valeurRetour == 101){ // code decimal de e minuscule
        if(clignote) {
          
          analogWrite(RGBrouge, 70);  
          analogWrite(RGBvert , 255); 
          clignote = false;
        }
        else {
          analogWrite(RGBrouge, 255);  
          analogWrite(RGBvert , 255); 
          clignote = true;
        }
      }
      if(valeurRetour == 100){ // code decimal de d minuscule
         digitalWrite(RGBrouge, LOW);  
         digitalWrite(RGBbleu , LOW);  
         digitalWrite(RGBvert , LOW); 
    
      }
   }else {
     digitalWrite(RGBrouge, LOW);  
     digitalWrite(RGBbleu , LOW);  
     digitalWrite(RGBvert , LOW); 
   }

  int sensorValueA = digitalRead(2);//on recupere la valeur du bouton "poser bombe"
 // int sensorValueB = digitalRead(3);//on recupere la valeur du bouton "utiliser bonus"
  int sensorValueC = digitalRead(4);//on recupere la valeur du bouton "start/pause"
  int sensorValueJoystickX = analogRead(A0);//Valeur x du joystick - 0 = bas _ 1024 = haut
  int sensorValueJoystickY = analogRead(A1);//Valeur y du joystick - 0 = gauche _ 1024 = droite

  if(sensorValueA == HIGH){
    Serial.println("A"); //valeur envoyee au code c++
  }
  /*if(sensorValueB == HIGH){
    Serial.println("B");
  }*/
  
  if(sensorValueC == HIGH ){
    Serial.println("C");
  }

  if(sensorValueJoystickX <= 5) {
     Serial.println("X");//bas
  }
  else if(sensorValueJoystickX >= 1020) {
     Serial.println("H");//haut
  }

  if(sensorValueJoystickY <= 5) {
     Serial.println("G");//gauche
  }
  else if(sensorValueJoystickY >= 1020) {
     Serial.println("D");//droite
  }

  if(sensorValueJoystickX > 400 && sensorValueJoystickY > 400 && sensorValueJoystickX < 600 && sensorValueJoystickY < 600){
      Serial.println("R");//reinitialisation valeur
  }
  
  delay(50);
}
