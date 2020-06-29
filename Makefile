SKETCH = integrado.ino

UPLOAD_PORT = /dev/ttyU0
CHIP = esp8266

include /usr/local/share/makeEspArduino/makeEspArduino.mk

serial:
	doas cu -l /dev/cuaU0 -s 115200
