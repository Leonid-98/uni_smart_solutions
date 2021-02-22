import socket
import sys
import threading
import time
from select import select
import RPi.GPIO as GPIO
from random import randrange

pin_led = [23, 24]
pin_matrix = [25, 16, 20, 21, 26, 6, 5]

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(pin_led, GPIO.OUT)
GPIO.output(pin_led, 0)

GPIO.setup(pin_matrix, GPIO.OUT)
GPIO.output(pin_matrix, 1)

d = {
        1: [16, 20], 
        2: [25, 16, 26, 6, 5], 
        3: [16, 20, 26, 6, 5], 
        4: [20, 16, 21, 5], 
        5: [20, 21, 26, 6, 5],
        6: [25, 21, 26, 6, 5, 20], 
        7: [16, 20, 26], 
        8: [25, 16, 20, 21, 26, 6, 5],
        9: [20, 16, 21, 26, 6, 5],
        0: [25, 16, 20, 21, 26, 6]
    }


try:
    port = int(sys.argv[1])
except IndexError:
    port = 9999

ip = ""

try:
    socket_server = socket.socket()
    socket_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    socket_server.bind((ip, port))
    socket_server.listen(5)
    print("<Server {}: {} is running.>".format(ip, port))

except socket.error as msg:
    print("<Code: {}, Error: {}>".format(msg.args[0], msg.args[1]))
    sys.exit()


inactive_tasks = ["task1", "task2"]
def accept_data(client, connection):
    global inactive_tasks

    client_ip = connection[0]
    client_port = connection[1]
    last_task, last_state, delay = None, None, 0

    print("<{}: {} Connected.>".format(client_ip, client_port))

    while True:
        ready_sockets, _, _ = select([client], [], [], 0.01)  # timeout 1s

        if ready_sockets:
            data = client.recv(4096)
            decoded_data = data.decode("utf-8")

            if decoded_data == "exit":
                break
            if decoded_data == "?":
                client.send("Available tasks: {}".format(inactive_tasks).encode("utf-8"))

            print("({}: {}): {}".format(client_ip, client_port, decoded_data))
            message = decoded_data.split()

            if message[0] in ["task1", "task2"] and len(message) == 3:
                if message[0] in inactive_tasks:
                    index = inactive_tasks.index(message[0])
                    message[0] = inactive_tasks.pop(index)

                    last_task, last_state, delay = message[0], message[1], message[2]
                    led_control(message[0], message[1], message[2])
                    client.send("Doing task {}. State: {}".format(message[0], message[1]).encode("utf-8"))
                else:
                    if message[0] == last_task:
                        last_state, delay = message[1], message[2]
                        client.send(
                            "Doing task {}. State: {}. Delay: {}".format(message[0], message[1], message[2]).encode(
                                "utf-8"))
                    else:
                        client.send("Task is not available.".encode("utf-8"))
            else:
                if decoded_data != "?":
                    client.send(data)
        else:
            led_control(last_task, last_state, delay)

    print("<{}: {} Disconnected.>".format(client_ip, client_port))
    client.close()
    if message[0]:
        inactive_tasks.append(message[0])


number = 0
def led_control(task, state, delay):
    global tasks, active_tasks, number, pin_led, pin_matrix, d
    delay = float(delay)

    if task == "task1":
        if state == "stop":
            GPIO.output(pin_led, 0)

        elif state == "eraldi":
            GPIO.output(pin_led[0], 1)
            GPIO.output(pin_led[1], 0)
            time.sleep(delay)
            GPIO.output(pin_led[0], 0)
            GPIO.output(pin_led[1], 1)
            time.sleep(delay)
            
        elif state == "koos":
            GPIO.output(pin_led[0], 1)
            GPIO.output(pin_led[1], 1)
            time.sleep(delay)
            GPIO.output(pin_led[0], 0)
            GPIO.output(pin_led[1], 0)
            time.sleep(delay)

    elif task == "task2":
        if state == "stop":
            GPIO.output(pin_matrix, 1)

        elif state == "from_0":
            if number == 10: number = 0  # reset
            GPIO.output(pin_matrix, 1)
            GPIO.output(d[number], 0)
            number += 1
            time.sleep(delay)
            GPIO.output(pin_matrix, 1)

        elif state == "from_9":
            if number == -1: number = 9  # reset
            GPIO.output(pin_matrix, 1)
            GPIO.output(d[number], 0)
            number -= 1
            time.sleep(delay)
            GPIO.output(pin_matrix, 1)

        elif state == "random":
            number = randrange(0, 10, 1)
            GPIO.output(pin_matrix, 1)
            GPIO.output(d[number], 0)
            time.sleep(0.5)
            GPIO.output(pin_matrix, 1)

while True:
    try:
        client, ip = socket_server.accept()
        accepter = threading.Thread(target=accept_data, args=(client, ip))
        accepter.start()
        
    except socket.error as msg:
        print("<Code: {}, Error: {}>".format(msg.args[0], msg.args[1]))
        sys.exit()
