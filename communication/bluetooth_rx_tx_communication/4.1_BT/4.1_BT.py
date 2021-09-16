import serial
import time


state = True
ser = serial.Serial('/dev/serial0', 9600)

while True:
    sonum = input("::: ") + "\n"
    ser.write(sonum.encode('ascii'))
    time.sleep(0.2)


