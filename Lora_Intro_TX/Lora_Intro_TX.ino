/*This Code is for the TRANSMITTER*/

void setup() {
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  
  Serial.begin(115200);   //default baudrate of module is 115200
  delay(100);             //wait for Lora device to be ready
  
  Serial.print("AT\r\n");
  delay(100);
  
  Serial.print("AT+PARAMETER=12,4,1,7\r\n");    //For More than 3Kms
  delay(100);   //wait for module to respond
  
  Serial.print("AT+BAND=896000000\r\n");    //Bandwidth set to 868.5MHz
  delay(100);   //wait for module to respond
  
  Serial.print("AT+ADDRESS=169\r\n");   //needs to be unique
  delay(100);   //wait for module to respond
  
  Serial.print("AT+NETWORKID=6\r\n");   //needs to be same for receiver and transmitter
  delay(100);   //wait for module to respond

  digitalWrite(BUILTIN_LED, HIGH);
}

void loop() {
  Serial.print("AT+SEND=170,1,1\r\n");    //send 1 to address 116("1" is of 1 byte)
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);

  delay(1900);
}
