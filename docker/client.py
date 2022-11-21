import  socket
c = socket.socket()

try:
    c.connect(('localhost',9999))

except socket.error as err:
    print(err)

name = input("Enter your name :")
c.send(bytes(name.encode()))
print(c.recv(1024).decode())
while True:
    received = c.recv(1024).decode()
    print("Reply from Server" , ":" ,received)
    mess = input("Chat here : ")
    c.send(mess.encode())
    if received == "bye":
        break
        c.close()