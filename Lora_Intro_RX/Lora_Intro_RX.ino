#include <SoftwareSerial.h>
/*This Code is for the RECEIVER*/

String received, response;
SoftwareSerial loraSerial(D6, D5);

void setup() {
  pinMode(BUILTIN_LED,OUTPUT);
  digitalWrite(BUILTIN_LED,LOW);

  // Setup software serial interface on TX/RX pins 
  loraSerial.begin(115200);

  delay(2000);

  loraSerial.print("AT\r\n");
  // Module respondes with an +OK or something
  Serial.print(loraSerial.readString());
  
  // https://reyax.com/wp-content/uploads/2020/01/Lora-AT-Command-RYLR40x_RYLR89x_EN.pdf
  // Page 4 for AT+PARAMETER
  loraSerial.print("AT+PARAMETER=7,9,1,7\r\n");
  Serial.print(loraSerial.readString());
  
  loraSerial.print("AT+BAND=896000000\r\n");
  Serial.print(loraSerial.readString());
  
  loraSerial.print("AT+ADDRESS=170\r\n");
  Serial.print(loraSerial.readString());
  
  loraSerial.print("AT+NETWORKID=6\r\n");
  Serial.print(loraSerial.readString());

  digitalWrite(BUILTIN_LED,HIGH);
}

void loop() {
  if(loraSerial.available()){
    received = loraSerial.readString();

    // Receiving a "1" blinks the light.
    if(received.startsWith("+RCV") && received[11]=='1'){
        digitalWrite(BUILTIN_LED,LOW);
        delay(100);
        digitalWrite(BUILTIN_LED,HIGH);

    // Otherwise just print the message received to the other serial channel
    } else { 
        Serial.print(received);
    }

  // Error
  } else {
    Serial.println("lora serial not available");
  }
}
