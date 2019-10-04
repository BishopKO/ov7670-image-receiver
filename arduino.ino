#include <ov7670_camera.h>

// Create an instance of Camera Library
Camera camera;

void setup() {
  Serial.begin(1000000); // We want to communicate at 1M Baud rate
  pinMode(LED_BUILTIN, OUTPUT); // We want to use the built-in LED as an output
  digitalWrite(LED_BUILTIN, LOW); // Set the built-in LED to LOW (OFF)
  while (!Serial) {
    delay(200); // Just check if Serial communication is ready
  }
  camera.setup_arduino(); // Setup Arduino ports to communicate with the camera module
  camera.setup_camera(); // Setup the camera module to communicate with Arduino
  Serial.print("RDY"); // Send "RDY" message to PC
  digitalWrite(LED_BUILTIN, HIGH); // Set the built-in LED to HIGH (ON)
}

void loop() {
  if(Serial.available()) {
    // If there is some data sent from computer
    Serial.read(); // Read the character, and forget it
    flicker(2); // Flicker the LED two times
    digitalWrite(LED_BUILTIN, LOW); // Turn off the LED, Indicating image is being sent
    camera.capture_and_transmit(320, 240); // Capture a 320x240 image and pass it to computer
    Serial.print("OK BYE ***"); // Send "OK BYE ***" to computer
    Serial.flush(); // Make sure we send everything, nothing should remain in buffer
    flicker(5); // Blink the LED 5 times
    Serial.print("RDY"); // Send the "RDY" message again, saying, Hey, we're ready again
  }
  delay(200);
}

void flicker(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}
