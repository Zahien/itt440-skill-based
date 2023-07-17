import socket

# Create a socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Server address
server_address = ('localhost', 12345)

# Get a number from the user
get_number_zh = int(input("Enter a number: "))

# Send the number to the server
client_socket.sendto(str(get_number_zh).encode(), server_address)

# Receive the result from the server
result, _ = client_socket.recvfrom(1024)

print(result.decode())

# Close the socket
client_socket.close()
