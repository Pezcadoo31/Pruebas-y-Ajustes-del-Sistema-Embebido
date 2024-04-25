#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {

  //i2c
  Wire.begin();

  //lcd
  lcd.init();                      
  lcd.backlight();

  //motor

  Serial.begin(9600); 
}

void loop() {
  Wire.requestFrom(8, 6); 
  if (Wire.available() == 6) {

    int distancia = Wire.read() | (Wire.read() << 8);
    int temperatura = Wire.read() | (Wire.read() << 8);
    char key = Wire.read() | (Wire.read() << 8);

    //LCD
    lcd.setCursor(0, 0);  
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" C");

    lcd.setCursor(0, 1);  
    lcd.print("Key: ");
    lcd.print(key);

    //MOTOR


    //consola
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C ");

    Serial.print("Tecla presionada: ");
    Serial.println(key);

  } else {
    Serial.println("Datos incompletos recibidos");
  }

  delay(1000);
}






