import socket
import sys
import threading
from select import select

ip = "localhost"
port = 9999
inactive_tasks = ["task1", "task2"]

try:
    socket_server = socket.socket()
    socket_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    socket_server.bind((ip, port))
    socket_server.listen(5)
    print("<Server {}: {} is running.>".format(ip, port))

except socket.error as msg:
    print("<Code: {}, Error: {}>".format(msg.args[0], msg.args[1]))
    sys.exit()


def led_control(task, new_state):
    global state, tasks, active_tasks, clients

    if task == "task1":
        print("Yeah baby, task 1", new_state)
    elif task == "task2":
        print("Nooo way 2nd task", new_state)



def accept_data(client, connection):
    global inactive_tasks

    client_ip = connection[0]
    client_port = connection[1]
    last_task, last_state = None, None

    print("<{}: {} Connected.>".format(client_ip, client_port))

    while True:
        ready_sockets, _, _ = select([client], [], [], 1)  # timeout 1s

        if ready_sockets:
            data = client.recv(4096)
            decoded_data = data.decode("utf-8")

            if decoded_data == "exit":
                break
            if decoded_data == "?":
                client.send({inactive_tasks}.encode("utf-8"))

            print("({}: {}): {}".format(client_ip, client_port, decoded_data))
            message = decoded_data.split()

            if message[0] in ["task1", "task2"] and len(message) == 2:
                if message[0] in inactive_tasks:
                    index = inactive_tasks.index(message[0])
                    message[0] = inactive_tasks.pop(index)

                    last_task, last_state = message[0], message[1]
                    led_control(message[0], message[1])
                    client.send(f"Doing task {}. State: {}".format(message[0], message[1]).encode("utf-8"))
                else:
                    if message[0] == last_task:
                        last_state = message[1]
                        client.send(f"Doing task {}. State: {}".format(message[0], message[1]).encode("utf-8"))
                    else:
                        client.send("Task is not available.".encode("utf-8"))
            else:
                client.send(data)
        else:
            led_control(last_task, last_state)

    if message[0]:
        inactive_tasks.append(message[0])
    print("<{}: {} Disconnected.>".format(client_ip, client_port))
    client.close()


while True:
    try:
        client, ip = socket_server.accept()
        # threading._start_new_thread(accept_data, (client, ip))
        accepter = threading.Thread(target=accept_data, args=(client, ip))
        accepter.start()

    except socket.error as msg:
        print("<Code: {}, Error: {}>".format(msg.args[0], msg.args[1]))
        sys.exit()
