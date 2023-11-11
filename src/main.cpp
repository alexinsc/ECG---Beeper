#include <Arduino.h>
#include <Tone.h>

// put function declarations here:
// Pin du buzzer
int pinBuzzer = 9;

// Pin du bouton poussoir
int buttonPin = 6;

// Fréquences cardiaques
int highRate = 90;
int normalRate = 75;
int lowRate = 60;

// État du beepage
boolean beepEnabled = true;

void setup() {
  // Configuration des pins
  pinMode(pinBuzzer, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Attachement de l'interruption au bouton poussoir
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleBeep, FALLING);

  // Initialisation de la communication série
  Serial.begin(9600);
}

// Fonction pour basculer l'état du beepage
void toggleBeep() {
  beepEnabled = !beepEnabled;
}

void loop() {
  // Lire la fréquence cardiaque entrée par l'utilisateur
  if (Serial.available() > 0) {
    int heartbeatRate = Serial.parseInt();
    
    // Vérifier si le beepage est activé
    if (beepEnabled) {
      // Sélectionner la fréquence de beep en fonction de la fréquence cardiaque
      if (heartbeatRate > highRate) {
        tone(pinBuzzer, 1000); // Beep aigu
      } else if (heartbeatRate >= lowRate) {
        tone(pinBuzzer, 800); // Beep modéré
      } else {
        tone(pinBuzzer, 600); // Beep grave
      }

      // Pause en fonction de la fréquence cardiaque
      delay(60000 / heartbeatRate);
    } else {
      noTone(pinBuzzer); // Arrêter le beepage si désactivé
    }
  }
}
