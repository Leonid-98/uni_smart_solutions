import serial
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(21,GPIO.OUT)
GPIO.output(21,GPIO.LOW)


state = "Led is off"
ser=serial.Serial('/dev/serial0' ,9600)

while True:
    if ser.inWaiting():
        data = ser.read(ser.inWaiting())
        data = data.decode('ascii')
        data = data[:-2]
        if data == "1":
            print("Turning on")
            GPIO.output(21,GPIO.HIGH)
            state = "Led is on"
        if data == "0":
            print("Turning off")
            GPIO.output(21,GPIO.LOW)
            state = "Led is off"
        if data == "state":
            ser.write(state.encode('ascii'))
            print(state)
    time.sleep(1)


