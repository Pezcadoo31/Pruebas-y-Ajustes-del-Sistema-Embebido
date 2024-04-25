#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int speedPin=2;
int dirPin1=5;
int dirPin2=4;
int speedMotor= 90;
int dt = 100;
int dt2 = 5000;

void setup() {
  Wire.begin();

  lcd.init();                      
  lcd.backlight();

  
  pinMode(speedPin,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  Wire.requestFrom(8, 6); 
  if (Wire.available() == 6) {

    int distancia = Wire.read() | (Wire.read() << 8);
    int temperatura = Wire.read() | (Wire.read() << 8);
    char key = Wire.read();
    float humidity = Wire.read() | (Wire.read() << 8);

    lcd.setCursor(0, 0);  
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" C");

    lcd.setCursor(0, 1);  
    lcd.print("Key: ");
    lcd.print(key);

  
    if(temperatura >= 29){
      digitalWrite(dirPin1,0);
      digitalWrite(dirPin2,1);
      analogWrite(speedPin, 500);
      delay(dt);
      analogWrite(speedPin, speedMotor);
      delay(dt2);
    } else{
      analogWrite(speedPin, 0);
    }
   
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C ");

    Serial.print("Tecla presionada: ");
    Serial.println(key);

    Serial.print("Humedad: ");
    Serial.println(humidity);

  } else {
    Serial.println("Datos no recuperadoss");
  }

  delay(2000);
}





