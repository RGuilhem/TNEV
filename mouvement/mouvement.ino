//Variables for the on/off button
const int onOffPin = 4;
int onOffState = 0;
int onOffPrevState = 0;

//Variables for the motor 1
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor1EnablePin = 9;
int motor1Enable = 0;
int motor1Speed = 150;

//Variables for the motor 2
const int motor2Pin1 = 11;
const int motor2Pin2 = 12;
const int motor2EnablePin = 10;
int motor2Enable = 0;
int motor2Speed = 150;

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
  onOffState = digitalRead(onOffPin);
  delay(1);

  //Turn the motors on or off with the button
  if (onOffState != onOffPrevState) {
    if (onOffState == HIGH) {
      motor1Enable = !motor1Enable;
      motor2Enable = !motor2Enable;
    }
  }

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

  Serial.print("Motor1 : ");
  Serial.println(motor1Enable);
  Serial.print("Motor2 : ");
  Serial.println(motor2Enable);
  
}
