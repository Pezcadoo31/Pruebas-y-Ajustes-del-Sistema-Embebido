// SLAVE

#include <Keypad.h>
#include <DHT.h>  
#include <Wire.h>

#define DHTPIN 2   // Define el pin al que está conectado el sensor DHT (pin 2)
#define DHTTYPE DHT11   // Define el tipo de sensor DHT como DHT11

DHT dht(DHTPIN, DHTTYPE);  // Crea un objeto de la clase DHT y lo inicializa con el pin y el tipo definidos anteriormente

const byte rowsCount = 4;
const byte columsCount = 4;

long duration;
int distanceCm;
int temp;
int hum;

 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
};
 
const byte rowPins[rowsCount] = { 11, 10, 9, 8 };
const byte columnPins[columsCount] = { 7, 6, 5, 4 };
const int EchoPin = 13;
const int TriggerPin = 12;
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
char key;
void setup() {
   Serial.begin(9600);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   dht.begin();  // Inicializa el sensor DHT

   Wire.begin(8);                
   Wire.onRequest(requestEvent);
 
}
 
void loop() {

  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  
  Serial.print("Distancia: ");
  Serial.print(distanceCm);

   char key = keypad.getKey();
 
   if (key) {
      Serial.println(key);
   }
  
   // Lectura de la humedad y temperatura
  float humidity = dht.readHumidity();  // Lee la humedad del ambiente desde el sensor DHT y la almacena en la variable humidity
  float temperature = dht.readTemperature();
  temp = int(temperature);
  hum = float(humidity);

    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" C°");
    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.print("Tecla: ");
    Serial.println(key);

  delay(2000); // Esperar 2 segundos antes de la próxima lectura
  
}

void requestEvent()
{
 Wire.write((uint8_t*)&distanceCm, sizeof(distanceCm));
  Wire.write((uint8_t*)&temp, sizeof(temp)); 
  Wire.write((char*)&key, sizeof(key));   
  Wire.write((uint8_t*)&hum, sizeof(hum));         
}
