import serial

with serial.Serial('COM4', 9600) as ser:
    x = ser.readline
    print(x)
    
    ser.wrtie("This is my message \n")
    
    y = ser.readline()
    print(y)
    
    ser.close
    