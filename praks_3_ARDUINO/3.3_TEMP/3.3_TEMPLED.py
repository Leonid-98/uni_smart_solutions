import serial
import time
import matplotlib.pyplot as plt
import numpy as np

state = True
ser=serial.Serial('/dev/serial0' ,9600)

plt.ion()
fig=plt.figure()
plt.axis([0, 0, 18, 35])
i=0
x= []
y=list()

while True:
    if state:
        sonum = "data\n"
        ser.write(sonum.encode('ascii'))
        time.sleep(0.2)
        
        state = False
        
    if ser.inWaiting():
        read_serial=ser.read(ser.inWaiting())
        state = True
        
        temp = int(read_serial.decode('ascii'))
        x.append(i);
        y.append(temp);
        plt.scatter(i,temp)
        i+=1
        plt.show()
        plt.pause(0.8)
        
        print(temp)
        
    time.sleep(0.8)

