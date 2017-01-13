 #include "pitches.h"; 
int buzzerPin  = 5 ;  //The buzzerPin is connected to pin 5 of the Arduino.
int button1Pin = 2;   //The SW1 button is connect to pin 2 of the Arduino.

void setup() { //The Setup function runs once.
  pinMode(buzzerPin, OUTPUT);  //Setup red LED pin as an output pin.
  pinMode(button1Pin, INPUT);  //Setup button1 pin as an input pin.
}

void loop() { //The loop function runs forever.
  if (digitalRead(button1Pin) == LOW) { //Check to see if button1 is pressed.
     tone(buzzerPin, NOTE_B4,408);     
     delay(408);    
tone(buzzerPin, NOTE_CS1, 35);    
delay(408);     
tone(buzzerPin, NOTE_F1 , 44);     
delay(408);     
tone(buzzerPin, NOTE_GS1, 52);     
delay(408);     
tone(buzzerPin, NOTE_AS1, 58);     
delay(408);     
tone(buzzerPin, NOTE_CS2 ,69);     
delay(408);     
tone(buzzerPin, NOTE_B4,408); 
delay(408);     
tone(buzzerPin, NOTE_GS2 ,104); 
delay(408);     
tone(buzzerPin, NOTE_FS3 ,185); 
delay(408);     
tone(buzzerPin, NOTE_FS5 ,7408); 
delay(408);     
tone(buzzerPin, NOTE_CS6 ,1109);  
delay(408);     
tone(buzzerPin, NOTE_FS6 ,1480);
delay(408);     
tone(buzzerPin, NOTE_CS8 ,4435);
delay(408);     
tone(buzzerPin, NOTE_DS8 ,4978);
delay(408);     
tone(buzzerPin, NOTE_DS8, 4978);
delay(408);     
tone(buzzerPin,NOTE_GS7, 3322); 
     } 
}
