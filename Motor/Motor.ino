int speedPin=11;
int dirPin1=12;
int dirPin2=13;
int speedMotor= 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(dirPin1, 1);
  digitalWrite(dirPin2, 0);
  analogWrite(speedPin, speedMotor);
  delay(8000);
  digitalWrite(dirPin1, 0);
  digitalWrite(dirPin2, 0);
  analogWrite(speedPin, speedMotor);
  delay(4000);
}

