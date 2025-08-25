#include <Servo.h>

// Pin configuration
const int rainSensorPin = A0;  // Analog pin connected to the rain sensor
const int threshold = 500;    // Threshold value for rain detection (adjust as needed)
Servo clothRackServo;         // Servo object

const int servoPin = 9;       // Pin connected to the servo signal
const int servoOpenAngle = 0; // Angle when it rains
const int servoCloseAngle = 90; // Angle when no rain

int currentAngle = servoCloseAngle;     // Keeps track of the current servo position

void setup() {
  Serial.begin(9600);
  clothRackServo.attach(servoPin);
  clothRackServo.write(currentAngle); // Default position
  Serial.println("System Initialized");
}

void loop() {
  int rainValue = analogRead(rainSensorPin);
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);

  if (rainValue < threshold && currentAngle != servoOpenAngle) {
    // Rain detected, move to 0 degrees gradually
    moveServoSmoothly(currentAngle, servoOpenAngle);
  } else if (rainValue >= threshold && currentAngle != servoCloseAngle) {
    // No rain, move to 90 degrees gradually
    moveServoSmoothly(currentAngle, servoCloseAngle);
  }

  delay(500); // Delay for stability
}

// Function to move servo smoothly to a target angle
void moveServoSmoothly(int startAngle, int targetAngle) {
  int step = (startAngle < targetAngle) ? 1 : -1; // Determine direction of movement
  for (int angle = startAngle; angle != targetAngle + step; angle += step) {
    clothRackServo.write(angle);
    delay(10); // Delay for smoothness (lower value = smoother but slower)
    currentAngle = angle;
  }
}
