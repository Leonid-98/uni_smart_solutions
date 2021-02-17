import socket
import sys

ip = "127.0.0.1"
port = 12345

server = socket.socket(
    socket.AF_INET,
    socket.SOCK_STREAM
)

server.bind(
    (ip, port)
)

server.listen(5)  # max 5 connect

while True:
    user_socket, adress = server.accept()
    user_socket.send("User {} connected".format(adress).encode("utf-8"))

