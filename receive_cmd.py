import socket
import serial

UDP_IP = "10.166.164.70" # IP of RPi when on Mason network
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((UDP_IP, UDP_PORT))
buffer = 1024

print"Waiting for Command"

# Listen for data on assigned port
while True:

        #receive from RPi
	cmd, address = sock.recvfrom(buffer) 
	
	print(cmd)
	
	#USB commuication with microcontroller
##	ser1 = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
##	if ser1.isOpen():
##		ser1.write(cmd) #send data to the opencm	
##	ser1.close()

