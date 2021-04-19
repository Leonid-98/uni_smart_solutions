import socket
import sys
import threading
import time
from select import select
from random import randrange

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


def accept_data(client, connection):
    global inactive_tasks

    client_ip = connection[0]
    client_port = connection[1]
    last_task, last_state, delay = None, None, 0

    print("<{}: {} Connected.>".format(client_ip, client_port))

    while True:
        ready_sockets, _, _ = select([client], [], [], 0.01)  # timeout

        if ready_sockets:
            data = client.recv(4096)
            decoded_data = data.decode("utf-8")

            print("({}: {}): {}".format(client_ip, client_port, decoded_data))
            message = decoded_data.split()


    print("<{}: {} Disconnected.>".format(client_ip, client_port))
    client.close()



while True:
    try:
        client, ip = socket_server.accept()
        accepter = threading.Thread(target=accept_data, args=(client, ip))
        accepter.start()
        
    except socket.error as msg:
        print("<Code: {}, Error: {}>".format(msg.args[0], msg.args[1]))
        sys.exit()

