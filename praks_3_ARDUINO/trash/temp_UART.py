#!/usr/bin/python3
#plottimine on vaadatud osaliselt stackoverflowst
import serial,time,sys
import matplotlib.pyplot as plt
x = []
y = []
vastus = True
# avame pordi /dev/ttyUSB0 kiirusega 9600 boodi
ser=serial.Serial('/dev/serial0' ,9600)
# kuvame pordi nime
print(ser.name)
a = 100

while True:
    file = open("temp.txt", "w")
    if vastus:
        vastus = False

    if ser.inWaiting():
        read_serial=ser.read(ser.inWaiting())
        vastus = True
        ans = read_serial.decode('ascii')
        y.append(ans.rstrip())
        print (ans)
        print (a)
        a -= 1

    time.sleep(0.2)
    if (a == 0):
        file.write('\n'.join(y))
        file.close()
        break

for i in range(0, 100):
    x.append(i)
fig = plt.figure(figsize=(15,10))
plt.plot(x,y,lineWidth=0.7)
plt.title("Temperatuurid")
plt.xlabel('Mitmes mootmine')
plt.ylabel('Temperatuur')
plt.show()
fig.savefig('plot.png')

file.close()
ser.close()
sys.exit()
