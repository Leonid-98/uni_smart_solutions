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

while True:
    data = input("::: ")
    client_socket.send(data.encode('utf-8'))

    if data == 'exit':
        print("<Client disconnected>")
        break

    server_response = client_socket.recv(4096)
    print("<Server received: {}>".format(server_response.decode()))
