#include <WiFi.h>
#include <HTTPClient.h>

// ================= WIFI CONFIG =================
const char* ssid = "Hello_C1";
const char* password = "esskeetit4";

// NOTE: Use the SAME PC IP here that your backend and mobile app use
const char* alertURL = "http://10.213.208.47:5000/api/alert";
const char* buzzerStatusURL = "http://10.213.208.47:5000/api/buzzer/status";

// ================= PIN CONFIG =================
const int buzzer = 4;

const int trigPin = 16;
const int echoPin = 17;

const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;

// ================= SETTINGS =================
const int detectionDistance = 20;
const unsigned long statusCheckInterval = 1000;

// ================= STATES =================
bool alarmActive = false;      // Alarm stays active until backend disables it
bool buzzerAllowed = true;     // Controlled by backend
unsigned long lastStatusCheck = 0;

// =================================================

void setup() {
  Serial.begin(115200);
  Serial.println("\n===== ESP32 MOTION ALERT SYSTEM STARTING =====");

  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  connectToWiFi();
}

// =================================================

void loop() {
  int distance = readUltrasonic();

  if (distance >= 0) {
    Serial.print("Measured Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Check buzzer status from backend periodically
  if (WiFi.status() == WL_CONNECTED && (millis() - lastStatusCheck >= statusCheckInterval)) {
    checkBuzzerStatusFromServer();
    lastStatusCheck = millis();
  }

  // Trigger alarm ONCE when motion detected
  if (distance > 0 && distance <= detectionDistance && !alarmActive) {
    Serial.println("🚨 Motion Detected! Alarm Activated.");
    alarmActive = true;
    sendAlertToServer(distance);
  }

  // Keep alarm running if active and backend allows it
  if (alarmActive && buzzerAllowed) {
    tone(buzzer, 1000);             // Continuous tone
    setColor(HIGH, LOW, LOW);       // Red LED
  }

  // Stop alarm only if backend disables buzzer
  if (!buzzerAllowed && alarmActive) {
    Serial.println("🛑 Alarm stopped by backend.");
    noTone(buzzer);
    setColor(LOW, LOW, LOW);
    alarmActive = false;  // Reset system
  }

  delay(200);
}

// =================================================
// ULTRASONIC SENSOR
// =================================================
int readUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.034 / 2;
}

// =================================================
// WIFI CONNECTION
// =================================================
void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    setColor(LOW, LOW, HIGH);
    attempts++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✅ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    setColor(LOW, HIGH, LOW);
    delay(500);
    setColor(LOW, LOW, LOW);
  } else {
    Serial.println("❌ WiFi Connection Failed!");
    setColor(HIGH, LOW, LOW);
  }
}

// =================================================
// SEND ALERT TO SERVER
// =================================================
void sendAlertToServer(int distance) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost. Reconnecting...");
    connectToWiFi();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Still not connected. Alert cancelled.");
      return;
    }
  }

  HTTPClient http;
  http.begin(alertURL);
  http.addHeader("Content-Type", "application/json");

  String payload = "{";
  payload += "\"type\":\"Motion Detected\",";
  payload += "\"sensor\":\"Ultrasonic\",";
  payload += "\"location\":\"Kitchen\",";
  payload += "\"distance\":" + String(distance);
  payload += "}";

  Serial.println("Sending alert to server...");
  int httpCode = http.POST(payload);

  if (httpCode > 0) {
    Serial.print("Server Response Code: ");
    Serial.println(httpCode);
  } else {
    Serial.print("HTTP Error Code: ");
    Serial.println(httpCode);
  }

  http.end();
}

// =================================================
// CHECK BUZZER STATUS FROM SERVER
// =================================================
void checkBuzzerStatusFromServer() {
  HTTPClient http;
  http.begin(buzzerStatusURL);

  int httpCode = http.GET();

  if (httpCode == 200) {
    String response = http.getString();

    bool active = response.indexOf("\"buzzer_active\": true") != -1;
    buzzerAllowed = active;

    Serial.print("Backend buzzer_active = ");
    Serial.println(active ? "true" : "false");
  } else {
    Serial.print("Failed to get buzzer status. HTTP code: ");
    Serial.println(httpCode);
  }

  http.end();
}

// =================================================
// RGB CONTROL
// =================================================
void setColor(bool r, bool g, bool b) {
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}