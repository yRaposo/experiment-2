#include <ArduinoJson.h>
#include <DHT_U.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Sensor de Temperatura e Umidade
#define DHT_PIN 4
#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

// Sensor de Umidade do Solo
#define SOLO_PIN1 34
#define SOLO_PIN2 32
const int VALOR_MAXIMO = 634; // Valor com solo seco
const int VALOR_MINIMO = 304; // Valor com solo umido
const int CONCENTRACAO_MINIMA = 30;

// Sensor de Luminosidade
#define LUMINOSITY_PIN 34

// URL da API Kepos
#define DENDRO_API_URL "https://lx0w99ks-8081.brs.devtunnels.ms/api/v1/dendro"
#define MODULE_API_URL "https://lx0w99ks-8081.brs.devtunnels.ms/api/v1/modulo"

String ID = "1";
const int ID_MODULO[] = {1, 2};

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

void verifyDendro()
{
    // Cria uma instância do objeto HTTPClient
    HTTPClient client;

    // Define a URL da requisição HTTP com base no número aleatório gerado
    client.begin(DENDRO_API_URL + String("/" + ID));

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
    }
    else if (httpCode == 404)
    {
        // Se o recurso não foi encontrado, usa o metodo post para criar um novo recurso
        Serial.println("Recurso não encontrado, criando novo recurso...");

        // Cria um objeto JSON para armazenar os dados do novo recurso
        DynamicJsonDocument doc(1024);
        doc["id"] = ID;
        doc["name"] = "Dendro Device";
        doc["temperature"] = 0;
        doc["humidity"] = 0;
        doc["luminosity"] = 0;

        // Define o array 'modules' como um JsonArray
        JsonArray modules = doc.createNestedArray("modules");

        // Adiciona os elementos 'JsonObject' individuais ao array 'modules'
        JsonObject module1 = modules.createNestedObject();
        module1["id"] = 1;
        module1["name"] = "Module 1";
        module1["humidity"] = 0;
        module1["desc"] = nullptr;

        JsonObject module2 = modules.createNestedObject();
        module2["id"] = 2;
        module2["name"] = "Module 2";
        module2["humidity"] = 0;
        module2["desc"] = nullptr;

        // Serializa o objeto JSON para uma string
        String json;
        serializeJson(doc, json);

        // Realiza uma requisição POST para criar um novo recurso
        client.begin(DENDRO_API_URL);
        client.addHeader("Content-Type", "application/json");
        int httpCode = client.POST(json);

        if (httpCode > 0)
        {
            // Se a requisição foi bem-sucedida, exibe o código de status e o payload da resposta
            Serial.print("Código de status da requisição: ");
            Serial.println(httpCode);

            String payload = client.getString();
            Serial.print("Resposta da requisição: ");
            Serial.println(payload);
        }
        else
        {
            // Se a requisição falhou, exibe uma mensagem de erro
            Serial.println("Erro na requisição HTTP");
        }
    }
    else
    {
        // Se a requisição falhou, exibe uma mensagem de erro
        Serial.println("Erro na requisição HTTP");
    }
}

void attDendro()
{
    // Atualiza dados do Dendro
    //  Cria um objeto JSON para armazenar os dados dos sensores
    DynamicJsonDocument doc(1024);

    float t = getTemperature();
    float h = getHumidity();

    doc["temperature"] = t; // Função que retorna a temperatura
    doc["humidity"] = h;    // Função que retorna a umidade
    Serial.println("Umid: " + String(h) + " Temp: " + String(t));

    // Serializa o objeto JSON para uma string
    String json;
    serializeJson(doc, json);

    // Cria uma instância do objeto HTTPClient
    HTTPClient client;

    // Define a URL da requisição HTTP com base no ID
    client.begin(DENDRO_API_URL + String("/" + ID));

    // Adiciona o cabeçalho Content-Type
    client.addHeader("Content-Type", "application/json");

    // Realiza uma requisição PATCH para atualizar o recurso
    int httpCode = client.PATCH(json);

    if (httpCode > 0)
    {
        // Se a requisição foi bem-sucedida, exibe o código de status e o payload da resposta
        Serial.print("Código de status da requisição: ");
        Serial.println(httpCode);

        String payload = client.getString();
        Serial.print("Resposta da requisição: ");
        Serial.println(payload);
    }
    else
    {
        // Se a requisição falhou, exibe uma mensagem de erro
        Serial.println("Erro na requisição HTTP");
    }
}

void attModulo(String id, double umidade)
{
    // Atualiza dados do Modulo
    //  Cria um objeto JSON para armazenar os dados dos sensores
    DynamicJsonDocument doc(1024);

    doc["idDendro"] = ID; // Função que retorna a temperatura
    doc["humidity"] = umidade; // Função que retorna a umidade
    Serial.println("Umid: " + String(umidade));

    // Serializa o objeto JSON para uma string
    String json;
    serializeJson(doc, json);

    // Cria uma instância do objeto HTTPClient
    HTTPClient client;

    // Define a URL da requisição HTTP com base no ID
    String url = MODULE_API_URL + String("/" + id);

    client.begin(url);
    Serial.println(url);

    // Adiciona o cabeçalho Content-Type
    client.addHeader("Content-Type", "application/json");

    // Realiza uma requisição PATCH para atualizar o recurso
    int httpCode = client.PATCH(json);

    if (httpCode > 0)
    {
        // Se a requisição foi bem-sucedida, exibe o código de status e o payload da resposta
        Serial.print("Código de status da requisição: ");
        Serial.println(httpCode);

        String payload = client.getString();
        Serial.print("Resposta da requisição: ");
        Serial.println(payload);
    }
    else
    {
        // Se a requisição falhou, exibe uma mensagem de erro
        Serial.println("Erro na requisição HTTP");
    }
}

float getTemperature()
{
    float t = dht.readTemperature(); // Código para obter a temperatura
    return t;
}

float getHumidity()
{
    float h = dht.readHumidity(); // Código para obter a umidade
    return h;
}

void modulo()
{
    const int VALOR_MAXIMO = 2666; // Valor com solo seco
    const int VALOR_MINIMO = 1057; // Valor com solo umido = 1057

    const int CONCENTRACAO_MINIMA = 816;

    double leitura1 = analogRead(SOLO_PIN1);
    leitura1 = (leitura1 - 1057) / 16.09;
    Serial.println(leitura1);

    double leitura2 = analogRead(SOLO_PIN2);
    leitura2 = (leitura2 - 1057) / 16.09;
    Serial.println(leitura2);

    attModulo("1", leitura1);
    attModulo("2", leitura2);
}

void setup()
{
    // Configurações iniciais

    // Inicia a comunicação serial com a velocidade de 115200 bauds
    Serial.begin(115200);

    setupWiFi();
    // Obtém o MAC Address do ESP32
    String macAddress = WiFi.macAddress();
    // Remove os dois pontos (:) do MAC Address para criar um ID único
    macAddress.replace(":", "");

    ID = macAddress;
    //  Exibe o ID único gerado a partir do MAC Address
    Serial.print("ID único: ");
    Serial.println(ID);

    pinMode(SOLO_PIN1, INPUT);
    pinMode(SOLO_PIN2, INPUT);

    dht.begin();
}

void loop()
{
    // Código que será executado repetidamente

    if ((WiFi.status() == WL_CONNECTED))
    {
        // Código que será executado quando o dispositivo estiver conectado à internet
        verifyDendro();
        attDendro();
        modulo();
    }
    else
    {
        // Código que será executado quando o dispositivo não estiver conectado à internet
        Serial.println("Dispositivo desconectado da internet!");
    }

    // Aguarda 10 segundos antes de executar o próximo ciclo do loop
    delay(1000);
}