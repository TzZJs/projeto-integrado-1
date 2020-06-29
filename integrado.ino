/*
1. Serial de bug
2. Ligar e desligar Leds
3. Conectar Wifi
4. Conectar no Servidor
5. Enviaremos uma mensagem (vaga preenchida ou não)
*/

#include <ESP8266WiFi.h>

/* wifi ssid */
const char 	*wifi_ssid = "Murilo";
/* wifi ssid */
const char 	*wifi_password = "32097070";

/* GPIO LED Vermelho */
int 		 LED_VERMELHO = 5;
int		 LED_AMARELO = 4;

/* BaudRate 1152000 */
int 		 BRD = 115200;


/*
 * Função Setup
 */
void
setup(void)
{
	/* inicializo o serial */
	Serial.begin(BRD);

	/* inicializamos os leds */
	pinMode(LED_VERMELHO, OUTPUT);
	pinMode(LED_AMARELO, OUTPUT);

	/* inicializar wifi modo estação (cliente) */
	WiFi.mode(WIFI_STA);
	WiFi.begin(wifi_ssid, wifi_password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println("Não conectado.");
	}

	/* imprime o ssid da rede wifi */
	Serial.print("Conectado Wifi: ");
	Serial.println(wifi_ssid);
	Serial.println("");

	/* retorna o ip da placa */
	Serial.print("IP: ");
	Serial.print(WiFi.localIP());
}

/*
 * Loop principal
 */
void
loop(void)
{
	/* Desligamos o led vermelho */
	Serial.println("Desligando led vermelho");
	digitalWrite(LED_VERMELHO, LOW);
	digitalWrite(LED_AMARELO, LOW);
	delay(1000);

	/* Liga o led vermelho */
	Serial.println("Ligando led vermelho");
	digitalWrite(LED_VERMELHO, HIGH);
	digitalWrite(LED_AMARELO, HIGH);
	delay(1000);

	/* aguarde 2 segundos */
	delay(2000);
}
