// TEST
#include <Wire.h>

void setup() {
  Wire.begin(8);                // Iniciar la comunicación I2C como esclavo con dirección 8
  Wire.onRequest(sendData);
}

void loop() {
 // Enviar mensaje al maestro
  delay(500); // Esperar 5 segundos antes de enviar otro mensaje
}

void sendData() {    // Iniciar transmisión al maestro
  Wire.write("Pezcadoo"); // Enviar mensaje al maestro
    // Finalizar transmisión
}


//SENSOR DHT11
// #include <Wire.h>
// #include <DHT.h>

// #define DHTPIN 2     // Define el pin al que está conectado el sensor DHT (pin 2)
// #define DHTTYPE DHT11   // Define el tipo de sensor DHT como DHT11

// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(9600);
//   dht.begin();
//   Wire.begin(8); // Inicia la comunicación I2C como esclavo con dirección 8
//   Wire.onRequest(sendData); // Registra la función sendData para atender solicitudes del maestro
// }

// void loop() {
//   delay(100);
// }

// void sendData() {
//   float humidity = dht.readHumidity();  // Lee la humedad del ambiente desde el sensor DHT
//   float temperature = dht.readTemperature(); // Lee la temperatura del ambiente desde el sensor DHT

//   byte humidityByte = humidity * 100; // Convierte la humedad a un byte multiplicando por 100
//   byte temperatureByte = temperature; // La temperatura se almacena en un byte directamente
  
//   Wire.write(humidityByte); // Envía la humedad al maestro
//   Wire.write(temperatureByte); // Envía la temperatura al maestro
// }


// SENSOR ULTRASONICO
#include <Wire.h>

int distancia = 0;
const int EchoPin = 13;
const int TriggerPin = 12;

void setup() {
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   Wire.begin(8); // Iniciar la comunicación I2C como esclavo con dirección 8
   Wire.onRequest(sendData); // Establecer función para enviar datos al maestro
}

void loop() {
   int cm = ping(TriggerPin, EchoPin);
   distancia = cm;
   delay(1000); // Esperar 1 segundo antes de la próxima lectura
}

void sendData() {
   Wire.write(distancia); // Enviar la distancia medida al maestro
}

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
  
   digitalWrite(TriggerPin, LOW);  // Generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  // Generar Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
  
   duration = pulseIn(EchoPin, HIGH);  // Medir el tiempo entre pulsos, en microsegundos
  
   distanceCm = duration * 10 / 292/ 2;   // Convertir a distancia, en cm
   return distanceCm;
}







// #include <Keypad.h>
// #include <DHT.h>  
// #include <Wire.h>

// #define DHTPIN 2     // Define el pin al que está conectado el sensor DHT (pin 2)
// #define DHTTYPE DHT11   // Define el tipo de sensor DHT como DHT11

// DHT dht(DHTPIN, DHTTYPE);  // Crea un objeto de la clase DHT y lo inicializa con el pin y el tipo definidos anteriormente

// const byte rowsCount = 4;
// const byte columsCount = 4;

// int distancia = 0;
// int tiempo = 0;
// float humidity = 0;  // Variable global para la humedad
// float temperature = 0;  // Variable global para la temperatura
 
// char keys[rowsCount][columsCount] = {
//    { '1','2','3', 'A' },
//    { '4','5','6', 'B' },
//    { '7','8','9', 'C' },
//    { '#','0','*', 'D' }
// };
 
// const byte rowPins[rowsCount] = { 11, 10, 9, 8 };
// const byte columnPins[columsCount] = { 7, 6, 5, 4 };
// const int EchoPin = 13;
// const int TriggerPin = 12;
 
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 
// void setup() {
//    Serial.begin(9600);
//    pinMode(TriggerPin, OUTPUT);
//    pinMode(EchoPin, INPUT);
//    dht.begin();  // Inicializa el sensor DHT

//    Wire.begin(2);                // Este Esclavo es el número 2
//    Wire.onRequest(requestEvent);
 
// }
 
// void loop() {
//    char key = keypad.getKey();
 
//    if (key) {
//       Serial.println(key);
//    }
  
//    int cm = ping(TriggerPin, EchoPin);
//   Serial.print("Distancia: ");
//   Serial.println(cm);
//   delay(1000);

//    // Lectura de la humedad y temperatura
//   float humidity = dht.readHumidity();  // Lee la humedad del ambiente desde el sensor DHT y la almacena en la variable humidity
//   float temperature = dht.readTemperature();

//   if (!isnan(temperature) && !isnan(humidity)) {  // Comprueba si los valores de temperatura y humedad son válidos (no son NaN)
//     // Mostrar la temperatura y humedad en el monitor serial
//     Serial.print("Temperatura: ");
//     Serial.print(temperature);
//     Serial.println(" C°");
//     Serial.print("Humedad: ");
//     Serial.print(humidity);
//     Serial.println(" %");

//   } else {
//     Serial.println("Error al leer los datos del sensor DHT.");

//   }

//   delay(2000); // Esperar 2 segundos antes de la próxima lectura
  
// }

// int ping(int TriggerPin, int EchoPin) {
//   long duration, distanceCm;
  
//   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
//   delayMicroseconds(4);
//   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
//   delayMicroseconds(10);
//   digitalWrite(TriggerPin, LOW);
  
//   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
//   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
//   return distanceCm;
// }


// void requestEvent()
// {
//  byte buffer[sizeof(float)]; // Buffer para almacenar los bytes de la variable
//   // Convertir la variable humidity a bytes y enviarlos
//   memcpy(buffer, &humidity, sizeof(humidity));
//   Wire.write(buffer, sizeof(buffer)); // Envía los bytes de la variable humidity

//   delay(100);

//   // Convertir la variable temperature a bytes y enviarlos
//   memcpy(buffer, &temperature, sizeof(temperature));
//   Wire.write(buffer, sizeof(buffer)); // Envía los bytes de la variable temperature          
// }



