import sys
import socket
import threading

ip = "localhost"
port = 9999

try:
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip, port))
    print("<Connected to server: {}: {}>".format(ip, port))

except socket.error as msg:
    print("<Code: {}, Error: {}>".format(msg.args[0], msg.args[1]))
    sys.exit()

def accept_response(client_socket):
    server_response = client_socket.recv(4096)
    print("Server response: {}".format(server_response.decode()))


while True:
    data = input("::: ")
    client_socket.send(data.encode('utf-8'))

    if data == 'exit':
        print("<Client disconnected>")
        break

    response_getter = threading.Thread(target=accept_response, args=(client_socket,))
    response_getter.start()

