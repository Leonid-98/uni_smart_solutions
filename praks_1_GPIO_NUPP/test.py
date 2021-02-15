import time
from random import randrange

import RPi.GPIO as GPIO

pin = [4, 17, 27, 22, 23, 24, 25]
button = 21

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin, GPIO.OUT) # 5V
GPIO.output([4, 17, 27, 22, 24, 25], 0)
GPIO.setup(button, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)


time.sleep(1)
GPIO.output(pin, 1)