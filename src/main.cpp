#include <Arduino.h>


// définition des Pin
const int beeperPin = 4;
const int pindetecteurdepoul = A0;
float Poul;
float BATT_S;
const int boutonPin = 2;
volatile bool etatProgramme = false;

void gestionnaireInterrupt() {
  // Bascule l'état du programme lorsque l'interruption est déclenchée
  etatProgramme = !etatProgramme;

  // Si le programme devient inactif, arrêter la tonalité
  if (!etatProgramme) {
    digitalWrite(beeperPin, LOW);
  }
}

void setup() {
  // Configure les pins
  pinMode(beeperPin, OUTPUT);
  pinMode(pindetecteurdepoul,INPUT);
  pinMode(boutonPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(boutonPin),gestionnaireInterrupt, FALLING);
}

void loop() {
Poul=analogRead(pindetecteurdepoul);
BATT_S  = (60/Poul)*1000 ;
int etatBouton= digitalRead(boutonPin);



if (etatProgramme){
if (Poul>100){
  // Génère une tonalité à 1200 Hz pendant 1 seconde
  int frequence = 1200;
  int duree = 1000;
 
  int periodeMicros = (1000000 / frequence); // Période en microsecondes
  int DemiPeriode = periodeMicros / 2; // Demi-période en microsecondes

  for (int k = 0; k < duree * 1000; k += periodeMicros) {
    // Cycle ON
   
    digitalWrite(beeperPin, HIGH);
    delayMicroseconds(DemiPeriode);

    // Cycle OFF
    digitalWrite(beeperPin, LOW);
    delayMicroseconds(DemiPeriode);
  }

  delay(BATT_S);
}
else if (Poul<50){
  // Génère une tonalité à 300 Hz pendant 1 seconde
  int frequence = 300;
  int duree = 1000;
 
  int periodeMicros = (1000000 / frequence); // Période en microsecondes
  int DemiPeriode = periodeMicros / 2; // Demi-période en microsecondes

  for (int k = 0; k < duree  * 1000; k += periodeMicros) {
    // Cycle ON
    digitalWrite(beeperPin, HIGH);
    delayMicroseconds(DemiPeriode);

    // Cycle OFF
    digitalWrite(beeperPin, LOW);
    delayMicroseconds(DemiPeriode);
  }

  delay(BATT_S);
}
else  {
  // Génère une tonalité à 600 Hz pendant 1 seconde
  int frequence = 600;
  int duree = 1000;
 
  int periodeMicros = (1000000 / frequence); // Période en microsecondes
  int DemiPeriode = periodeMicros / 2; // Demi-période en microsecondes

  for (int k = 0; k < duree * 1000; k += periodeMicros) {
    // Cycle ON
   
    digitalWrite(beeperPin, HIGH);
    delayMicroseconds(DemiPeriode);

    // Cycle OFF
    digitalWrite(beeperPin, LOW);
    delayMicroseconds(DemiPeriode);
  }
  delay(BATT_S);
}}
}