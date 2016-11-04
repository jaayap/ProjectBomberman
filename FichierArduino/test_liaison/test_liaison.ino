int valeurRetour = 0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    //led verte
    pinMode(5,OUTPUT);

    //led RVB/RGB
    pinMode(11,OUTPUT);//bleu
    pinMode(12,OUTPUT);//vert
    pinMode(10,OUTPUT);//rouge

    //Joystick
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

   //digitalWrite(12, LOW);  
   // digitalWrite(11, HIGH);  
   // digitalWrite(10, HIGH); 
    
   if(Serial.available() > 0) {
      valeurRetour = Serial.read();//valeur recu du code c++
      if(valeurRetour == 97){ // code decimal de a minuscule
        digitalWrite(5, HIGH);  
      }
      if(valeurRetour == 98){ // code decimal de b minuscule
        digitalWrite(5, LOW);
      }
   }

  int sensorValueA = digitalRead(2);//on recupere la valeur du bouton "poser bombe"
  int sensorValueB = digitalRead(3);//on recupere la valeur du bouton "utiliser bonus"
  int sensorValueC = digitalRead(4);//on recupere la valeur du bouton "start/pause"
  int sensorValueJoystickX = analogRead(A0);//Valeur x du joystick - 0 = bas _ 1024 = haut
  int sensorValueJoystickY = analogRead(A1);//Valeur y du joystick - 0 = gauche _ 1024 = droite

  if(sensorValueA == HIGH){
    Serial.println("A"); //valeur envoyee au code c++
  }
  if(sensorValueB == HIGH){
    Serial.println("B");
  }
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
  delay(50);
}
