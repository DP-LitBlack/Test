import socket
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation

msgFromClient       = "Hello UDP Server"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = ("192.168.0.17", 8080)
bufferSize          = 1024

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

ani = animation

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# # This function is called periodically from FuncAnimation
def animate(i, xs, ys):
    # Add x and y to lists
    try:
        UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        UDPClientSocket.settimeout(2)
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        msg = "Message from Server {}".format(msgFromServer[0])
        print(int(msgFromServer[0]))
        ys.append(int(msgFromServer[0]))
        xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))

    except socket.timeout:
        # UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        return


    # Limit x and y lists to 20 items
    xs = xs[-20:]
    ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('TMP102 Temperature over Time')
    plt.ylabel('Temperature (deg C)')

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=100)
plt.show()




