#include <HTTPClient.h>
#include <WiFi.h>

const int pinSensorHujan = 34;

const char* ssid = "baa";         
const char* password = "hep67123"; 
const char* serverName = "http://192.168.180.158:5000/sensorhujan"; 

void setup()
{
  Serial.begin(9600);
    
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    float persentase;
    int hasilPembacaan = analogRead(pinSensorHujan);
    persentase = (100 - ((hasilPembacaan/4095.00)*100));
    Serial.print("Persentase Air Hujan = ");
    Serial.print(persentase);
    Serial.println("%");

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"persentase\":" + String(persentase) + "}";

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(10000); 

}