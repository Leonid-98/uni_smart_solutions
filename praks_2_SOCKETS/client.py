import socket

ip = "127.0.0.1"
port = 12345

client = socket.socket(
    socket.AF_INET,
    socket.SOCK_STREAM
)

client.connect(
    (ip, port)
)

while True:
    data = client.recv(2048)
    print(data.decode("utf-8"))

