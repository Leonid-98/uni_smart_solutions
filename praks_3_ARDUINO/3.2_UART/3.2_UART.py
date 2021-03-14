import serial
import threading
import time
import sys

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=5)
ser.flush()

def accept_data():
    global ser
    
    while True:
        data = ser.readlines().decode("utf-8")
        if data:
            print("<Serial rsponse>" + data)

def send_data():
    global ser
    
    while True:
        data = input("::: ")
        ser.write(("pi: " + data + "\n").encode())





