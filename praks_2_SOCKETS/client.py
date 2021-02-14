import socket
import speech_recognition as sr
import snowboydecoder

HOST = "192.168.119.129"
PORT = 12345

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))

detector = snowboydecoder.HotwordDetector("computer.pmdl")
sensitivity = 0.5
print('Listening for hotword... PressCtrl+C to exit')

x = 0

def speak():
    global sr
    r = sr.Recognizer()
    with sr.Microphone() as source:
        r.adjust_for_ambient_noise(source)
        print("Say something: ")
        audio = r.listen(source)

    try:
        x = r.recognize_google(audio)
        x = x.split(" ")
        print(x)
        x = str(x)
        x = x.encode()
        s.send(x)

    except:
        print("Couldn't detect audio")
              
detector.start(speak)
detector.terminate()



