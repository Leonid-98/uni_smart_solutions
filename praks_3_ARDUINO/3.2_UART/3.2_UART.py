import serial
import threading
import time
import sys

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=5)
ser.flush()

    
while True:
    data = chr(input("::: "))
    ser.write(data.encode())





