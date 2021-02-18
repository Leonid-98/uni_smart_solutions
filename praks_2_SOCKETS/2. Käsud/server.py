import sys
import socket
import threading

ip = "localhost"
port = 9999

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
    client_ip = connection[0]
    client_port = connection[1]
    print("<{}: {} Connected.>".format(client_ip, client_port))

    while True:
        data = client.recv(1024)
        decoded_data = data.decode("utf-8")

        if decoded_data == 'exit':
            break
        print("({}: {}): {}".format(client_ip, client_port, decoded_data))
        client.sendall(data)

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
