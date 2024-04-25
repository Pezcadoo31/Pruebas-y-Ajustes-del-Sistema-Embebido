# Desafío Multitarea: Controlando un Sistema Embebido con Arduinos
Este proyecto explora el campo de los sistemas embebidos mediante la implementación de un sistema utilizando Arduinos, donde las tareas son esenciales. Se conectan dos Arduinos, integrando sensores y actuadores, y se analiza cómo las tareas pueden gestionar eficientemente las diferentes funcionalidades del sistema. Además, se comparan las implementaciones con y sin tareas, evaluando su eficacia y eficiencia.

## Descripción del Proyecto
El proyecto consiste en desarrollar un sistema embebido utilizando dos placas Arduino interconectadas mediante el protocolo I2C. La primera placa Arduino está equipada con un sensor de temperatura, un sensor de proximidad y un teclado matricial de 4x4. La segunda placa Arduino cuenta con un motor y un display LCD de 16x2.

El objetivo del sistema es que la primera placa Arduino lea continuamente la información de los sensores y del teclado matricial, la envíe al display LCD y, a través del protocolo I2C, transmita estos datos a la segunda placa Arduino. La segunda placa Arduino recibirá la información y la mostrará en el display LCD. Además, controlará el motor según los datos recibidos del sensor de temperatura.

## Configuración y Ejecución
1. Instalación del Entorno de Desarrollo: Es necesario tener el entorno de desarrollo Arduino IDE instalado en su computadora.
2. Conexión del Hardware: Siga las instrucciones proporcionadas en la documentación para conectar los componentes físicos correctamente.
3. Carga del Código: Abra los archivos de código fuente en Arduino IDE y cárguelos en las placas Arduino correspondientes.
4. Ejecución del Proyecto: Una vez cargado el código, alimente las placas Arduino y observe el funcionamiento del sistema.

## Contribuciones
Se anima a cualquier persona interesada a contribuir al proyecto. Las contribuciones pueden incluir mejoras en el código, correcciones de errores, actualizaciones de documentación o sugerencias de nuevas características.