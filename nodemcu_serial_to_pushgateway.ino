#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>

  const char* ssid     = "accessping";
  const char* password = "password";
  int wifiStatus;
  int wifiStatusPrev = 0;
  HTTPClient httpclient;


void setup() {
  Serial.begin(115200);
  Serial.print("Your are connecting to;");
  Serial.println(ssid);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.begin(ssid, password);

}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    wifiStatusPrev = 0;
    delay(500);
    Serial.print(".");
  }
  if (wifiStatusPrev == 0) {
    Serial.println("");
    Serial.println("Your ESP is connected!");
    Serial.println("Your IP address is: ");
    Serial.println(WiFi.localIP());
    wifiStatusPrev = 1;
  }
  String serialtext = Serial.readString();
  if (serialtext != "")    {
    httpclient.begin("http://192.168.1.111:9091/metrics/job/ampmonitor"); //prometheus pushgateway address
    httpclient.addHeader("Content-Type", "text/html");
    int rcode = httpclient.POST(serialtext);
    String rcontent = httpclient.getString();
    Serial.print(rcode);
    Serial.print(" ");
    Serial.println(rcontent);
  }
}
