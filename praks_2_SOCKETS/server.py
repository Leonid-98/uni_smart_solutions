import socket
from RobotMove_module import *
import speech_recognition as sr

HOST = "192.168.119.129"
PORT = 12345

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print ('Socket created')

try:
    s.bind((HOST, PORT))
except:
    print("Bind failed")
    
s.listen(5)
conn, adrr = s.accept()

def move(x):
    if x[1] == "forward":
        try:
            x[2] = int(x[2])
            soida_otse(x[2])
        except:
            print(f'Error, cant understand: {x}')
    elif x[1] == "backward":
        try:
            x[2] = int(x[2])
            soida_tagasi(x[2])
        except:
            print(f'Error, cant convert {x[2]} into int')
    else:
        print(f'Error, cant understand: {x}')

def turn(x):
    if x[1] == 'left':
        try:
            x[2] = int(x[2])
            keera_vasakule(x[2])
        except:
            print(f'Error, cant convert {x[2]} into int')
    elif x[1] == 'right':
        try:
            x[2] = int(x[2])
            keera_paremale(x[2])
        except:
            print(f'Error, cant convert {x[2]} into int')
    else:
        print(f'Error, cant understand: {x}')

def speed(x):
    try:
        x[2] = int(x[2])
        kiirus(x[2])
    except:
        print(f'Error, cant convert {x[2]} into int')

def parallel(x):
    if x[2] == 'right':
        parallel_park_parem()
    elif x[2] == 'left':
        parallel_park_vasak()
    else:
        print(f'Error, cant understand: {x}')

while True:
    x = conn.recv(1024)
    x = x.decode('utf-8')
    x = eval(x)
    try:
        if not x is None:
            if x[0] == "move" and len(x) >= 3:
                move(x)
            elif x[0] == "turn" and len(x) >= 3:
                turn(x)
            elif x[1] == "speed" and len(x) >= 2:
                speed(x)
            elif x[0] == "parallel" and len(x) >= 3:
                parallel(x)
            elif x[0] == "stop":
                stop()
            else:
                x = ' '.join([str(i) for i in x])
                print(f'Info is not clear: {x}')
        else:
            print('Input is NoneType')
    
    except sr.UnknownValueError:
        print("Could not understand audio")
    except sr.RequestError as e:
        print("Error; {0}".format(e))
            
        
