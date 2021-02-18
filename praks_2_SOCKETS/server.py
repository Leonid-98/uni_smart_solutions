import socket
import sys
import threading

ip = "localhost"
port = 12345

# if sys.argv[1]:
#     port = int(sys.argv[1])

try:
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # reuse same ip addr
    server.bind((ip, port))
    server.listen(10)
    print("<Server {} created.>".format(ip))
except socket.error as msg:
    print("<Code: {}, message: {}>".format(msg.args[0], msg.args[1]))
    sys.exit()


def get_data(client_socket):
    while True:
        try:
            data = client_socket.recv(2048)
            id = client_socket.getpeername()
            print("{}: {}".format(id, data.decode("utf-8")))

        except ConnectionResetError as msg:
            print("<Code: {}, message: {}>".format(msg.args[0], msg.args[1]))
            sys.exit()


def send_data(all_clients):
    while True:
        data = input()
        for client in all_clients:
            client.send("Server: {}".format(data).encode("utf-8"))


def accept_connection():
    all_clients = []

    while True:
        # Initial message sent
        client_socket, adress = server.accept()
        print("<User {} connected.>".format(adress[0]))
        client_socket.send("Server: You are connected.".encode("utf-8"))
        all_clients.append(client_socket)

        getter = threading.Thread(target=get_data, args=(client_socket,))
        getter.start()

        sender = threading.Thread(target=send_data, args=(all_clients,))
        sender.start()


accept_connection()
