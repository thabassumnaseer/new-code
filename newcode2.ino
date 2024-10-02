#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(-1);

String data;  // Variable for storing received data

void setup() {
  Serial.begin(9600);  // Sets the baud for serial data transmission
  Serial.println("Starting...");

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Initialized");
  display.display();

  Serial.println("Setup complete, waiting for data...");
}

void loop() {
  // Check if data is coming in through the serial
  if (Serial.available() > 0) {
    data = Serial.readString();  // Read the incoming data & store it in 'data'
    Serial.println("Data received: " + data);  // Debug message to confirm receipt of data

    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Message: ");
    display.print(data);
    display.display();
  }

  delay(1000);  // Update every second
}

