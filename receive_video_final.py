#This a simple python file that will receive an image
#over an infinite loop which will in effect show a set of frames
#or video feed.
#sources: getting started with videos OpenCV & Class notes


import socket
import cv2

IP="192.168.2.1"	#IP of my computer
port = 5005
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind((IP,port))
addr = (IP,port)

count = 0
cv2.namedWindow("Crane Cam", cv2.WINDOW_NORMAL) #so that window is resizeable

while True:
	f = open("video.jpg","wb")	#to store the frames
	
	data,addr = sock.recvfrom(1024) #receiving socket in a buffer of size 1024
	while(data):
		f.write(data)
		data,addr = sock.recvfrom(1024)
		if data == "stop":
			f.close()
			frame = cv2.imread("video.jpg",1) #open
			cv2.imshow("Crane Cam", frame)	#display
			cv2.waitKey(50)			#wait forkeyboard input
			break
