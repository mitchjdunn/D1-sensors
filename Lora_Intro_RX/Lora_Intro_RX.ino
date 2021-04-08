#include <SoftwareSerial.h>
/*This Code is for the RECEIVER*/

String received;
SoftwareSerial loraSerial(12, 14); // TX RX

void setup() {
  pinMode(BUILTIN_LED,OUTPUT);
  digitalWrite(BUILTIN_LED,LOW);

  // Setup software serial interface on TX/RX pins 
  Serial.begin(115200);
  Serial.println("\r\nHello World!");
  loraSerial.begin(9600);

  delay(2000);

  loraSerial.print("AT\r\n");
  delay(200);
  Serial.println(loraSerial.readString());
  // Module respondes with an +OK or something
  
  // https://reyax.com/wp-content/uploads/2020/01/Lora-AT-Command-RYLR40x_RYLR89x_EN.pdf
  Serial.println("Asking bandwidth");
  loraSerial.println("AT+IPR?\r");
delay(100);
Serial.print(loraSerial.readString());
  loraSerial.print("AT+BAND?\r\n");
  delay(100);
  Serial.println(loraSerial.readString());
  // Page 4 for AT+PARAMETER
  Serial.println("Setting Adress");
  loraSerial.print("AT+ADDRESS=170\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  Serial.println("Setting NetworkID");
  loraSerial.print("AT+NETWORKID=6\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  Serial.println("Setting Bandwdith");
  loraSerial.print("AT+BAND=868500000\r\n");
  delay(100);

  Serial.println(loraSerial.readString());
  Serial.println("Asking bandwidth");
  loraSerial.print("AT+BAND?\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  Serial.println("Setting parameter");
  loraSerial.print("AT+PARAMETER=10,7,4,7\r\n");
  delay(100);
  Serial.println(loraSerial.readString());
  Serial.println("Asking bandwidth");
  loraSerial.print("AT+BAND?\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  digitalWrite(BUILTIN_LED, HIGH);
  
}

void loop() {
  if(loraSerial.available()){
    received = loraSerial.readString();
    Serial.println(received);

    // Receiving a "1" blinks the light.
    if(received.startsWith("+RCV") && received[11]=='1'){
        digitalWrite(BUILTIN_LED,LOW);
        delay(100);
        digitalWrite(BUILTIN_LED,HIGH);

    } 
  }
}
