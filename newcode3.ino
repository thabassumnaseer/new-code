#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(-1);

String data;  // Variable for storing received data

void setup() {
  Serial.begin(9600);  // Sets the baud rate for serial data transmission
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

    // Parse the incoming data for specific types: TEXT or CALL
    if (data.startsWith("TEXT:")) {
      String message = data.substring(5);  // Get the text message after "TEXT:"
      displayMessage("Text: ", message);
    } 
    else if (data.startsWith("CALL:")) {
      String caller = data.substring(5);  // Get the caller name after "CALL:"
      displayMessage("Call: ", caller);
    } 
    else {
      displayMessage("Unknown: ", data);  // Display unknown data
    }
  }

  delay(1000);  // Update every second
}

// Helper function to display message on OLED
void displayMessage(String prefix, String content) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print(prefix);  // Print the type (Text or Call)
  display.print(content);  // Print the actual message or caller name
  display.display();
}
