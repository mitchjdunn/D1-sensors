void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial.print("AT+IPR=9600\r\n");
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
}

void loop() {
}
