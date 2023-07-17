import socket

def is_prime(number_zh):
    if number_zh < 2:
        return False
    for i in range(2, int(number_zh ** 0.5) + 1):
        if number_zh % i == 0:
            return False
    return True

# Create a socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to a specific IP address and port
server_address = ('', 12345)
server_socket.bind(server_address)

print("Server is listening on {}:{}".format(server_address[0], server_address[1]))

# Receive number from client and check if it is prime
while True:
    data, client_address = server_socket.recvfrom(1024)
    number_request = int(data.decode())

    if is_prime(number_request):
        result = "{} is a prime number".format(number_request)
    else:
        result = "{} is not a prime number".format(number_request)

    # Send the result back to the client
    server_socket.sendto(result.encode(), client_address)
