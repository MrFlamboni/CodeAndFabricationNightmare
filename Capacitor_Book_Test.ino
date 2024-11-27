

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Copper Tape only
  int noRes = analogRead(A0);
  // 220ohm Resistor
  int lowRes = analogRead(A3);
  // 1000ohm Resistor
  int highRes = analogRead(A5);

  Serial.println("Copper Tape:" + noRes);
  Serial.println("Small Resistor:" + lowRes);
  Serial.println("Large Resistor:" + highRes);
  delay(2000);
}
