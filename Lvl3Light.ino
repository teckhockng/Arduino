int sensorPin = A1;// select the input pin for the potentiometer
int ledPin1 = 13;
int ledPin2 = 12; // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
pinMode(ledPin2, OUTPUT);
pinMode(ledPin1, OUTPUT);  

}

void loop() {
 sensorValue = analogRead(sensorPin);
 if (sensorValue < 400){ 
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH); 
}

 if (sensorValue > 400){ 
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW); 
}                            
 
}
