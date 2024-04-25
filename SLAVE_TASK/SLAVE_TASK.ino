#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Keypad.h>

// Definiciones de pines y constantes
#define DHTPIN 49     // Define el pin al que está conectado el sensor DHT (pin 2)
#define DHTTYPE DHT11   // Define el tipo de sensor DHT como DHT11

DHT dht(DHTPIN, DHTTYPE);  // Crea un objeto de la clase DHT y lo inicializa con el pin y el tipo definidos anteriormente

const byte rowsCount = 4;
const byte columsCount = 4;

long duration;
int distanceCm;
int temp;
 
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

// Prototipos de funciones para las tareas
void taskUltrasonic(void *pvParameters);
void taskDHT(void *pvParameters);
void taskKeypad(void *pvParameters);
void taskI2C(void *pvParameters);

// Definiciones de objetos y variables globales
QueueHandle_t distanceQueue; // Cola para almacenar la distancia medida por el sensor ultrasónico

void setup() {
    // Configuración inicial
    Serial.begin(9600); // Iniciar comunicación serial
    Wire.begin(); // Iniciar la comunicación I2C
    distanceQueue = xQueueCreate(1, sizeof(int)); // Crear cola para la distancia medida por el sensor ultrasónico

    xTaskCreate(taskUltrasonic, "Ultrasonic", 100, NULL, 1, NULL); // Crear tarea para el sensor ultrasónico
    xTaskCreate(taskDHT, "DHT", 100, NULL, 1, NULL); // Crear tarea para el sensor DHT
    xTaskCreate(taskKeypad, "Keypad", 100, NULL, 1, NULL); // Crear tarea para el teclado
    xTaskCreate(taskI2C, "I2C", 100, NULL, 1, NULL); // Crear tarea para la comunicación I2C

    vTaskStartScheduler(); // Iniciar el planificador de tareas
}

void loop() {
    
}

// Implementación de las tareas

void taskUltrasonic(void *pvParameters) {
    for (;;) {
        // Código para la lectura del sensor ultrasónico
        digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
        delayMicroseconds(4);
        digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
        delayMicroseconds(10);
        digitalWrite(TriggerPin, LOW);
        duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
        distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm      
        Serial.print("Distancia: ");
        Serial.print(distanceCm);
        delay(2000); // Esperar 2 segundos antes de la próxima lectura

        vTaskDelay(pdMS_TO_TICKS(2000)); // Esperar 2 segundos
    }
}

void taskDHT(void *pvParameters) {
    for (;;) {
        // Código para la lectura del sensor DHT
        float humidity = dht.readHumidity();  // Lee la humedad del ambiente desde el sensor DHT y la almacena en la variable humidity
        float temperature = dht.readTemperature();
        temp = int(temperature);
        Serial.print("Temperatura: ");
        Serial.print(temp);
        Serial.println(" C°");
        Serial.print("Humedad: ");
        Serial.print(humidity);
        Serial.println(" %");
        delay(2000); // Esperar 2 segundos antes de la próxima lectura

        vTaskDelay(pdMS_TO_TICKS(2000)); // Esperar 2 segundos
    }
}

void taskKeypad(void *pvParameters) {
    for (;;) {
        // Código para la lectura del teclado
        char key = keypad.getKey();
        if (key) {
            Serial.println(key);
        }
        Serial.print("Tecla: ");
        Serial.println(key);
        
        vTaskDelay(pdMS_TO_TICKS(100)); // Esperar 100 milisegundos
    }
}

void taskI2C(void *pvParameters) {
    for (;;) {
        // Código para enviar datos al maestro a través de I2C
        Wire.write((uint8_t*)&distanceCm, sizeof(distanceCm));
        Wire.write((uint8_t*)&temp, sizeof(temp)); 
        Wire.write((uint8_t*)&key, sizeof(key)); 
        
        vTaskDelay(pdMS_TO_TICKS(5000)); // Esperar 5 segundos
    }
}

