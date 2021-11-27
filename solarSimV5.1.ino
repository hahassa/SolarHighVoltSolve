
const int analogPin1 = A0;
const int analogPin2 = A1;
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int inverterRelay = 7;
const int threshold1 = 890;
const int threshold2 = 950;
const int highVoltageCheckTime = 5000;
const int voltageCheckTime = 200;
bool iterator = false;

void setup() {
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(inverterRelay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int analogValue = 0;
  int analogPin = 0;
  int threshold = 0;
  if (iterator) {
    iterator = false;
    analogPin = analogPin2;
    analogValue = analogRead(analogPin);
    threshold = threshold2;
  }
  else {
    iterator = true;
    analogPin = analogPin1;
    analogValue = analogRead(analogPin);
    threshold = threshold1;
  }

  digitalWrite(inverterRelay, LOW);

  if (digitalRead(ledPin1) == 0 || digitalRead(ledPin2) == 0 || digitalRead(ledPin3) == 0) {
    if (analogValue >= threshold) {
      if (analogPin == analogPin1) {
        digitalWrite(inverterRelay, LOW);
      }
      else {
        digitalWrite(inverterRelay, HIGH);
      }
      digitalWrite(ledPin1, HIGH);
      delayTime(highVoltageCheckTime, analogPin);
      analogValue = analogRead(analogPin);
      if (analogValue >= threshold) {
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin1, LOW);
        delayTime(highVoltageCheckTime, analogPin);
        analogValue = analogRead(analogPin);
        if (analogValue >= threshold) {
          digitalWrite(ledPin1, HIGH);
          delayTime(highVoltageCheckTime, analogPin);
          analogValue = analogRead(analogPin);
          if (analogValue >= threshold) {
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            delayTime(highVoltageCheckTime, analogPin);
            analogValue = analogRead(analogPin);
            if (analogValue >= threshold) {
              digitalWrite(ledPin3, HIGH);
              digitalWrite(ledPin1, HIGH);
              digitalWrite(ledPin2, LOW);
              delayTime(highVoltageCheckTime, analogPin);
              analogValue = analogRead(analogPin);
              if (analogValue >= threshold) {
                digitalWrite(ledPin3, HIGH);
                digitalWrite(ledPin1, LOW);
                digitalWrite(ledPin2, HIGH);
                delayTime(highVoltageCheckTime, analogPin);
                analogValue = analogRead(analogPin);
                if (analogValue >= threshold) {
                  digitalWrite(ledPin3, HIGH);
                  digitalWrite(ledPin1, HIGH);
                  digitalWrite(ledPin2, HIGH);
                  delayTime(highVoltageCheckTime, analogPin);
                  analogValue = analogRead(analogPin);
                }            
              }
            }
          }
        }
      }
    }
  }
  
  if (analogValue < threshold) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
  
  Serial.println(analogValue);
  delay(voltageCheckTime);        
}

void delayTime(int number_of_milliseconds, int analogPin) {
  int counter = 0;
  while (counter < (number_of_milliseconds / voltageCheckTime)) {
    int analogValue = analogRead(analogPin);
    Serial.println(analogValue);
    counter++;
    delay(voltageCheckTime);
  }
}
