import time
from random import randrange

import RPi.GPIO as GPIO

pin_matrix = [25, 16, 20, 21, 26, 6, 5]
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin_matrix, GPIO.OUT)
GPIO.output(pin_matrix, 1)
d = {
        1: [16, 20], #
        2: [25, 16, 26, 6, 5], #
        3: [16, 20, 26, 6, 5], #
        4: [20, 16, 21, 5], #
        5: [20, 21, 26, 6, 5],
        6: [25, 21, 26, 6, 5, 20], #
        7: [16, 20, 26], #
        8: pin_matrix,
        9: [20, 16, 21, 26, 6, 5],
        0: [25, 16, 20, 21, 26, 6]
    }
GPIO.output(pin_matrix, 0)
