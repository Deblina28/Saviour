
void setup() {
  
  Serial.begin(2000000);
  
}
char l=65;
void loop() {
  l = (char)(90-map(analogRead(A0),0,1023,0,25));
  Serial.println((int)l);
}
