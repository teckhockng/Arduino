int sensorPin = A1;
int rgbRed = 9;
int rgbGreen = 10;
int rgbBlue = 11;
int sensorValue = 0;
int bright = 800;
int moderate = 550;
int dark = 150;

void setup() {
  // put your setup code here, to run once:
 pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(sensorPin);
if ( sensorValue < dark){
  digitalWrite(rgbRed, HIGH);
  digitalWrite(rgbBlue, LOW);
  digitalWrite(rgbGreen, LOW);
}  
if ((sensorValue > dark) && (sensorValue < bright)){
  digitalWrite(rgbBlue, HIGH);
  digitalWrite(rgbRed, LOW);
  digitalWrite(rgbGreen, LOW);
}  
if  (sensorValue > bright){
  digitalWrite(rgbGreen, HIGH);
  digitalWrite(rgbRed , LOW);
  digitalWrite(rgbBlue, LOW);
}
}

