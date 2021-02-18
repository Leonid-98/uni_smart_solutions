import socket
import sys
import threading

ip = "localhost"
port = 12345

# if sys.argv[1]:
#     ip = sys.argv[1]
# if sys.argv[2]:
#     port = int(sys.argv[2])

try:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, port))
except socket.error as msg:
    print("Fail...\nCode: {}, Error: {}".format(msg.args[0], msg.args[1]))
    sys.exit()


def get_data(client):
    while True:
        data = client.recv(2048)
        print(data.decode("utf-8"))


def send_data(client):
    while True:
        data = input().encode("utf-8")
        client.send(data)


while True:
    # Initial message received
    data = client.recv(2048)
    print(data.decode("utf-8"))

    getter = threading.Thread(target=get_data, args=(client,))
    getter.start()

    sender = threading.Thread(target=send_data, args=(client,))
    sender.start()
