import pyfirmata
import time
import serial

#ser = serial.Serial(usbport,9600,timeout=1)

#port chosing
board=pyfirmata.Arduino('COM4')

it=pyfirmata.util.Iterator(board)
it.start()

board.digital[5].mode=pyfirmata.INPUT

#assign names
digital_input=board.get_pin('d:5:i')
led=board.get_pin('d:13:o')
Servo=board.get_pin('d:6:p')
	
def move(angle):
	if (0 <= angle <= 180):
		Servo.write(angle)

while True:
	#sw=board.digital[5].read()
	sw=digital_input.read()

	if sw is True:
		board.digital[13].write(1)
		move(1000)
	else:
		led.write(0)
		move(0)

	time.sleep(0.1)
	print(sw)
