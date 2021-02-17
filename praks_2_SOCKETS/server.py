import socket
import sys
import threading

ip = "localhost"
port = 12345
clients = []

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
    while True:
        for client in clients:
            data = client.recv(2048)  # ootab kuni clients[0] saadab data
            print(data.decode("utf-8"))


def send_data(clients):
    while True:
        data = input().encode("utf-8")
        for client in clients:
            client.send(data)


def start_server():
    global clients

    while True:
        # Initial message sent
        client_socket, adress = server.accept()
        print("User {} connected.".format(adress[0]))
        client_socket.send("You are connected.".encode("utf-8"))
        clients.append(client_socket)

        getter = threading.Thread(target=get_data, args=(clients,))
        getter.start()

        sender = threading.Thread(target=send_data, args=(clients,))
        sender.start()


start_server()
