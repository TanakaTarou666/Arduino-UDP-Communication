#include <SPI.h>
#include <WiFiS3.h>
#include <WiFiUdp.h>

#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiUDP Udp;
unsigned int localPort = 8888;  // 送信先ポートを8888に設定
IPAddress destinationIP(127,0,0,1); //IPアドレスを設定

void setup() {
  Serial.begin(9600);
  // WiFiに接続
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  
  // IPアドレスを取得し表示
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Udp.begin(localPort);
}

void loop() {
  // データの送信
  char packetData[] = "Hello, UDP!";
  Udp.beginPacket(destinationIP, localPort); // 送信先のIPアドレスとポートを指定
  Udp.write(packetData, strlen(packetData));
  Udp.endPacket();
  Serial.println("send messeage");

  delay(1000); // 1秒待つ
}
