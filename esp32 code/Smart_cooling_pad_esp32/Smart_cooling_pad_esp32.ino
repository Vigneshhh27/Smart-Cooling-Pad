#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C
#define OLED_SDA 21
#define OLED_SCL 22

// Fan PWM pins
const int fanPin1 = 4;
const int fanPin2 = 5;

// Temperature thresholds
const float off_temp = 45.0;
const float low_temp = 55.0;
const float med_temp = 70.0;
const float high_temp = 80.0;
const float max_temp = 90.0;

// PWM range
const int pwm_off = 0;
const int pwm_low_start = 50;
const int pwm_med_start = 140;
const int pwm_high_start = 215;
const int pwm_max = 255;

// OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Temp received from PC
float received_temp = 0;

void setup() {
  Serial.begin(115200);

  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  analogWrite(fanPin1, 0);
  analogWrite(fanPin2, 0);

  // Init OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Cooling Pad");
  display.println("Waiting for temp...");
  display.display();
}

void loop() {
  if (Serial.available() > 0) {
    String temp_str = Serial.readStringUntil('\n');
    received_temp = temp_str.toFloat();

    Serial.print("Received Temp: ");
    Serial.println(received_temp);

    int pwm_value = 0;
    String fan_status;

    // Temperature region logic
    if (received_temp < off_temp) {
      pwm_value = pwm_off;
      fan_status = "OFF";
    } else if (received_temp < low_temp) {
      pwm_value = map(received_temp, off_temp, low_temp, pwm_low_start, pwm_med_start);
      fan_status = "LOW";
    } else if (received_temp < med_temp) {
      pwm_value = map(received_temp, low_temp, med_temp, pwm_med_start, pwm_high_start);
      fan_status = "MED";
    } else if (received_temp < high_temp) {
      pwm_value = map(received_temp, med_temp, high_temp, pwm_high_start, pwm_max);
      fan_status = "HIGH";
    } else {
      pwm_value = pwm_max;
      fan_status = "MAX";
    }

    // Apply PWM
    analogWrite(fanPin1, pwm_value);
    analogWrite(fanPin2, pwm_value);

    // Update OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Smart Cooling Pad");

    display.setCursor(0, 15);
    display.print("Temp: ");
    display.print(received_temp, 1);
    display.println(" C");

    display.setCursor(0, 30);
    display.print("Fan PWM: ");
    display.print(pwm_value);

    display.setCursor(0, 45);
    display.print("Status: ");
    display.println(fan_status);

    display.display();
  }

  delay(100);
}
