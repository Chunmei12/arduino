#include <Servo.h>




Servo servoLeft;
Servo servoRight;

int contourne;
byte maps[60][20];
byte x;
byte y;
boolean obstacledroite = false;



void setup() {
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  pinMode(7, INPUT);                         // Set right whisker pin to input
  pinMode(5, INPUT);                         // Set left whisker pin to input  

  x=0; //position horizontale initiale
  y=10;//position vertical initiale
  
  Serial.begin(9600); 
  /*servoLeft.attach(12);
  servoRight.attach(13); 
  avancer();
  delay(1200);            //test avncer d'un "Robot"
  servoLeft.detach();
  servoRight.detach();*/
  
}

void loop() {
  // put your main code here, to run repeatedly:
  contourne=0;//initialise la distance parcourue
  servoLeft.attach(12);//servo roue gauche atacher
  servoRight.attach(13);//servo roue droite atacher
  avancer(); // on commence à avancer
  //delay(3000);
  byte wLeft = digitalRead(5);               // variable pour verifier présence d'un obstacle
  byte wRight = digitalRead(7);              // variable pour verifier présence d'un obstacle
  
  //delay(120);
  while(wLeft == 1 && wRight == 1){
    wLeft = digitalRead(5);               // tant qu'il n'y a pas d'obstacle on avance d'un / 10e de "Robot"
    wRight = digitalRead(7);              
    contourne++;            // on incremente la valeur de la distance parcouru depuis le debus de la loop
    //Serial.println(contourne); 
    delay(120);
  }

  x = x + contourne;//position horizontal à laquel on a rencontrer l'obstacle
  maps[x][y]=1; // ajout de l'obstacle à la map
  reculer();      // on recule pour changer de trajectoir
  x = x - 9;      //la nouvelle position après le recul
  delay(1200);
  if(obstacledroite){//si on a trouver un obstacle à droite on teste de passer par la gauche
    tournergauche();//on tourne à gauche
  //reculer();
  delay(700);
  avancer();//on avance
  
  
  delay(240);
  wLeft = digitalRead(5);               // verifiaction qu'il n'y ai pas d'obstacle  
  wRight = digitalRead(7);
  if(wLeft == 0 || wRight ==0){//si il y a un obstacle on repart vers le coté droit
    obstacledroite = false;
    reculer();
    delay(240);
    tournerdroite();
    delay(700);
  }else{
    y--;//on se decale sur la gauche
    tournerdroite();//
    delay(700);
  }
  }else{//ici on essaye toujours de contourner vers la droite
  tournerdroite();//on tourne à droite
  //reculer();
  delay(700);
  avancer();//on avance 
  boolean obstacl=false;//variable qui représenta la présence d'un obstacle
  for(int i =0;i<20;i++){//si on tombe sur un obstacle on met obstacle à true
    wLeft = digitalRead(5);                 
    wRight = digitalRead(7);
    delay(24);
    if(wLeft == 0 || wRight ==0){
      obstacl = true;
    }
  }
  reculer();// on a avancer de 2 fois la distance pour verifier la presence d'un obstacle donc on recule d'une foi la distance
  
  delay(240);
  //wLeft = digitalRead(5);               // Copy left result to wLeft  
  //wRight = digitalRead(7);
  if(obstacl){//si il y a un obstacle 
    obstacledroite = true;// on met obstacledroite à vrai 
    reculer();// on recule
    delay(240);
    tournergauche();// et on se remet dans la bonne direction
    delay(700);
    maps[x][y+1]=1;//on ajoute l'obstacleà la map
  }else{
    y++;//on passe à la position verticale suivante
    tournergauche();//et on se repositione dans la bonne direction
    delay(700);
  }
  }
  servoLeft.detach();//les servos sont détachés
  servoRight.detach();
  afficherMap();
  
}

void avancer() {//fonction pour avancer
  servoLeft.writeMicroseconds(-1700);
  servoRight.writeMicroseconds(1700);
}

void reculer() {//fonction pour reculer
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(-1700);
}

void tournerdroite(){ //fonction pour tourner à droite
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
}

void tournergauche(){//fonction pour tourner à gauche
  servoLeft.writeMicroseconds(-1700);
  servoRight.writeMicroseconds(-1700);
}

void afficherMap() {//fonction pour afficher la map
  for(int i = 0; i<60; i++) {
    for (int j = 0 ; j<20; j++) {
        Serial.print(maps[i][j]);
        Serial.print("");     
    }
      Serial.println("");
  }
}

