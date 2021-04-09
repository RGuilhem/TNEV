/* Photocell controlling lamp program */
// Constants
#define DELAY 200 // Delay between two measurements in ms
#define MIN_RAW 0 // Analog minimum value
#define MAX_RAW 1000 // Analog maximum value
#define MIN_CMD 0 // Digital minimum value
#define MAX_CMD 255 // Digital maximum value

// Parameters
const int sensorPin = A0; // Pin connected to sensor
int cmd = 0;
//Variables
int sensorVal; // Analog value from the sensor

//Main
void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  sensorVal = analogRead(sensorPin);
  cmd=sensorToLed(sensorVal);
  delay(DELAY);
  Serial.print("Sensor : ");
  Serial.println(sensorVal);
  Serial.print("Command : ");
  Serial.println(cmd);
}

//Functions
int sensorToLed(int raw){
  // The LED shine when the room is dark
  int val = map(sensorVal, 0, 1000, 0, 255);
  val=max(val,MIN_CMD);
  val=min(val,MAX_CMD);
  return val;
}
