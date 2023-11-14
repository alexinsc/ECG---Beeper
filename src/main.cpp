#include <Arduino.h>


// définition des Pin
const int beeperPin = 4; //Pin beeper
const int pindetecteurdepoul = A0; //Pin du détecteur de pouls
float Poul; //Variable de la valeur du pouls
float BATT_S; //Variable de la valeur de la battement par seconde
const int boutonPin = 2; //Pin du bouton
volatile bool etatProgramme = false; //Variable de l'état du programme

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
  pinMode(beeperPin, OUTPUT); //Définition de la pin beeper en sortie
  pinMode(pindetecteurdepoul,INPUT); //Définition de la pin du détecteur de pouls en entrée
  pinMode(boutonPin,INPUT); //Définition de la pin du bouton en entrée
  attachInterrupt(digitalPinToInterrupt(boutonPin),gestionnaireInterrupt, FALLING); //Définition de l'interruption du bouton
}

void loop() {
Poul=analogRead(pindetecteurdepoul); //Lecture de la valeur du pouls
BATT_S  = (60/Poul)*1000 ; //Calcul de la valeur de la battement par seconde

while (etatProgramme == true){
if (Poul>100){
  // Génère une tonalité à 1200 Hz pendant 1 seconde
  int frequence = 1200; // Fréquence en Hertz
  int nbreit = 1000; // Durée en millisecondes
 
  int periodeMicros = (1000000 / frequence); // Période en microsecondes
  int DemiPeriode = periodeMicros / 2; // Demi-période en microsecondes

  for (int k = 0; k < nbreit * 1000; k += periodeMicros) { //Boucle de la tonalité
    // Cycle ON
   
    digitalWrite(beeperPin, HIGH); //Définition du beeper en état haut
    delayMicroseconds(DemiPeriode); //Demi-période en microsecondes

    // Cycle OFF
    digitalWrite(beeperPin, LOW); //Définition du beeper en état bas
    delayMicroseconds(DemiPeriode); //Demi-période en microsecondes
  }

  delay(BATT_S); //Pause de la tonalité
}
// Le "else if" et le "else" fonctionne de la même manière que le "if"

else if (Poul<50){
  // Génère une tonalité à 300 Hz pendant 1 seconde
  int frequence = 300;
  int nbreit = 1000;
 
  int periodeMicros = (1000000 / frequence); // Période en microsecondes
  int DemiPeriode = periodeMicros / 2; // Demi-période en microsecondes

  for (int k = 0; k < nbreit  * 1000; k += periodeMicros) {
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
  int nbreit = 1000;
 
  int periodeMicros = (1000000 / frequence); // Période en microsecondes
  int DemiPeriode = periodeMicros / 2; // Demi-période en microsecondes

  for (int k = 0; k < nbreit * 1000; k += periodeMicros) {
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
