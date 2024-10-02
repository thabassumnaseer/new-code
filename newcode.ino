#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <RTClib.h>  // Include RTC library for DS3231

RTC_DS3231 rtc;  // Create an RTC object

// OLED display TWI address
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(-1);

String data;  // Variable for storing received data

void setup() {
  Serial.begin(9600);  // Sets the baud for serial data transmission
  Serial.println("Starting...");

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set the RTC to the compile time
  }

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
  // Get the current time from RTC
  DateTime now = rtc.now();
  String currentTime = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Time: ");
  display.print(currentTime);
  display.display();

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
