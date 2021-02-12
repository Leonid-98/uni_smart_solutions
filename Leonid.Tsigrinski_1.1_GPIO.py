import time

import RPi.GPIO as GPIO

pin = [18, 21]
delay = 0.5  # 1 Hz // 0.5 + 0.5

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 0)


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


# task 3
# 7 segment led
state = "0 - 9"
number = 0  # current number
while True:
    if state == "0 - 9":
        pass
        # show 0 - 9
        # if button:
        #   state = "9 - 0"


    elif state == "9 - 0":
        pass
        # change direction
        # if button:
        #   state = "random"

    elif state == "random":
        pass
        # randomm show
        # if button:
        #   state = "0 - 9" # RESTORE
