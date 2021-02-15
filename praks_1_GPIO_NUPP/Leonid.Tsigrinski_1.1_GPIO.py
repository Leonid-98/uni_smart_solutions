import time
import RPi.GPIO as GPIO

pin = [4, 18, 17, 27, 23, 22, 24, 25, 19, 26]
delay = 0.5  # 1 Hz // 0.5 + 0.5

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 0)
time.sleep(1)
#GPIO.output(pin, 3)



def task1():
    # 1 led
    global pin, delay
    while True:
        GPIO.output(pin[0], 1)
        time.sleep(delay)
        GPIO.output(pin[0], 0)
        time.sleep(delay)

def task2():
    # 2 led
    global pin, delay
    while True:
        GPIO.output(pin[0], 1)
        GPIO.output(pin[1], 0)
        time.sleep(delay)
        GPIO.output(pin[0], 0)
        GPIO.output(pin[1], 1)
        time.sleep(delay)


def task3(delay):
    # 10 segment led
    global pin

    while True:
        for led in pin:
            GPIO.output(led, 1)  # ON
            time.sleep(delay)
            GPIO.output(led, 0)  # OFF
        for led in reversed(pin):
            GPIO.output(led, 1)  # ON
            time.sleep(delay)
            GPIO.output(led, 0)  # OFF
task3(0.02)
            
            

