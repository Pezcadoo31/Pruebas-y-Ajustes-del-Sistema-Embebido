#include <LiquidCrystal_I2C.h>  
#include <DHT.h>  

#define DHTPIN 2     // Define el pin al que está conectado el sensor DHT (pin 2)
#define DHTTYPE DHT11   // Define el tipo de sensor DHT como DHT11
int speedPin=11;
int dirPin1=12;
int dirPin2=13;
int speedMotor= 255;

DHT dht(DHTPIN, DHTTYPE);  // Crea un objeto de la clase DHT y lo inicializa con el pin y el tipo definidos anteriormente
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Crea un objeto de la clase LiquidCrystal_I2C con la dirección I2C de la pantalla LCD, y el número de columnas y filas

void setup() {
  // Inicialización del puerto serial y la pantalla LCD
  Serial.begin(9600);  // Inicia la comunicación serial a una velocidad de 9600 baudios
  lcd.init();  // Inicializa la pantalla LCD
  lcd.backlight();  // Enciende la retroiluminación de la pantalla LCD
  dht.begin();  // Inicializa el sensor DHT

  pinMode(speedPin, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2,OUTPUT);
}

void loop() {
  // Lectura de la humedad y temperatura
  float humidity = dht.readHumidity();  // Lee la humedad del ambiente desde el sensor DHT y la almacena en la variable humidity
  float temperature = dht.readTemperature();  // Lee la temperatura del ambiente desde el sensor DHT y la almacena en la variable temperature

  // Verificar si la lectura fue exitosa
  if (!isnan(temperature) && !isnan(humidity)) {  // Comprueba si los valores de temperatura y humedad son válidos (no son NaN)
    // Mostrar la temperatura y humedad en el monitor serial
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" C°");
    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Mostrar la temperatura y humedad en la pantalla LCD
    lcd.setCursor(0, 0);  // Establece la posición del cursor en la primera fila y primera columna de la pantalla LCD
    lcd.print("Temp: ");
    lcd.print(temperature);  // Muestra la temperatura en la pantalla LCD
    lcd.print(" C");
    lcd.setCursor(0, 1);  // Establece la posición del cursor en la segunda fila y primera columna de la pantalla LCD
    lcd.print("Humedad: ");
    lcd.print(humidity);  // Muestra la humedad en la pantalla LCD
    lcd.print(" %");
  } else {
    Serial.println("Error al leer los datos del sensor DHT.");  // Si la lectura no fue exitosa, imprime un mensaje de error en el monitor serial
    lcd.setCursor(0, 0);
    lcd.print("Error");
  }

  delay(2000); // Esperar 2 segundos antes de la próxima lectura

  if (temperature > 24.70)
  {
    digitalWrite(dirPin1, 1);
    digitalWrite(dirPin2, 0);
    analogWrite(speedPin, speedMotor);
  }
  else 
  {
    digitalWrite(dirPin1, 0);
    digitalWrite(dirPin2, 0);
    analogWrite(speedPin, speedMotor);
  }
}

