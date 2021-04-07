/*This Code is for the RECEIVER*/

String received;

void setup() {
  pinMode(BUILTIN_LED,OUTPUT);
  digitalWrite(BUILTIN_LED,LOW);
  // put your setup code here, to run once:
  Serial.begin(115200);   //default baudrate of module is 115200
  delay(2000);             //wait for Lora device to be ready

  Serial.print("AT\r\n");
  delay(1000);
  
  // https://reyax.com/wp-content/uploads/2020/01/Lora-AT-Command-RYLR40x_RYLR89x_EN.pdf
  // Page 4 for AT+PARAMETER
  Serial.print("AT+PARAMETER=12,4,1,7\r\n");    //For More than 3Kms
  delay(100);   //wait for module to respond
  
  Serial.print("AT+BAND=896000000\r\n");    //Bandwidth set to 868.5MHz
  delay(100);   //wait for module to respond
  
  Serial.print("AT+ADDRESS=170\r\n");   //needs to be unique
  delay(100);   //wait for module to respond
  
  Serial.print("AT+NETWORKID=6\r\n");   //needs to be same for receiver and transmitter
  delay(100);   //wait for module to respond

  digitalWrite(BUILTIN_LED,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    received = Serial.readString();
    if(received.startsWith("+RCV") && received[11]=='1'){  //in this case our single received byte would always be at the 11th position
        digitalWrite(BUILTIN_LED,LOW);
        delay(100);
        digitalWrite(BUILTIN_LED,HIGH);
    }
  }
}
