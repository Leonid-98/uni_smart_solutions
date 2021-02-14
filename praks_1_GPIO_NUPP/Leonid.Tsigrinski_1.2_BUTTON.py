# https://www.woolseyworkshop.com/2019/02/27/interfacing-a-7-segment-display-to-a-raspberry-pi/

import time
from random import randrange

import RPi.GPIO as GPIO

pin = [18, 21]
button = None
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 0)
time.sleep(1)


def show_number(number):
    d = {
        1: [],
        2: [],
        3: [],
        4: [],
        5: [],
        6: [],
        7: [],
        8: [],
        9: [],
        0: []
    }
    GPIO.output(d[number], 1)


def next_state():
    global state, pin
    if state == "from_start":
        state = "from_end"

    elif state == "from_end 0":
        state = "random"

    elif state == "random":
        state = "from_start"


GPIO.add_event_detect(button, GPIO.FALLING, callback=next_state, bouncetime=250)
state = "from_start"
number = 0  # current number

while True:
    if state == "from_start":
        if number == 10: number = 0  # reset
        show_number(number)
        number += 1
        time.sleep(0.5)
        GPIO.output(pin, 0)

    elif state == "from_end":
        if number == -1: number = 9  # reset
        show_number(number)
        number -= 1
        time.sleep(0.5)
        GPIO.output(pin, 0)

    elif state == "random":
        number = randrange(0, 10, 1)
        show_number(number)
        time.sleep(0.5)
        GPIO.output(pin, 0)
