// #include <Wire.h>

// #define SLAVE_ADDRESS 2 // Dirección del esclavo

// float humidity = 0; // Variable para almacenar la humedad recibida del esclavo
// float temperature = 0; // Variable para almacenar la temperatura recibida del esclavo

// void setup() {
//   Serial.begin(9600);
//   Wire.begin(); // Inicializa la comunicación I2C
// }

// void loop() {
//   Wire.requestFrom(SLAVE_ADDRESS, 8); // Solicita 8 bytes de datos al esclavo

//   while (Wire.available() < 8); // Espera a que se reciban todos los datos

//   byte buffer[sizeof(float)]; // Buffer para almacenar los bytes recibidos

//   // Recibe y convierte los bytes de la humedad
//   Wire.readBytes(buffer, sizeof(float));
//   memcpy(&humidity, buffer, sizeof(float));

//   // Recibe y convierte los bytes de la temperatura
//   Wire.readBytes(buffer, sizeof(float));
//   memcpy(&temperature, buffer, sizeof(float));

//   // Muestra los datos recibidos en el monitor serial
//   Serial.print("Humedad: ");
//   Serial.print(humidity);
//   Serial.println(" %");
//   Serial.print("Temperatura: ");
//   Serial.print(temperature);
//   Serial.println(" C°");

//   delay(2000); // Espera 2 segundos antes de solicitar nuevos datos al esclavo
// }


//INTENTO DE LCD
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C de la LCD y sus dimensiones (16 columnas, 2 filas)

// void setup() {
//   Wire.begin();                  // Iniciar la comunicación I2C como maestro
//   lcd.init();                    // Inicializar la LCD
//   lcd.backlight();               // Encender la retroiluminación de la LCD
//   lcd.clear();                   // Limpiar la LCD
//   Serial.begin(9600);            // Iniciar comunicación serial
// }

// void loop() {
//   Wire.requestFrom(8, 8);
//   while (Wire.available()) {     // Leer los datos disponibles del esclavo
//     char receivedChar = Wire.read(); // Leer un byte de datos del esclavo
//     Serial.print(receivedChar);     // Imprimir el byte recibido en el monitor serial
//     lcd.print(receivedChar);        // Imprimir el byte recibido en la LCD
//   }
//   Serial.println();       // Cámbia de línea en el Serial Monitor.
//     delay(500);
// }



// #include <Wire.h>

// void setup() {
//   Wire.begin(); // Inicia la comunicación I2C como maestro
//   Serial.begin(9600);
// }

// void loop() {
//   Wire.requestFrom(8, 2); // Solicita 2 bytes de datos del esclavo con dirección 8
//   requestSensorData();
//   delay(2000);
// }

// void requestSensorData() {
//   Wire.requestFrom(8, 2); // Solicita 2 bytes de datos del esclavo con dirección 8
  
//   while(Wire.available())    // slave may send less than requested
//   { 
//     if (Wire.available() >= 2 ) {
//     byte humidityByte = Wire.read(); // Lee el byte correspondiente a la humedad
//     byte temperatureByte = Wire.read(); // Lee el byte correspondiente a la temperatura

//     float humidity = float(humidityByte) / 100.0; // Convierte el byte de humedad a valor flotante
//     float temperature = float(temperatureByte); // La temperatura ya es un valor flotante

//     // Imprime los datos
//     Serial.print("Temperatura: ");
//     Serial.print(temperature);
//     Serial.println(" C°");
//     Serial.print("Humedad: ");
//     Serial.print(humidity);
//     Serial.println(" %");
//   } else {
//     Serial.println("Error: Datos insuficientes recibidos");
//   }
//     Serial.println();       // Cámbia de línea en el Serial Monitor.
//     delay(500);
// }
// }


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C de la LCD y sus dimensiones (16 columnas, 2 filas)

void setup() {
   Serial.begin(9600); // Iniciar comunicación serial
   Wire.begin(); // Iniciar la comunicación I2C como maestro
   lcd.init(); // Inicializar la LCD
   lcd.backlight(); // Encender la retroiluminación de la LCD
   lcd.clear(); // Limpiar la LCD
}

void loop() {
  int distancia = 0;
  Wire.requestFrom(8, 2); // Solicitar datos al esclavo con dirección 8 y esperar hasta 2 bytes

  while (Wire.available()) {
      distancia = Wire.read(); // Leer la distancia recibida del esclavo
      Serial.print(distancia);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Distancia:");
      lcd.setCursor(0, 1);
      lcd.print(distancia);
      lcd.print(" cm");
   }
  Serial.println();       // Cámbia de línea en el Serial Monitor.
  delay(500); // Esperar 1 segundo antes de la próxima solicitud
}






