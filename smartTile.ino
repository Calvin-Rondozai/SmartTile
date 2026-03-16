// Pin definitions
const int buzzer = 4;

const int trigPin = 8;
const int echoPin = 12;

const int redPin = 7;
const int greenPin = 2;
const int bluePin = 13;

// Detection distance (in cm)
const int detectionDistance = 20;

void setup() {
  pinMode(buzzer, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);

  // Convert to cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= detectionDistance) {
    // Object detected
    
    tone(buzzer, 1000);  // 1kHz sound

    // Flash different colors
    setColor(HIGH, LOW, LOW);   // Red
    delay(200);
    setColor(LOW, HIGH, LOW);   // Green
    delay(200);
    setColor(LOW, LOW, HIGH);   // Blue
    delay(200);
    setColor(HIGH, HIGH, LOW);  // Yellow
    delay(200);
    setColor(LOW, HIGH, HIGH);  // Cyan
    delay(200);
    setColor(HIGH, LOW, HIGH);  // Purple
    delay(200);
  } 
  else {
    // No object
    noTone(buzzer);
    setColor(LOW, LOW, LOW); // Turn off RGB
  }
}

// Function to control RGB
void setColor(bool red, bool green, bool blue) {
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(bluePin, blue);
}