#!/usr/bin/python3
import serial,time,sys
vastus = True
try:
# avame pordi /dev/ttyUSB0 kiirusega 9600 boodi
	ser=serial.Serial('/dev/serial0' ,9600)
# kuvame pordi nime
	print(ser.name)

	while True:
		if vastus:
			sonum = input('Sisestage teade mida soovid arduinole edastada: ')
			ser.write(sonum.encode('ascii'))
		#print (sonum)
			time.sleep(0.2)
			#print ("okei")
			vastus = False
# loeme terve rea puhvrist koos reavahetusega
		if ser.inWaiting():
			read_serial=ser.read(ser.inWaiting())
# l6ikame 2ra reavahetuse ja kuvame
			vastus = True
			print (read_serial.decode('ascii'))
# v2ike paus
		time.sleep(2)
except KeyboardInterrupt:
	ser.close()
	print ("saadeti k2sk l6petada...")
	sys.exit()
