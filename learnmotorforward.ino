const int IN1 = 18;
const int IN2 = 19;
const int EN = 5;
void setup() {
  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);
  // Optionally, initialize serial communication for debugging
  Serial.begin(115200);
}
void loop() {
  // Forward motion
  Serial.println("Forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 255); // Set PWM value for speed delay(2000);
  delay(2000)
}
