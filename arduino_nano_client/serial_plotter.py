#!/usr/bin/env python3

from serial import Serial
import sys

import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

fd = None


def get_val():
    if fd.isOpen():
        ligne = fd.readline()
        s = "".join([chr(i) for i in list(ligne)][0:-2])
        try:
            s = int(s)
            return s
        except:
            pass

n= 0
# This function is called periodically from FuncAnimation
def animate(i, xs, ys):
    global n
    # Read temperature (Celsius) from TMP102
    temp_c = get_val()

    # Add x and y to lists
    xs.append(str(n))
    n += 1
    ys.append(temp_c)

    # Limit x and y lists to 20 items
    xs = xs[-50:]
    ys = ys[-50:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Serial Value')
    plt.ylabel('Value')
    plt.xlabel('Time');

# Set up plot to call animate() function periodically


# Port série ttyACM0
# Vitesse de baud : 9600
# Timeout en lecture : 1 sec
# Timeout en écriture : 1 sec
def read_serial(fp="/dev/ttyUSB0", baud="9600"):
    try:
        fd = Serial(port=fp, baudrate=int(baud), timeout=1, writeTimeout=1)
        return fd
    except:
        sys.exit("Could not open file")

def main(argc, argv):
    global fd
    if argc != 3:
        exit(1)
    fd = read_serial(argv[1], argv[2])
    ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1)
    plt.show()

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)


