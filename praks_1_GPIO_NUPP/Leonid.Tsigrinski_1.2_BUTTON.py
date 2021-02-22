# https://www.woolseyworkshop.com/2019/02/27/interfacing-a-7-segment-display-to-a-raspberry-pi/

import time
from random import randrange

import RPi.GPIO as GPIO

pin = [4, 17, 27, 22, 23, 24, 25]
button = 21

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin, GPIO.OUT) # 5V
GPIO.output(pin, 1)
GPIO.setup(button, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)


def show_number(number):
    global pin_matrix
    
    d = {
        1: [22, 25],
        2: [4, 27, 22, 23, 24],
        3: [4, 27, 22, 24, 25],
        4: [4, 17, 22, 25],
        5: [4, 17, 27, 24, 25],
        6: [4, 17, 27, 24, 25, 23],
        7: [17, 27, 22, 25],
        8: [4, 17, 27, 22, 23, 24, 25],
        9: [4, 17, 27, 22, 24, 25],
        0: [17, 27, 22, 23, 24, 25]
    }
    GPIO.output(pin, 1)
    GPIO.output(d[number], 0)


def next_state(event):
    global state, pin
    if state == "from_start":
        state = "from_end"

    elif state == "from_end":
        state = "random"

    elif state == "random":
        state = "from_start"
        
    print(state)


GPIO.add_event_detect(button, GPIO.FALLING, callback=next_state, bouncetime=250)
state = "from_start"
number = 0  # current number

while True:
    if state == "from_start":
        if number == 10: number = 0  # reset
        show_number(number)
        number += 1
        time.sleep(0.5)
        GPIO.output(pin, 1)

    elif state == "from_end":
        if number == -1: number = 9  # reset
        show_number(number)
        number -= 1
        time.sleep(0.5)
        GPIO.output(pin, 1)

    elif state == "random":
        number = randrange(0, 10, 1)
        show_number(number)
        time.sleep(0.5)
        GPIO.output(pin, 1)
