#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


#define I2C_ADDR          0x3f        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


#define SSID        "Georgian"
#define PASS        "" // 
#define DEST_HOST   "api.thingspeak.com"
#define DEST_IP     "52.7.53.111"
#define TIMEOUT     10000 // mS
#define CONTINUE    false
#define HALT        true
char ch;
String line ="";
String Time = "";
unsigned int long deadline;
unsigned long int now=0;
unsigned long int last=0;
unsigned long int interval =60000;

// #define ECHO_COMMANDS // Un-comment to echo AT+ commands to serial monitor

// Print error message and loop stop.
void errorHalt(String msg)
{
  Serial.println(msg);
  Serial.println("HALT");
  while(true){};
}

// Read characters from WiFi module and echo to serial until keyword occurs or timeout.
boolean echoFind(String keyword)
{
  byte current_char   = 0;
  byte keyword_length = keyword.length();
  
//   Fail if the target string has not been sent by deadline.
  deadline = millis() + TIMEOUT;
  while(millis() < deadline)
  {
    if (Serial1.available())
    {
      char ch = Serial1.read();
      Serial.write(ch);
      if (ch == keyword[current_char])
        if (++current_char == keyword_length)
        {
          Serial.println();
          return true;
        }
    }
  }
  return false;  // Timed out
}

// Read and echo all available module output.
// (Used when we're indifferent to "OK" vs. "no change" responses or to get around firmware bugs.)
void echoFlush()
  {while(Serial1.available()) Serial.write(Serial1.read());}
  
// Echo module output until 3 newlines encountered.
// (Used when we're indifferent to "OK" vs. "no change" responses.)
void echoSkip()
{
  echoFind("\n");        // Search for nl at end of command echo
  echoFind("\n");        // Search for 2nd nl at end of response.
  echoFind("\n");        // Search for 3rd nl at end of blank line.
}

// Send a command to the module and wait for acknowledgement string
// (or flush module output if no ack specified).
// Echoes all data received to the serial monitor.
boolean echoCommand(String cmd, String ack, boolean halt_on_fail)
{
  Serial1.println(cmd);
  #ifdef ECHO_COMMANDS
    Serial.print("--"); Serial.println(cmd);
  #endif
  
  // If no ack response specified, skip all available module output.
  if (ack == "")
    echoSkip();
  else
    // Otherwise wait for ack.
    if (!echoFind(ack))          // timed out waiting for ack string 
      if (halt_on_fail)
        errorHalt(cmd+" failed");// Critical failure halt.
      else
        return false;            // Let the caller handle it.
  return true;                   // ack blank or ack found
}

// Connect to the specified wireless network.
boolean connectWiFi()
{
  String cmd = "AT+CWJAP=\""; cmd += SSID; cmd += "\",\""; cmd += PASS; cmd += "\"";
  if (echoCommand(cmd, "OK", CONTINUE)) // Join Access Point
  {
    Serial.println("Connected to WiFi.");
    return true;
  }
  else
  {
    Serial.println("Connection to WiFi failed.");
    return false;
  }
}

// ******** SETUP ********
void setup()  
{
  lcd.begin (16,2);
    
    //Switch on the backlight
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    
  Serial.begin(115200);         // Communication with PC monitor via USB
  Serial1.begin(115200);        // Communication with ESP8266 via 5V/3.3V level shifter
  
  Serial1.setTimeout(TIMEOUT);
  Serial.println("ESP8266 Demo");
  
  delay(2000);

  echoCommand("AT+RST", "ready", HALT);    // Reset & test if the module is ready  
  Serial.println("Module is ready.");
  echoCommand("AT+GMR", "OK", CONTINUE);   // Retrieves the firmware ID (version number) of the module. 
  echoCommand("AT+CWMODE?","OK", CONTINUE);// Get module access mode. 
  
  // echoCommand("AT+CWLAP", "OK", CONTINUE); // List available access points - DOESN't WORK FOR ME
  
  echoCommand("AT+CWMODE=1", "", HALT);    // Station mode
  echoCommand("AT+CIPMUX=1", "", HALT);    // Allow multiple connections (we'll only use the first).

  //connect to the wifi
  boolean connection_established = false;
  for(int i=0;i<5;i++)
  {
    if(connectWiFi())
    {
      connection_established = true;
      break;
    }
  }
  if (!connection_established) errorHalt("Connection failed");
  
  delay(5000);

  //echoCommand("AT+CWSAP=?", "OK", CONTINUE); // Test connection
  echoCommand("AT+CIFSR", "", HALT);         // Echo IP address. (Firmware bug - should return "OK".)
  //echoCommand("AT+CIPMUX=0", "", HALT);      // Set single connection mode

         

}

// ******** LOOP ********
void loop(){
//this could not make the loop fun forever
//this only run once
//might do some more research in the future to make it run forever
//now=millis();
//if(now-last>interval){
//  last=now;

 
  
  boolean tempFound = false;
  boolean weatherFound = false;
  
  // Establish TCP connection
  String cmd = "AT+CIPSTART=0,\"TCP\",\""; cmd += DEST_IP; cmd += "\",80";
  if (!echoCommand(cmd, "OK", CONTINUE)) return;
  delay(2000);
  
  // Get connection status 
  if (!echoCommand("AT+CIPSTATUS", "OK", CONTINUE)) return;

  //Create more HTTP request in the future to get data such as temperature and date
  
  // Build HTTP request.
  cmd = "GET /apps/thinghttp/send_request?api_key=";
  cmd += "UACNZ0NKU0BUDL72";
  cmd += " HTTP/1.1\r\n";
  cmd += "Host: api.thingspeak.com\n"; cmd += ":\r\n\r\n";
  
  // Ready the module to receive raw data
  if (!echoCommand("AT+CIPSEND=0,"+String(cmd.length()), ">", CONTINUE))
  {
    echoCommand("AT+CIPCLOSE", "", CONTINUE);
    Serial.println("Connection timeout.");
    return;
  }
  
  // Send the raw HTTP request
  echoCommand(cmd, "OK", CONTINUE);  // GET
 
   //Loop forever echoing data received from destination server.
   while (!(tempFound & weatherFound)){
  if(Serial1.available()){
  //parse everything received into a string
    line += Serial1.readStringUntil('\n');
    
   if(line != ""){
     Serial.print(line);
    
   }
   //get the time around the last section of the string
   if(line.length() > 510){
  
   Time = line.substring(line.lastIndexOf('r')+8,line.lastIndexOf('0'));
   Serial.println(Time);
   lcd.setCursor(0,0);
   lcd.print(Time);
   Serial.println("AT+CIPCLOSE");
   }
    
  }
   }
//}
}




