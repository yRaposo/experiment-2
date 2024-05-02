#include <DallasTemperature.h>
#include <OneWire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define ONE_WIRE_BUS 4 // Define o pino de dados do sensor DS18B20
OneWire oneWire(ONE_WIRE_BUS); // Cria uma instância da classe OneWire para se comunicar com o sensor DS18B20
DallasTemperature sensors(&oneWire); // Cria uma instância da classe DallasTemperature para controlar o sensor DS18B20


// URL da API Dendro
#define DENDRO_API_URL "https://sv95h56n-8080.brs.devtunnels.ms/api/v1/dendro/"
String ID = "123456789012";

const char *ssid = "CHOCOLATRA";
const char *password = "sa2nd3y40";

void setupWiFi()
{
    // Conecta-se à rede WiFi usando as credenciais fornecidas
    WiFi.begin(ssid, password);
    Serial.println("Conectando ao WiFi...");

    // Aguarda até que a conexão WiFi seja estabelecida
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    // Exibe uma mensagem informando que o dispositivo está conectado ao WiFi
    Serial.println("Conectado ao WiFi!");

    // Exibe o endereço IP atribuído ao dispositivo
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

void verifyResource()
{
    // Cria uma instância do objeto HTTPClient
    HTTPClient client;

    // Define a URL da requisição HTTP com base no número aleatório gerado
    client.begin(DENDRO_API_URL + String(ID));

    // Realiza uma requisição GET para a URL especificada
    int httpCode = client.GET();

    if (httpCode > 0 && httpCode != 404)
    {
        // Se a requisição foi bem-sucedida, exibe o código de status e o payload da resposta
        Serial.print("Código de status da requisição: ");
        Serial.println(httpCode);

        // Lê o corpo da resposta e o armazena em uma String
        String payload = client.getString();

        // Exibe o payload da resposta
        Serial.print("Resposta da requisição: ");
        Serial.println(payload);

        // Cria um objeto JSON a partir do payload da resposta
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);

        // Exibe o ID e o nome do dispositivo obtidos da resposta da API
        Serial.print("ID do dispositivo: ");
        Serial.print(doc["id"].as<String>());

        Serial.print(" - Nome do dispositivo: ");
        Serial.println(doc["name"].as<String>());
    } else if (httpCode == 404) {
        // Se o recurso não foi encontrado, usa o metodo post para criar um novo recurso
        Serial.println("Recurso não encontrado, criando novo recurso...");

        // Cria um objeto JSON para armazenar os dados do novo recurso
        DynamicJsonDocument doc(1024);
        doc["id"] = ID;
        doc["name"] = "Dendro Device";
        doc["temperature"] = 0;
        doc["humidity"] = 0;
        doc["light"] = 0;

        // Serializa o objeto JSON para uma string
        String json;
        serializeJson(doc, json);

        // Realiza uma requisição POST para criar um novo recurso
        client.begin(DENDRO_API_URL);
        client.addHeader("Content-Type", "application/json");
        int httpCode = client.POST(json);

        if (httpCode > 0) {
            // Se a requisição foi bem-sucedida, exibe o código de status e o payload da resposta
            Serial.print("Código de status da requisição: ");
            Serial.println(httpCode);

            String payload = client.getString();
            Serial.print("Resposta da requisição: ");
            Serial.println(payload);
        } else {
            // Se a requisição falhou, exibe uma mensagem de erro
            Serial.println("Erro na requisição HTTP");
        }
    } else {
        // Se a requisição falhou, exibe uma mensagem de erro
        Serial.println("Erro na requisição HTTP");
    }
}

void attResource() {
    // Cria um objeto JSON para armazenar os dados dos sensores
    DynamicJsonDocument doc(1024);

    float t = getTemperature();
    float h = getHumidity();

    doc["temperature"] = t; // Função que retorna a temperatura
    doc["humidity"] = h; // Função que retorna a umidade
    Serial.println("Umid: " + String(h) + " Temp: " + String(t));
    // Serializa o objeto JSON para uma string
    String json;
    serializeJson(doc, json);

    // Cria uma instância do objeto HTTPClient
    HTTPClient client;

    // Define a URL da requisição HTTP com base no ID
    client.begin(DENDRO_API_URL + String(ID));

    // Adiciona o cabeçalho Content-Type
    client.addHeader("Content-Type", "application/json");

    // Realiza uma requisição PATCH para atualizar o recurso
    int httpCode = client.PATCH(json);

    if (httpCode > 0) {
        // Se a requisição foi bem-sucedida, exibe o código de status e o payload da resposta
        Serial.print("Código de status da requisição: ");
        Serial.println(httpCode);

        String payload = client.getString();
        Serial.print("Resposta da requisição: ");
        Serial.println(payload);
    } else {
        // Se a requisição falhou, exibe uma mensagem de erro
        Serial.println("Erro na requisição HTTP");
    }
}

float getTemperature() {
    float t = sensors.getTempCByIndex(0); // Código para obter a temperatura
    return t;
}

float getHumidity() {
    float h = 10;//dht.readHumidity(); // Código para obter a umidade
    return h;
}

void setup()
{
    // Configurações iniciais

    // Inicia a comunicação serial com a velocidade de 115200 bauds
    Serial.begin(115200);

    setupWiFi();
    sensors.begin();
    // Obtém o MAC Address do ESP32
    String macAddress = WiFi.macAddress();
    // Remove os dois pontos (:) do MAC Address para criar um ID único
    macAddress.replace(":", "");

    ID = macAddress;
    // Exibe o ID único gerado a partir do MAC Address
    Serial.print("ID único: ");
    Serial.println(macAddress);
}

void loop()
{
    // Código que será executado repetidamente

    if ((WiFi.status() == WL_CONNECTED))
    {
        // Código que será executado quando o dispositivo estiver conectado à internet
        verifyResource();
        sensors.requestTemperatures();
        attResource();
    }
    else
    {
        // Código que será executado quando o dispositivo não estiver conectado à internet
        Serial.println("Dispositivo desconectado da internet!");
    }

    // Aguarda 10 segundos antes de executar o próximo ciclo do loop
    delay(1000);
}