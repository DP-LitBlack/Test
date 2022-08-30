import socket
import datetime as dt
import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.widgets import Button

msgFromClient       = "Hello UDP Server"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = ("192.168.0.17", 8080)
bufferSize          = 1024

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(2, 1, 1)

plt.title('TMP102 Temperature over Time')
plt.ylabel('Temperature (deg C)')

# ani = animation
paused = False

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
xs1, ys1 = [],[]
xs2, ys2 = [],[]

# Adjustable parameters
xlimit = 100
frame_num = 1
num_i = 0
num_j = 0

# # This function is called periodically from FuncAnimation
def animate(i):
    # Add x and y to lists
    global num_i
    global num_j
    global xs1, ys1, xs2, ys2

    try:
        UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        UDPClientSocket.settimeout(2)
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        msg = msgFromServer[0].decode()

        # print(int(msg[1:]))
        if msg[0] == "r":
            ys1.append(float(msg[1:]))
            # xs1.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
            xs1.append(num_i)
            num_i = num_i + 1
            xs1 = xs1[-xlimit:]
            ys1 = ys1[-xlimit:]
        elif msg[0] == "p":
            ys2.append(float(msg[1:]))
            # xs2.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
            xs2.append(num_j)
            num_j = num_j + 1
            xs2 = xs2[-xlimit:]
            ys2 = ys2[-xlimit:]

        # print(xs1)
        ax.clear()

        plt.subplots_adjust(bottom=0.1)
        # plt.subplots_adjust(bottom=0.5)
        # plt.xticks(rotation=45, ha='right')
        plt.title('TMP102 Temperature over Time')
        plt.ylabel('Temperature (deg C)')
        ax.plot(xs1, ys1, color="red")
        ax.plot(xs2, ys2, color="blue")

    except socket.timeout:
        # UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        return





# def pause(event):
#     pause = True

# def resume(event):
#     pause = False



# axprev = plt.axes([0.7, 0.05, 0.1, 0.075])
# axnext = plt.axes([0.81, 0.05, 0.1, 0.075])
# bnext = Button(axnext, 'Pause')
# bnext.on_clicked(pause)
# bprev = Button(axprev, 'Resume')
# bprev.on_clicked(resume)

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, frames=100,
                                interval=xlimit)

plt.show()