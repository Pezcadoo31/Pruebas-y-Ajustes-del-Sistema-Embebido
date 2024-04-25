#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void taskI2C(void *pvParameters);

void setup() {
  // Configuración inicial
  
  // Iniciar comunicación I2C
  Wire.begin();
  
  // Inicializar LCD
  lcd.init();                      
  lcd.backlight();

  // Crear tarea para la comunicación I2C
  xTaskCreate(taskI2C, "I2C", 100, NULL, 1, NULL);
  
  Serial.begin(9600); 
}

void loop() {
  // No es necesario tener código aquí con FreeRTOS
}

void taskI2C(void *pvParameters) {
  for (;;) {
    // Solicitar datos al esclavo con dirección 8 y esperar hasta 6 bytes
    Wire.requestFrom(8, 6); 
    if (Wire.available() == 6) {
      // Leer datos recibidos del esclavo
      int distancia = Wire.read() | (Wire.read() << 8);
      int temperatura = Wire.read() | (Wire.read() << 8);
      char key = Wire.read() | (Wire.read() << 8);

      // Mostrar datos en LCD
      lcd.setCursor(0, 0);  
      lcd.print("Temp: ");
      lcd.print(temperatura);
      lcd.print(" C");
      lcd.setCursor(0, 1);  
      lcd.print("Key: ");
      lcd.print(key);

      // Mostrar datos en consola
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

    vTaskDelay(pdMS_TO_TICKS(1000)); // Esperar 1 segundo antes de solicitar datos nuevamente
  }
}
