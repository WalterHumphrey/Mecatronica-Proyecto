#include <AFMotor.h>  // Importamos libreria para control de motores
#include<Servo.h> // Importamos libreria para control de servomotor

#define Speed 200 // Definimos velocidad de motores

Servo Myservo;  // Definimos servomotor
AF_DCMotor motor1(1); // Definimos motor 1
AF_DCMotor motor2(2); // Definimos motor 2

// Definimos los pines de nuestros botones y la señal del buzzer
const int buttonPinUP = A0;
const int buttonPinDOWN = A1;
const int buttonPinLEFT = A2;
const int buttonPinRIGHT = A3;
const int buttonPinGRP = A4;
const int buzzer = A5; 

// Definimos variable para el estado de nuestros botones
int buttonStateUP = 0;
int buttonStateDOWN = 0;
int buttonStateLEFT = 0;
int buttonStateRIGHT = 0;
int buttonStateGRP = 0;
 
// Variable para controlar el estado de la garra
bool encendido = false;

void setup() {
  Serial.begin(9600); // Establecemos comunicacion serial para imrimir instrucciones
  motor1.setSpeed(Speed); // Definimos velocidad de motor 1
  motor2.setSpeed(Speed); // Definimos velocidad de motor 2

  // Definimos pines para botones como entrada con resistencia pull-up
  pinMode(buttonPinUP, INPUT_PULLUP);
  pinMode(buttonPinDOWN, INPUT_PULLUP);
  pinMode(buttonPinLEFT, INPUT_PULLUP);
  pinMode(buttonPinRIGHT, INPUT_PULLUP);
  pinMode(buttonPinGRP, INPUT_PULLUP);

  // Definimos pin de salida de señal para el buzzer
  pinMode(buzzer, OUTPUT);

  // Definimos pin del servomotor
  Myservo.attach(9);
}

void loop() {
  // Leemos los botones y actualizamos la variable de estado
  buttonStateUP = digitalRead(buttonPinUP);
  buttonStateDOWN = digitalRead(buttonPinDOWN);
  buttonStateLEFT = digitalRead(buttonPinLEFT);
  buttonStateRIGHT = digitalRead(buttonPinRIGHT);
  buttonStateGRP = digitalRead(buttonPinGRP);

  if (buttonStateUP == LOW){  // Movimiento hacia adelante
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    Serial.println("Adelante");
  } else if (buttonStateDOWN == LOW) {  // Movimiento hacia atras
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    Serial.println("Atras");
    digitalWrite(buzzer, HIGH); // Encendemos la señal del buzzer
  } else if (buttonStateLEFT == LOW) {  // Movimiento a la izquierda
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    Serial.println("Izquierda");
  } else if (buttonStateRIGHT == LOW) { // Movimiento a la derecha
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    Serial.println("Derecha");
  } else {  // Si no se presiona ningun boton el robot se detiene
    Serial.println("Stop");
    digitalWrite(buzzer, LOW);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
  if (buttonStateGRP == LOW) {  // Control del gripper, al presionar el boton alterna el estado
    encendido = !encendido;
    if (encendido == true) {
      Myservo.write(25);
      Serial.println(encendido);
    } else if (encendido == false){
      Myservo.write(90);
      Serial.println(encendido);
    }
    delay(300); // Rebote al presionar
    while(buttonStateGRP == HIGH); // Esperar a soltar boton 
    delay(100);
  }
}
