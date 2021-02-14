# https://www.woolseyworkshop.com/2019/02/27/interfacing-a-7-segment-display-to-a-raspberry-pi/

import time
import RPi.GPIO as GPIO

pin = [18, 21]
button = None
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 0)
time.sleep(1)


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
        pass
        # show 0 - 9
        # number += 1
        # if number = 9:
        #   number = 0
        # time.sleep(1)


    elif state == "from_end":
        pass
        # change direction
        # time.sleep(1)

    elif state == "random":
        pass
        # randomm show
        # time.sleep(1)