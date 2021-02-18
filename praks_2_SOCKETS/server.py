import socket
import sys
import threading
from select import select

ip = "localhost"
port = 12345
clients = []

# if sys.argv[1]:
#     port = int(sys.argv[1])

try:
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # reuse same ip addr
    server.bind((ip, port))
    server.listen(10)
    print("Sucess...\nServer {} created.".format(ip))
except socket.error as msg:
    print("Fail...\nCode: {}, message: {}".format(msg.args[0], msg.args[1]))
    sys.exit()


def get_data(clients):
    """
    Thread 1. Saab andmed clientist.
    Clients[] on list cient socketiga.
    For loop kontrolib, kas server sai mingi info v6i mitte.
    """
    while True:
        ready_to_read, _, _ = select(clients, [], [])
        for client in ready_to_read:
            try:
                data = client.recv(2048)
                print(data.decode("utf-8"))
            except ConnectionResetError as msg:
                print("Fail...\nCode: {}, message: {}".format(msg.args[0], msg.args[1]))
                sys.exit()


def send_data(clients):
    """
    Thread 2. Saadab andmed clientile.
    Clients[] on list cient socketiga.
    """
    while True:
        data = input().encode("utf-8")
        for client in clients:
            client.send(data)


def accept_connection(clients):
    """
    Main thread. Pääseb clientid connectida.
    """
    while True:
        # Initial message sent
        client_socket, adress = server.accept()
        print("User {} connected.".format(adress[0]))
        client_socket.send("You are connected.".encode("utf-8"))
        clients.append(client_socket)

        getter = threading.Thread(target=get_data, args=(client_socket,))
        getter.start()

        sender = threading.Thread(target=send_data, args=(clients,))
        sender.start()


accept_connection(clients)
