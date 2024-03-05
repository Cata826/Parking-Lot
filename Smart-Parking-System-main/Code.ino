#include <HCSR04.h>
#include <Servo.h>
#include <LiquidCrystal.h>

Servo monServomoteur;
const int servoPin = 2;
const int trig1Pin = 3;
const int echo1Pin = 4;
const int trig2Pin = A1;
const int echo2Pin = 13;
const int LEDrouge = 7;
const int LEDvert = 8;
int position = 180;
int counter1 = 0;  // Counter for detected vehicles
int counter2 = 0;
int availableSlots = 4;  // Total number of parking slots
//int availableParkingSlots = 2;
int ok = 1;

UltraSonicDistanceSensor distanceSensor1(trig1Pin, echo1Pin);
UltraSonicDistanceSensor distanceSensor2(trig2Pin, echo2Pin);

// Define the LCD settings
LiquidCrystal lcd(6, 5, 9, 10, 11, 12);

void setup() {
  monServomoteur.attach(servoPin);
  pinMode(LEDrouge, OUTPUT);
  pinMode(LEDvert, OUTPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
 // lcd.print("Parking Slots: 2");
  Serial.begin(9600);  // Initialize serial communication for debugging
}

void loop() {

    int ledColor = 0;

  if (((distanceSensor1.measureDistanceCm() + 1) < 6) && ((distanceSensor1.measureDistanceCm() + 1) > 0) && (ok)) {
    monServomoteur.write(180);
    digitalWrite(LEDrouge, LOW);
    digitalWrite(LEDvert, HIGH);
    ledColor = 1;
//if(availableParkingSlots!=0)
    counter1++;
     Serial.println("Sensor1Detected");
      
       // Print LED color information
  if (ledColor == 1) {
    Serial.println("Green");
  } else {
    Serial.println("Red");
  }
    delay(5000);
  } else {
    monServomoteur.write(90);
    digitalWrite(LEDrouge, HIGH);
    digitalWrite(LEDvert, LOW);
    ledColor = 0;
       // Print LED color information
  if (ledColor == 1) {
    Serial.println("Green");
  } else {
    Serial.println("Red");
  }
  }
  if (((distanceSensor2.measureDistanceCm() + 1) < 6) && ((distanceSensor2.measureDistanceCm() + 1) > 0)) {
    monServomoteur.write(180);
    digitalWrite(LEDrouge, LOW);
    digitalWrite(LEDvert, HIGH);
    ledColor = 1;
      counter2++;
       Serial.println("Sensor2Detected");
      ok=1;
    
       // Print LED color information
  if (ledColor == 1) {
    Serial.println("Green");
  } else {
    Serial.println("Red");
  }
    delay(5000);
  } else {
    monServomoteur.write(90);
    digitalWrite(LEDrouge, HIGH);
    digitalWrite(LEDvert, LOW);
    ledColor = 0;
       // Print LED color information
  if (ledColor == 1) {
    Serial.println("Green");
  } else {
    Serial.println("Red");
  }
  }

  delay(100);
  



  // Calculate the number of available parking slots
   int availableParkingSlots = availableSlots - counter1 + counter2;
  if(availableParkingSlots<0)
    {availableParkingSlots=0;
    counter2++;
    
    }
    
  if(availableParkingSlots>availableSlots)  {
    availableParkingSlots=availableSlots;
    counter1++;
  }
  if(availableParkingSlots==0)
  {
    ok=0;
    lcd.clear();
    lcd.setCursor(0, 1);
  lcd.print("Full parking");
  
  }
  else{
  lcd.setCursor(0, 0);
  lcd.print("Parking Slots: 4");  
  lcd.setCursor(0, 1);
  lcd.print("Available: ");
  lcd.print(availableParkingSlots);
  }
 
    
}
 

  // Print the information to the serial monitor
  // Serial.print("Number of parking slots available: ");
  // Serial.println(availableParkingSlots);

 

