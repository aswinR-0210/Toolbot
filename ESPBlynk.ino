#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(9600); // Communication with Arduino
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');

    if (msg == "OBSTACLE_FRONT") Blynk.notify("Front obstacle detected! Robot stopped.");
    else if (msg == "OBSTACLE_BACK") Blynk.notify("Back obstacle detected! Robot stopped.");
    else if (msg == "DESTINATION") Blynk.notify("Robot reached destination. Drawers opened!");
    else if (msg == "DRAWER_OPEN") Blynk.notify("Drawer motor triggered!");
  }
}
