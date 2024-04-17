#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// URL da API Dendro
#define DENDRO_API_URL "https://sv95h56n-8080.brs.devtunnels.ms/api/v1/dendro/"
#define ID "1"

const char* ssid = "CHOCOLATRA";
const char* password = "sa2nd3y40";

void setup() {
    // Configurações iniciais

    // Inicia a comunicação serial com a velocidade de 115200 bauds
    Serial.begin(115200);

    // Conecta-se à rede WiFi usando as credenciais fornecidas
    WiFi.begin(ssid, password);
    Serial.println("Conectando ao WiFi...");

    // Aguarda até que a conexão WiFi seja estabelecida
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    // Exibe uma mensagem informando que o dispositivo está conectado ao WiFi
    Serial.println("Conectado ao WiFi!");

    // Exibe o endereço IP atribuído ao dispositivo
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    
}

void loop() {
    // Código que será executado repetidamente

    if ((WiFi.status() == WL_CONNECTED)) {
        // Código que será executado quando o dispositivo estiver conectado à internet

        // Cria uma instância do objeto HTTPClient
        HTTPClient client;

        // Define a URL da requisição HTTP com base no número aleatório gerado
        client.begin(DENDRO_API_URL + String(ID));

        // Realiza uma requisição GET para a URL especificada
        int httpCode = client.GET();

        if (httpCode > 0) {
            // Se a requisição foi bem-sucedida, exibe o código de status HTTP e o payload da resposta

            // Obtém o payload da resposta como uma string
            String payload = client.getString();

            // Exibe o código de status HTTP e o payload da resposta
            Serial.println("\nStatuscode:" + String(httpCode));
            Serial.println(payload);

            // Cria um objeto JSON para armazenar o payload da resposta
            StaticJsonDocument<200> doc;

            // Deserializa o payload da resposta para o objeto JSON
            DeserializationError error = deserializeJson(doc, payload);

            // Verifica se houve algum erro durante a deserialização
            if (error) {
                // Se houve um erro, exibe uma mensagem de erro
                Serial.println("Erro ao deserializar o JSON");
            } else {
                // Se não houve erro, exibe o valor do campo "temperature" do objeto JSON
                Serial.print("Nome: ");
                Serial.println(doc["name"].as<String>());
                Serial.print("Posição: ");
                Serial.println(doc["position"].as<int>());
            }
        } else {
            // Se a requisição falhou, exibe uma mensagem de erro
            Serial.println("Erro na requisição HTTP");
        }
    } else {
        // Código que será executado quando o dispositivo não estiver conectado à internet
        Serial.println("Dispositivo desconectado da internet!");
    }

    // Aguarda 10 segundos antes de executar o próximo ciclo do loop
    delay(500);
}