#include <WiFi.h>

const char* ssid = "CHOCOLATRA";
const char* password = "sa2nd3y40";

void setup() {
    // Configurações iniciais
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Conectando ao WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("Conectado ao WiFi!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Código que será executado repetidamente
    if ((WiFi.status() == WL_CONNECTED)) {
        // Código que será executado quando o dispositivo estiver conectado à internet
        Serial.println("Dispositivo conectado à internet!");
        delay(500);
    } else {
        // Código que será executado quando o dispositivo não estiver conectado à internet
        Serial.println("Dispositivo desconectado da internet!");
    }
}