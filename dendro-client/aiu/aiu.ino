#include <ESP32PWM.h>
#include <ESP32Servo.h>

Servo myservo;  // cria um objeto servo para controlar um servo
// 16 objetos servo podem ser criados no ESP32

int pos = 0;    // variável para armazenar a posição do servo
// Pinos GPIO PWM recomendados no ESP32 incluem 2,4,12-19,21-23,25-27,32-33
int servoPin = 13;

void setup() {
	// Permite a alocação de todos os timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // servo padrão de 50 hz
	myservo.attach(servoPin, 500, 2400); // anexa o servo ao pino 18 ao objeto servo
	// usando min/max padrão de 1000us e 2000us
	// diferentes servos podem exigir configurações min/max diferentes
	// para uma varredura precisa de 0 a 180 graus
}

void loop() {

	for (pos = 0; pos <= 180; pos += 1) { // vai de 0 graus a 180 graus
		// em incrementos de 1 grau
		myservo.write(pos);    // diz ao servo para ir para a posição na variável 'pos'
		delay(15);             // espera 15ms para o servo alcançar a posição
	}
	for (pos = 180; pos >= 0; pos -= 1) { // vai de 180 graus a 0 graus
		myservo.write(pos);    // diz ao servo para ir para a posição na variável 'pos'
		delay(15);             // espera 15ms para o servo alcançar a posição
	}
}