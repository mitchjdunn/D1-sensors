#include <SoftwareSerial.h>
/*This Code is for the TRANSMITTER*/

String received;
int count = 0;
SoftwareSerial loraSerial(12, 14); // TX RX

void setup() {
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  Serial.begin(115200);
  Serial.println("\r\nHello World!");
  // Max baud rate for the GPIO pins 
  loraSerial.begin(9600);

  delay(2000);

  loraSerial.print("AT+ADDRESS=169\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  loraSerial.print("AT+NETWORKID=6\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  loraSerial.print("AT+BAND=868500000\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  loraSerial.print("AT+PARAMETER=10,7,1,7\r\n");
  delay(100);
  Serial.println(loraSerial.readString());

  digitalWrite(BUILTIN_LED, HIGH);
}

void loop() {
  count = ++count % 10; 

  Serial.printf("Sent! %d\n", count);
  // Send command format: "AT+SEND=" + receiver addr + "," + msg length + "," + msg data 
  loraSerial.printf("AT+SEND=170,103,This is a very long message that I will put one number at the end of for the sake of making it unique %d\r\n", count);

  // Blink after we send packet
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  
  // This'll wait for the +OK message back from the lora module
  // I thnk this means that the message was ack'd on the RX side
  while (!loraSerial.available());
  // Prints "+OK" or an error
  Serial.println(loraSerial.readString());


}
