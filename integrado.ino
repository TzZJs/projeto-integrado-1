/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <ESP8266WiFi.h>
#include <Hash.h>
#include <WebSocketsClient.h>

/* wifi ssid */
const char 	*wifi_ssid = "";
/* wifi ssid */
const char 	*wifi_password = "";

/* GPIO LED Vermelho */
const int	 LED_VERMELHO = 5;
const int	 LED_AMARELO = 4;

/* BaudRate 1152000 */
const int 	 BRD = 115200;

/* configurações para se conectar ao servidor websocket */
const char	*ip_servidor = "";
const char	*rota = "/";
const int	 porta = 1234;

/* instância global websocket */
WebSocketsClient websocket;

static void fn_recebe_evento(WStype_t, uint8_t *, size_t);

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

	/* conectar ao servidor websocket */;
	websocket.begin(ip_servidor, porta, rota);
	/* qualquer evento */
	websocket.onEvent(fn_recebe_evento);
	/* intervalo de reconexão */
	websocket.setReconnectInterval(5000);
	/* heart beat */
	websocket.enableHeartbeat(15000, 3000, 2);
}

static void
fn_recebe_evento(WStype_t tipo, uint8_t *dado, size_t tamanho)
{
	switch(tipo) {
		case WStype_DISCONNECTED:
			Serial.println("Desconectado Websocket");
			break;
		case WStype_CONNECTED:
			Serial.println("Conectado no Websocket");
			websocket.sendTXT("TAMO CONECTADO!!!");
			break;
	}
}

/*
 * Loop principal
 */
void
loop(void)
{
	websocket.loop();
	/* Desligamos o led vermelho */
	/*Serial.println("Desligando led vermelho");
	digitalWrite(LED_VERMELHO, LOW);
	digitalWrite(LED_AMARELO, LOW);
	delay(1000);
*/
	/* Liga o led vermelho */
/*
	Serial.println("Ligando led vermelho");
	digitalWrite(LED_VERMELHO, HIGH);
	digitalWrite(LED_AMARELO, HIGH);
	delay(1000);
*/
	/* aguarde 2 segundos */
	//delay(2000);
}
