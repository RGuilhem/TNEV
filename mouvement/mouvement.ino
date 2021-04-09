//Variables for the on/off button
const int onOffPin = 4;
int onOffState = 0;
int onOffPrevState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

//Variables for the motor 1
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor1EnablePin = 9;
int motor1Enable = 0;
int motor1Speed = 0;

//Variables for the motor 2
const int motor2Pin1 = 11;
const int motor2Pin2 = 12;
const int motor2EnablePin = 10;
int motor2Enable = 0;
int motor2Speed = 0;

//Instructions
const int nombreInstructions = 4;
char instructions[nombreInstructions] = "ADAG";
int valeurs[nombreInstructions] = {60, 90, 30, 90};
int instructionIndex = 0;
bool instructionDone = false;
bool done = false;
unsigned long ti = 0;
unsigned long tActuel = 0;
int vRectiligne = 41; //en cm par secondes
int vAngulaire = 97; //en degres par secondes
bool startInstructions = false;
bool firstPass = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(onOffPin, INPUT);
  
  //Setup the control pins of the motors as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  //Setup the enable pins on the motors as outputs low by default
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  digitalWrite(motor1EnablePin, LOW);
  digitalWrite(motor2EnablePin, LOW);

  //Set the motors direction 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);

  //Debug here
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  changeSpeed(0, 0);
  buttonLogic();

  if (startInstructions) {
    if (firstPass) {
      ti = millis();
      firstPass = false;
      Serial.print("firstpass ti = ");
      Serial.println(ti);
    }
    bouge();
  }

  //Ecrit les vitesses dans les pin du pont en H
  if (motor1Enable == 1) {
    analogWrite(motor1EnablePin, motor1Speed);
  } else {
    analogWrite(motor1EnablePin, 0);
  }
  if (motor2Enable == 1) {
    analogWrite(motor2EnablePin, motor2Speed);
  } else {
    analogWrite(motor2EnablePin, 0);
  }

  
}

void bouge() {
  tActuel = millis();
  
  if (instructionDone) {
    if (instructionIndex < nombreInstructions -1){
      instructionIndex += 1;
      ti = millis();
      instructionDone = false;
    } else {
      done = true;
    }
  }
  if (!(done)) {
    unsigned long deltaT = tActuel - ti;
    
    if (instructions[instructionIndex] == 'A'){
      //code pour avancer droit
      int dActuel = deltaT * vRectiligne / 1000;
      if (dActuel < valeurs[instructionIndex]) {
        changeSpeed(255, 255);
      } else {
        instructionDone = true;
        changeSpeed(0, 0);
        delay(400);
      }
    } else if (instructions[instructionIndex] == 'D') {
      //code pour un virage à droite
      int angleActuel = deltaT * vAngulaire / 1000;
      if (angleActuel < valeurs[instructionIndex]) {
        changeSpeed(255, 0);
      } else {
        instructionDone = true;
        changeSpeed(0, 0);
        delay(400);
      }
    } else if (instructions[instructionIndex] == 'G') {
      //code pour un virage à gauche
      int angleActuel = deltaT * vAngulaire / 1000;
      if (angleActuel < valeurs[instructionIndex]) {
        changeSpeed(0, 255);
      } else {
        instructionDone = true;
         changeSpeed(0, 0);
        delay(400);
      }
    }
  } else {
    changeSpeed(0, 0);
  }
}


void changeSpeed(int vg, int vd) {
  //Change the speed of the motor depending ont the value entered
  motor1Speed = vd;
  motor2Speed = vg;
}

void buttonLogic() {
  //Turn the motors on or off with the button
  int value = digitalRead(onOffPin);
  if (value != onOffPrevState) {
    lastDebounceTime = millis();  
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (value != onOffState) {
      onOffState = value;
      if (onOffState == HIGH) {
        motor1Enable = !motor1Enable;
        motor2Enable = !motor2Enable;
        startInstructions = true;
      }
    } 
  } 
  onOffPrevState = value;
}
