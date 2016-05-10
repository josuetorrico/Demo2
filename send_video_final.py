#This a simple python file that will transmit an image
#over an infinite loop which will in effect send a set of frames
#or video feed.
#sources: getting started with videos OpenCV & Class notes

import cv2
import socket

capture = cv2.VideoCapture(0)
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
host ="192.168.2.1" #IP of computer
port = 5005
addr = (host,port)

while(True):
  ret, img = capture.read() #obtainging the feed from the camera
  resized = cv2.resize(img, (320,240)) #resize image for easier transfer
  cv2.imwrite("videoOut.jpg", resized) #saving the resized img
  f=open("videoOut.jpg", "rb") #converting
  data = f.read(1024) 	#reading into a buffer of size 1024
  while (data):
    if(sock.sendto(data,addr)):	#socket transmission
      data = f.read(1024)
  f.close()
  sock.sendto("stop",addr) #stop receiving

capture.release()
cv2.destroyAllWindows()
