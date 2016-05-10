
#this code will also send commands to the raspberrypi3 utilizing UDP


import socket

#UDP_IP = "10.166.164.70" # IP of RPi when on Mason network
UDP_IP = "192.168.2.4"
#UDP_PORT = 5006
UDP_PORT = 5007

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP

while True:
  inp = raw_input("Type Command:") #taking input from the user

  #these keys are to move the position servo i.e. the end-effector
  if   inp == "e":
  	print("opening gripper")
  	sock.sendto(inp, (UDP_IP, UDP_PORT))
  elif inp == "d":
	print("closing gripper")
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  #these keys are to move the arm up or down
  elif inp == "r":
	print("moving arm up")
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  elif inp == "f":
	print("moving arm down")
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  #these keys are to move the trolley left and right
  elif inp == "t":
	print("moving the trolley left")
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  elif inp == "y":
	print("moving the trolley right")
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  #these keys are used to rotate the the boom
  elif inp == "g":
        print ("moving boom to the left")      # left = ccw
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  elif inp == "h":
        print ("moving the boom to the right") # right = cw
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  #this key is used to stop all of the servos
  elif inp == "s":
        print ("stopping")
	sock.sendto(inp, (UDP_IP, UDP_PORT))
  else:
	print("Input not recognized ")




#Created by Josue Torrico
#For ECE 499 - SP16
