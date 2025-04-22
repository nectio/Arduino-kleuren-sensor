int S0 = 2;
int S1 = 3;
int S2 = 4;
int S3 = 5;
int kleur_IN = 6;

int START = 7;
int STOP = 8;

int contactor = 9;
int contactor2 = 10;
int vent1 = 11;
int vent2 = 12;
int vent3 = 13;

int rood = 0;
int groen = 0;
int blauw = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(contactor, OUTPUT);
  pinMode(contactor2, OUTPUT);
  pinMode(vent1, OUTPUT);
  pinMode(vent2, OUTPUT);
  pinMode(vent3, OUTPUT);

  pinMode(kleur_IN, INPUT);
  pinMode(START, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW); //frequentieschaling op 20% gezet, waarom? geen idee... (meeste projecten gebruiken 20%)
  // om 2 extra pins vrij te maken in de toekomst, zal ik deze 2 regels vervangen met permanente bedrading.

  Serial.begin(9600);
}

void loop() {
  rood = leesKleur(1);
  delay(100);

  groen = leesKleur(2);
  delay(100);

  blauw = leesKleur(3);
  delay(100);

  Serial.print("Rood puls lengte: ");
  Serial.println(rood);
  Serial.print("Groen puls lengte: ");
  Serial.println(groen);
  Serial.print("Blauw puls lengte: ");
  Serial.println(blauw);


  int STARTstd = digitalRead(START); 
  int STOPstd = digitalRead(STOP);

  if (STARTstd == LOW) {
    digitalWrite(contactor, HIGH);
  }

  if (STOPstd == LOW) {
    digitalWrite(contactor, LOW);
  }
}

int leesKleur(int kleurKanaal) {
  if (kleurKanaal == 1) { // Rood
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
  } else if (kleurKanaal == 2) { // Groen
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
  } else if (kleurKanaal == 3) { // Blauw
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
  }

  // Meet de pulslengte
  int pulslengte = pulseIn(kleur_IN, LOW);
  return pulslengte; // de sterkte van de kleur, bijvoorbeeld hoe groen iets is, is recht evenredig met de frequencie van de kanaal die wij zullen meten.
}