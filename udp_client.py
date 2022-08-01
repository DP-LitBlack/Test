import socket
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import Button

msgFromClient       = "Hello UDP Server"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = ("192.168.0.17", 8080)
bufferSize          = 1024

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(2, 1, 1)
plt.subplots_adjust(bottom=0.5)
xs = []
ys = []

ani = animation
paused = False

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Adjustable parameters
xlimit = 20
ylimit = 20
xlength = 100

# # This function is called periodically from FuncAnimation
def animate(i, xs, ys):
    # Add x and y to lists
    try:
        UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        UDPClientSocket.settimeout(2)
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        msg = "Message from Server {}".format(msgFromServer[0])
        print(msgFromServer[0])
        ys.append(int(msgFromServer[0]))
        xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))

    except socket.timeout:
        # UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        return

    # Limit x and y lists to 20 items
    xs = xs[-xlimit:]
    ys = ys[-ylimit:]

    # Draw x and y lists
    if(not paused): 
        ax.clear()
        ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('TMP102 Temperature over Time')
    plt.ylabel('Temperature (deg C)')

def pause(event):
    pause = True

def resume(event):
    pause = False



# axprev = plt.axes([0.7, 0.05, 0.1, 0.075])
# axnext = plt.axes([0.81, 0.05, 0.1, 0.075])
# bnext = Button(axnext, 'Pause')
# bnext.on_clicked(pause)
# bprev = Button(axprev, 'Resume')
# bprev.on_clicked(resume)

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=100)

plt.show()




