import serial
import time


state = True
ser=serial.Serial('/dev/serial0' ,9600)

while True:
    if state:
        sonum = input("::: ")
        ser.write(sonum.encode('ascii'))
        time.sleep(0.2)
        state = False
        
    if ser.inWaiting():
        read_serial=ser.read(ser.inWaiting())
        state = True
        print (read_serial.decode('ascii'))

    time.sleep(2)

